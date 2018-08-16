#include "invoke.h"
#include "error.h"

#include <windows.h>
#include <psapi.h>

#include <cstring>
#include <iostream>
using namespace std;

BOOL APIENTRY DllMain(
    HANDLE,
    DWORD,
    LPVOID)
{
    return TRUE;
}

void getProcessTimeInfo(HANDLE handle, boolean useExitTime, int64& timeConsumed, int64& timePassed) {
    FILETIME creationTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    SYSTEMTIME currentTimeSys;
    FILETIME currentTime;

    GetProcessTimes(handle, &creationTime, &exitTime, &kernelTime, &userTime);
    if (useExitTime) {
        currentTime = exitTime;
    } else {
        GetSystemTime(&currentTimeSys);
        SystemTimeToFileTime(&currentTimeSys, &currentTime);
    }

    __int64 r = *(reinterpret_cast<int64*>(&kernelTime)) +
                *(reinterpret_cast<int64*>(&userTime));

    r /= 10000;

    timeConsumed = r;

    r = *(reinterpret_cast<int64*>(&currentTime)) -
        *(reinterpret_cast<int64*>(&creationTime));

    r /= 10000;

    timePassed = r;
}

void getProcessMemoryInfo(HANDLE handle, int64& currentMemoryConsumed, int64& peakMemoryConsumed) {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
    currentMemoryConsumed = pmc.WorkingSetSize;
    peakMemoryConsumed = pmc.PeakWorkingSetSize;
}

static void openForRead(char* fileName, SECURITY_ATTRIBUTES* sa, HANDLE& handle) {
    handle = CreateFile(
        fileName == NULL ? TEXT("nul") : fileName,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        sa,
        OPEN_EXISTING,
        0,
        NULL);
}

static void openForWrite(char* fileName, SECURITY_ATTRIBUTES* sa, HANDLE& handle) {
    handle = CreateFile(
        fileName == NULL ? TEXT("nul") : fileName,
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        sa,
        CREATE_ALWAYS,
        0,
        NULL);
}

/**
 * If INVOKE_REDIRECT_STD_STREAMS flag is set in invocation request passed,
 * opens standard handles. The handles that are not equal to HANDLE_INVALID_VALUE
 * must be closed before invoke routine returns, even if openStandardHandles returns
 * false.
 *
 * @param ip - Invocation request that contains names of files to open. If some
 *     file name is NULL, the corresponding handle value is set to INVALID_HANDLE_VALUE.
 * @param sh - StandardHandles structure that must be filled with open handles.
 * @return whether all handles were successfully opened.
 */
static bool openStandardHandles(InvocationRequest* ip, boolean redirect, StandardHandles* sh, SECURITY_ATTRIBUTES* sa) {
    sh->input = INVALID_HANDLE_VALUE;
    sh->output = INVALID_HANDLE_VALUE;
    sh->error = INVALID_HANDLE_VALUE;

    if (!redirect) {
        return true;
    }

    openForRead(ip->inputFileName, sa, sh->input);
    if (sh->input == INVALID_HANDLE_VALUE) {
         return false;
    }
    openForWrite(ip->outputFileName, sa, sh->output);
    if (sh->output == INVALID_HANDLE_VALUE) {
         return false;
    }
    if (ip->outputFileName != NULL && ip->errorFileName != NULL &&
            strcmp(ip->outputFileName, ip->errorFileName) == 0) {
        sh->error = sh->output;
    } else {
        openForWrite(ip->errorFileName, sa, sh->error);
        if (sh->error == INVALID_HANDLE_VALUE) {
             return false;
        }
    }

    return true;
}

/**
 * Closes all handles that are not equal to INVALID_HANDLE_VALUE.
 */
static void closeStandardHandles(StandardHandles* sh) {
    if (sh == NULL) {
        return;
    }
    if (sh->input != INVALID_HANDLE_VALUE) {
        CloseHandle(sh->input);
    }
    if (sh->output != INVALID_HANDLE_VALUE) {
        CloseHandle(sh->output);
    }
    if (sh->error != INVALID_HANDLE_VALUE) {
        CloseHandle(sh->error);
    }
}

__declspec(dllexport)
void invokeWithHandles(
    InvocationRequest* ip,
    InvocationResult* ir,
    InvocationCallback callback,
    StandardHandles* standardHandles)
{
    memset(ir, 0, sizeof(*ir));

    InvocationStatus is;
    memset(&is, 0, sizeof(is));
    is.state = PREPARING;
    is.processorLoad = 0.0;
    is.userInfo = ip->userInfo;

    if (callback != NULL) {
        if ((*callback)(&is)) {
            ir->outcome = FAIL;
            ir->comment = _strdup(TEXT("Forced to terminate by callack"));
            return;
        }
    }


    SetLastError(ERROR_SUCCESS);

    if (ip == NULL || ip->program == NULL || ir == NULL) {
        SetLastError(ERROR_INVOKE_NULL_PARAMETER);
        if (ir != NULL) {
            ir->outcome = FAIL;
            ir->comment = _strdup(TEXT("One of the parameters is NULL"));
        }
        return;
    }

    ir->outcome = SUCCESS;
    ir->comment = NULL;

    if (ip->requiredProcessorLoad < 0.0 || ip->requiredProcessorLoad > 1.0) {
        SetLastError(ERROR_INVOKE_INVALID_INVOCATION_PARAMETER);
        ir->outcome = FAIL;
        ir->comment = _strdup(TEXT("Invalid minimal non-idle load passed as the parameter"));
        return;
    }

    STARTUPINFO si;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.lpDesktop = TEXT("");

    if ((ip->flags & INVOKE_SHOW_APPLICATION_WINDOW) == 0) {
       si.dwFlags |= STARTF_USESHOWWINDOW;
       si.wShowWindow = SW_HIDE;
    }

    if (standardHandles != NULL) {
        si.dwFlags |= STARTF_USESTDHANDLES;
        si.hStdInput = standardHandles->input;
        si.hStdOutput = standardHandles->output;
        si.hStdError = standardHandles->error;
    }

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));

    size_t commandLineLen = strlen(ip->program);
    for (int i = 0; i < ip->argc; i++) {
        commandLineLen += strlen(ip->argv[i]) + 1;
    }
    char* commandLine = (char*) malloc(commandLineLen + 1);
    commandLine[0] = 0;
    strcpy(commandLine, ip->program);
    for (int i = 0; i < ip->argc; i++) {
        strcat(commandLine, " ");
        strcat(commandLine, ip->argv[i]);
    }

    BOOL createOk;
    if (ip->login == NULL) {
        createOk = CreateProcess(
            NULL,
            commandLine,
            NULL,
            NULL,
            standardHandles != NULL ? TRUE : FALSE,
            CREATE_NEW_CONSOLE | DEBUG_PROCESS,
            ip->environment,
            ip->directory,
            &si,
            &pi);
    } else {
        char* login;
        char* domain;

        char* buffer = _strdup(ip->login);
        char* delimiter = strstr(buffer, TEXT("\\"));

        if (delimiter != NULL) {
            *delimiter = 0;
            login = delimiter + 1;
            domain = buffer;
        } else {
            login = buffer;
            domain = TEXT(".");
        }

        HANDLE hUser;
        if (!LogonUser(
            login,
            domain,
            ip->password != NULL ? ip->password : TEXT(""),
            LOGON32_LOGON_BATCH,
            LOGON32_PROVIDER_DEFAULT,
            &hUser
            ))
        {
            ir->outcome = FAIL;
            ir->comment = getErrorDescription("LogonUser", GetLastError());
            free(commandLine);
            closeStandardHandles(standardHandles);
            return;
        }

        createOk = CreateProcessAsUser(
            hUser,
            NULL,
            commandLine,
            NULL,
            NULL,
            standardHandles != NULL ? TRUE : FALSE,
            CREATE_NEW_CONSOLE | DEBUG_PROCESS,
            ip->environment,
            ip->directory,
            &si,
            &pi
        );
        CloseHandle(hUser);
    }

    if (!createOk) {
        if (ip->flags & INVOKE_SECURITY_VIOLATION_IF_FAILED_TO_INVOKE) {
            ir->outcome = SECURITY_VIOLATION;
        } else {
            ir->outcome = FAIL;
        }
        int error = GetLastError();
        ir->comment = getErrorDescription("CreateProcess", error, commandLine);
        free(commandLine);

        if (callback != NULL) {
            is.state = FAILED_TO_INVOKE;
            ((*callback)(&is));
        }

        closeStandardHandles(standardHandles);
        return;
    }
    free(commandLine);


    int interval = 100;
    DEBUG_EVENT de;

    const int smoothPeriod = 10;

    int64 oldTimeConsumed[smoothPeriod];
    int64 oldTimePassed[smoothPeriod];
    int hits = 0;

    bool signal = false;
    bool signalled = false;
    bool terminated = false;

    is.state = RUNNING;
    is.processorLoad = 1.0;

    if ((ip->flags & INVOKE_SET_SINGLE_AFFINITY) != 0) {
        SetProcessAffinityMask(pi.hProcess, 1);
    }

    int processes = 0;
    while (!terminated) {
        BOOL deok = WaitForDebugEvent(&de, interval);
        bool handled = true;

        if (deok) {
            switch (de.dwDebugEventCode) {
                case EXCEPTION_DEBUG_EVENT: {
                    DWORD eCode = de.u.Exception.ExceptionRecord.ExceptionCode;
                    if (
                        eCode == EXCEPTION_BREAKPOINT ||
                        eCode == STATUS_SEGMENT_NOTIFICATION ||
                        eCode == STATUS_INVALID_HANDLE)
                    {
                        break;
                    }


                    if (!de.u.Exception.dwFirstChance || (ip->flags & INVOKE_TERMINATE_ON_FIRST_CHANCE_EXCEPTIONS)) {
                        ir->outcome = CRASH;
                        is.state = CRASHED;
                        ir->exceptionCode = de.u.Exception.ExceptionRecord.ExceptionCode;
                        signal = true;
                    } else {
                        handled = false;
                    }
                    break;
                }
                case CREATE_THREAD_DEBUG_EVENT: {
                    CloseHandle(de.u.CreateThread.hThread);
                    break;
                }
                case CREATE_PROCESS_DEBUG_EVENT: {
                    CloseHandle(de.u.CreateProcessInfo.hFile);

                    processes++;
                    if (processes > 1 && !(ip->flags & INVOKE_ALLOW_CREATE_PROCESSES)) {
                        signal = true;
                        ir->outcome = SECURITY_VIOLATION;
                        ir->comment = _strdup(TEXT("Child process created"));
                    }
                    break;
                }
                case EXIT_THREAD_DEBUG_EVENT: {
                    break;
                }
                case LOAD_DLL_DEBUG_EVENT: {
                    CloseHandle(de.u.LoadDll.hFile);
                    break;
                }
                case UNLOAD_DLL_DEBUG_EVENT: {
                    break;
                }
                case EXIT_PROCESS_DEBUG_EVENT: {
                    processes--;
                    terminated = processes == 0;
                    break;
                }
                default: {
                    cout << "?";
                }
            }
            ContinueDebugEvent(de.dwProcessId, de.dwThreadId, handled ? DBG_CONTINUE : DBG_EXCEPTION_NOT_HANDLED);
        }

        oldTimeConsumed[hits % smoothPeriod] = is.timeConsumed;
        oldTimePassed[hits % smoothPeriod] = is.timePassed;
        int64 justPrevTimePassed = is.timePassed;
        hits++;
        int64 prevTimeConsumed = oldTimeConsumed[0];
        int64 prevTimePassed = oldTimePassed[0];
        if (hits >= smoothPeriod) {
            prevTimeConsumed = oldTimeConsumed[hits % smoothPeriod];
            prevTimePassed = oldTimePassed[hits % smoothPeriod];
        }

        getProcessTimeInfo(pi.hProcess, false, is.timeConsumed, is.timePassed);
        getProcessMemoryInfo(pi.hProcess, is.currentMemoryConsumed, is.peakMemoryConsumed);
        if (is.timePassed != prevTimePassed) {
            is.processorLoad = (is.timeConsumed - prevTimeConsumed) * 1.0 /
                (is.timePassed - prevTimePassed);
        }

        if (is.processorLoad < ip->requiredProcessorLoad)
        {
            is.state = IDLE;
            is.idlenessPeriod += is.timePassed - justPrevTimePassed;
            if (ip->idlenessLimit > 0 &&
                is.idlenessPeriod > ip->idlenessLimit)
            {
                signal = true;
                ir->outcome = IDLENESS_LIMIT_EXCEEDED;
            }
        } else {
            if (is.state == IDLE) {
                is.state = RUNNING;
            }
            is.idlenessPeriod = 0;
        }

        if (ip->timeLimit > 0 && is.timeConsumed > ip->timeLimit)
        {
            signal = true;
            ir->outcome = TIME_LIMIT_EXCEEDED;
        }
        if (ip->memoryLimit > 0 && is.peakMemoryConsumed > ip->memoryLimit)
        {
            signal = true;
            ir->outcome = MEMORY_LIMIT_EXCEEDED;
        }

        if (callback != NULL) {
            if ((*callback)(&is) && !signal) {
                signal = true;
                ir->outcome = USER_TERMINATED;
                ir->comment = _strdup(TEXT("Forced to terminate by callack"));
            }
        }

        if (signal && !signalled && !terminated) {
            signalled = true;
            TerminateProcess(pi.hProcess, 0);
        }
    }

    is.state = TERMINATING;

    while (WaitForSingleObject(pi.hProcess, interval) == WAIT_TIMEOUT) {
        if (callback != NULL) {
            (*callback)(&is);
        }
    }

    is.state = TERMINATED;
    getProcessTimeInfo(pi.hProcess, true, is.timeConsumed, is.timePassed);
    getProcessMemoryInfo(pi.hProcess, is.currentMemoryConsumed, is.peakMemoryConsumed);
    GetExitCodeProcess(pi.hProcess, &ir->exitCode);

    if (callback != NULL) {
        (*callback)(&is);
    }

    ir->timeConsumed = is.timeConsumed;
    ir->timePassed = is.timePassed;
    ir->peakMemoryConsumed = is.peakMemoryConsumed;

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    ir->forcedToTerminate = signalled;

    closeStandardHandles(standardHandles);

    return;
}

__declspec(dllexport)
void invoke(
    InvocationRequest* ip,
    InvocationResult* ir,
    InvocationCallback callback)
{
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = true;

    memset(ir, 0, sizeof(*ir));

    bool redirectStandardStreams = (
        ip->inputFileName != NULL ||
        ip->outputFileName != NULL ||
        ip->errorFileName != NULL);

    StandardHandles* standardHandles = NULL;
    if (redirectStandardStreams) {
        standardHandles = new StandardHandles();
        if (!openStandardHandles(ip, redirectStandardStreams, standardHandles, &sa)) {
            ir->outcome = FAIL;
            ir->comment = getErrorDescription("OpenStandardHandles", GetLastError());
            closeStandardHandles(standardHandles);
            return;
        }
    }
    invokeWithHandles(ip, ir, callback, standardHandles);
}
