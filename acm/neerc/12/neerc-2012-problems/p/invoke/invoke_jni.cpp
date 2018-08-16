#define INVOKE_EXPORTS

#include "invoke.h"
#include "error.h"

#include "jni.h"

#include <iostream>
using namespace std;

char* getJavaString(JNIEnv* env, jobject object, jclass, jfieldID field) {
    jstring string = static_cast<jstring>(env->GetObjectField(object, field));
    if (string != NULL) {
        const char *buffer = env->GetStringUTFChars(string, NULL);
        char *result = _strdup(buffer);
        env->ReleaseStringUTFChars(string, buffer);
        return result;
    } else {
        return NULL;
    }
}

struct JNIData {
    jclass ip_class;
    jfieldID ip_program;
    jfieldID ip_arguments;
    jfieldID ip_directory;
    jfieldID ip_login;
    jfieldID ip_password;
    jfieldID ip_timeLimit;
    jfieldID ip_memoryLimit;
    jfieldID ip_idlenessLimit;
    jfieldID ip_requiredProcessorLoad;
    jfieldID ip_inputFileName;
    jfieldID ip_outputFileName;
    jfieldID ip_errorFileName;
    jfieldID ip_flags;
    jfieldID ip_environment;

    jclass ir_class;
    jmethodID ir_init;
    jfieldID ir_outcome;
    jfieldID ir_forcedToTerminate;
    jfieldID ir_comment;
    jfieldID ir_exitCode;
    jfieldID ir_exceptionCode;
    jfieldID ir_timeConsumed;
    jfieldID ir_timePassed;
    jfieldID ir_peakMemoryConsumed;

    jclass is_class;
    jmethodID is_init;
    jfieldID is_state;
    jfieldID is_timeConsumed;
    jfieldID is_timePassed;
    jfieldID is_currentMemoryConsumed;
    jfieldID is_peakMemoryConsumed;
    jfieldID is_processorLoad;
    jfieldID is_idlenessPeriod;

    jclass ic_class;
    jmethodID ic_callback;

    jclass no_class;
    jfieldID no_success;
    jfieldID no_time_limit_exceeded;
    jfieldID no_memory_limit_exceeded;
    jfieldID no_crash;
    jfieldID no_idleness_limit_exceeded;
    jfieldID no_security_violation;
    jfieldID no_fail;
    jfieldID no_user_terminated;

    jclass ps_class;
    jfieldID ps_preparing;
    jfieldID ps_failed_to_invoke;
    jfieldID ps_running;
    jfieldID ps_crashed;
    jfieldID ps_idle;
    jfieldID ps_terminating;
    jfieldID ps_terminated;

    jclass map_class;
    jmethodID map_key_set;
    jmethodID map_size;
    jmethodID map_get;

    jclass set_class;
    jmethodID set_iterator;

    jclass iterator_class;
    jmethodID iterator_has_next;
    jmethodID iterator_next;

    JNIData(JNIEnv* env) {
        ip_class = env->FindClass("invoke/NativeInvokeRequest");
        ip_program =
          env->GetFieldID(ip_class, "program", "Ljava/lang/String;");
        ip_arguments =
          env->GetFieldID(ip_class, "arguments", "[Ljava/lang/String;");
        ip_directory =
          env->GetFieldID(ip_class, "directory", "Ljava/lang/String;");
        ip_login =
          env->GetFieldID(ip_class, "login", "Ljava/lang/String;");
        ip_password =
          env->GetFieldID(ip_class, "password", "Ljava/lang/String;");
        ip_timeLimit =
          env->GetFieldID(ip_class, "timeLimit", "J");
        ip_memoryLimit =
          env->GetFieldID(ip_class, "memoryLimit", "J");
        ip_idlenessLimit =
          env->GetFieldID(ip_class, "idlenessLimit", "J");
        ip_requiredProcessorLoad =
          env->GetFieldID(ip_class, "requiredProcessorLoad", "D");
        ip_flags =
          env->GetFieldID(ip_class, "flags", "I");
        ip_inputFileName =
          env->GetFieldID(ip_class, "inputFileName", "Ljava/lang/String;");
        ip_outputFileName =
          env->GetFieldID(ip_class, "outputFileName", "Ljava/lang/String;");
        ip_errorFileName =
          env->GetFieldID(ip_class, "errorFileName", "Ljava/lang/String;");
        ip_environment =
          env->GetFieldID(ip_class, "environment", "Ljava/util/Map;");

        ir_class = env->FindClass("invoke/NativeInvokeResult");
        ir_init = env->GetMethodID(ir_class, "<init>",
          "(Linvoke/NativeOutcome;Ljava/lang/String;ZIIJJJ)V");
        ir_outcome =
          env->GetFieldID(ir_class, "outcome", "Linvoke/NativeOutcome;");
        ir_comment =
          env->GetFieldID(ir_class, "comment", "Ljava/lang/String;");
        ir_forcedToTerminate =
          env->GetFieldID(ir_class, "forcedToTerminate", "Z");
        ir_timeConsumed =
          env->GetFieldID(ir_class, "timeConsumed", "J");
        ir_timePassed =
          env->GetFieldID(ir_class, "timePassed", "J");
        ir_peakMemoryConsumed =
          env->GetFieldID(ir_class, "peakMemoryConsumed", "J");
        ir_exitCode =
          env->GetFieldID(ir_class, "exitCode", "I");
        ir_exceptionCode =
          env->GetFieldID(ir_class, "exceptionCode", "I");

        is_class = env->FindClass("invoke/NativeInvokeStatus");
        is_init = env->GetMethodID(is_class, "<init>",
            "(Linvoke/ProcessState;JJJJJD)V");
        is_state =
          env->GetFieldID(is_class, "state", "Linvoke/ProcessState;");
        is_timeConsumed =
          env->GetFieldID(is_class, "timeConsumed", "J");
        is_timePassed =
          env->GetFieldID(is_class, "timePassed", "J");
        is_currentMemoryConsumed =
          env->GetFieldID(is_class, "currentMemoryConsumed", "J");
        is_peakMemoryConsumed =
          env->GetFieldID(is_class, "peakMemoryConsumed", "J");
        is_processorLoad =
          env->GetFieldID(is_class, "processorLoad", "D");
        is_idlenessPeriod =
          env->GetFieldID(is_class, "idlenessPeriod", "J");

        no_class = env->FindClass("invoke/NativeOutcome");
        no_success = env->GetStaticFieldID(no_class,
            "SUCCESS", "Linvoke/NativeOutcome;");
        no_time_limit_exceeded = env->GetStaticFieldID(no_class,
            "TIME_LIMIT_EXCEEDED", "Linvoke/NativeOutcome;");
        no_memory_limit_exceeded = env->GetStaticFieldID(no_class,
            "MEMORY_LIMIT_EXCEEDED", "Linvoke/NativeOutcome;");
        no_crash = env->GetStaticFieldID(no_class,
            "CRASH", "Linvoke/NativeOutcome;");
        no_idleness_limit_exceeded = env->GetStaticFieldID(no_class,
            "IDLENESS_LIMIT_EXCEEDED", "Linvoke/NativeOutcome;");
        no_security_violation = env->GetStaticFieldID(no_class,
            "SECURITY_VIOLATION", "Linvoke/NativeOutcome;");
        no_fail = env->GetStaticFieldID(no_class,
            "FAIL", "Linvoke/NativeOutcome;");
        no_user_terminated = env->GetStaticFieldID(no_class,
            "USER_TERMINATED", "Linvoke/NativeOutcome;");

        ic_class = env->FindClass("invoke/NativeInvokeCallback");
        ic_callback =
          env->GetMethodID(ic_class, "reportStatus", "(Linvoke/NativeInvokeStatus;)Z");

        ps_class = env->FindClass("invoke/ProcessState");
        ps_preparing = env->GetStaticFieldID(ps_class,
            "PREPARING", "Linvoke/ProcessState;");
        ps_failed_to_invoke = env->GetStaticFieldID(ps_class,
            "FAILED_TO_INVOKE", "Linvoke/ProcessState;");
        ps_running = env->GetStaticFieldID(ps_class,
            "RUNNING", "Linvoke/ProcessState;");
        ps_crashed = env->GetStaticFieldID(ps_class,
            "CRASHED", "Linvoke/ProcessState;");
        ps_idle = env->GetStaticFieldID(ps_class,
            "IDLE", "Linvoke/ProcessState;");
        ps_terminating = env->GetStaticFieldID(ps_class,
            "TERMINATING", "Linvoke/ProcessState;");
        ps_terminated = env->GetStaticFieldID(ps_class,
            "TERMINATED", "Linvoke/ProcessState;");

        map_class = env->FindClass("java/util/Map");
        map_key_set = env->GetMethodID(map_class, "keySet", "()Ljava/util/Set;");
        map_size = env->GetMethodID(map_class, "size", "()I");
        map_get = env->GetMethodID(map_class, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");

        set_class = env->FindClass("java/util/Set");
        set_iterator = env->GetMethodID(set_class, "iterator", "()Ljava/util/Iterator;");

        iterator_class = env->FindClass("java/util/Iterator");
        iterator_has_next = env->GetMethodID(iterator_class, "hasNext", "()Z");
        iterator_next = env->GetMethodID(iterator_class, "next", "()Ljava/lang/Object;");
    }
};

typedef struct {
    JNIEnv *env;
    JNIData* data;
    jobject callbackObject;
} JavaCallback;

bool jniCallbackWrapper(InvocationStatus* is) {
    JavaCallback* jc = static_cast<JavaCallback*>(is->userInfo);
    JNIEnv* env = jc->env;
    JNIData& d = *(jc->data);

    jobject process_status;
    switch (is->state) {
        case PREPARING:
            process_status = env->GetStaticObjectField(d.ps_class, d.ps_preparing);
            break;
        case FAILED_TO_INVOKE:
            process_status = env->GetStaticObjectField(d.ps_class, d.ps_failed_to_invoke);
            break;
        case RUNNING:
            process_status = env->GetStaticObjectField(d.ps_class, d.ps_running);
            break;
        case CRASHED:
            process_status = env->GetStaticObjectField(d.ps_class, d.ps_crashed);
            break;
        case IDLE:
            process_status = env->GetStaticObjectField(d.ps_class, d.ps_idle);
            break;
        case TERMINATING:
            process_status = env->GetStaticObjectField(d.ps_class, d.ps_terminating);
            break;
        case TERMINATED:
            process_status = env->GetStaticObjectField(d.ps_class, d.ps_terminated);
            break;
        default:
            process_status = NULL;
            cout << "?!";
    }

    jobject invocationStatus = env->NewObject(d.is_class, d.is_init,
        process_status, is->timeConsumed, is->timePassed, is->currentMemoryConsumed, is->peakMemoryConsumed,
        is->idlenessPeriod, is->processorLoad);


    jboolean result = env->CallBooleanMethod(jc->callbackObject, d.ic_callback, invocationStatus);

    return result ? true : false;
}

char* getErrorDescription(int error, ...);

extern "C"
__declspec(dllexport)
jobject Java_invoke_NativeInvoke_invoke(
    JNIEnv* env,
    jobject,
    jobject request,
    jobject callback)
{

    JNIData d(env);

    InvocationRequest ip;
    InvocationResult ir;

    ip.program = getJavaString(env, request, d.ip_class, d.ip_program);
    jobjectArray js_arguments = (jobjectArray) env->GetObjectField(request, d.ip_arguments);
    if (js_arguments == NULL) {
        ip.argc = 0;
    } else {
        ip.argc = env->GetArrayLength(js_arguments);
        if (ip.argc > 0) {
            ip.argv = new char*[ip.argc];
            for (int i = 0; i < ip.argc; i++) {
                jstring arg = static_cast<jstring>(env->GetObjectArrayElement(js_arguments, i));
                const char *buffer = env->GetStringUTFChars(arg, NULL);
                ip.argv[i] = _strdup(buffer);
                env->ReleaseStringUTFChars(arg, buffer);
            }
        }
    }
    ip.directory = getJavaString(env, request, d.ip_class, d.ip_directory);
    jobject j_environment = env->GetObjectField(request, d.ip_environment);
    if (j_environment == NULL) {
        ip.environment = NULL;
    } else {
        int nenv = env->CallIntMethod(j_environment, d.map_size);
        jobject key_set = env->CallObjectMethod(j_environment, d.map_key_set);
        jobject key_set_iterator = env->CallObjectMethod(key_set, d.set_iterator);

        char** evars = new char*[nenv];
        size_t estrlen = 0;
        int ind = 0;
        while (env->CallBooleanMethod(key_set_iterator, d.iterator_has_next)) {
            jstring j_key = static_cast<jstring>(env->CallObjectMethod(key_set_iterator, d.iterator_next));
            const char *key = env->GetStringUTFChars(j_key, NULL);
            jstring j_value = static_cast<jstring>(env->CallObjectMethod(j_environment, d.map_get, j_key));
            const char *value = env->GetStringUTFChars(j_value, NULL);
            size_t klen = strlen(key);
            size_t vlen = strlen(value);
            evars[ind] = (char*) malloc(klen + 1 + vlen + 1);
            strcpy(evars[ind], key);
            evars[ind][klen] = '=';
            strcpy(evars[ind] + klen + 1, value);
            estrlen += (klen + 1 + vlen + 1);
            ind++;
            env->ReleaseStringUTFChars(j_key, key);
            env->ReleaseStringUTFChars(j_value, value);
        }
        ip.environment = (char*) malloc(estrlen + 1);
        char* p = ip.environment;
        for (int i = 0; i < nenv; i++) {
            p = strcpy(p, evars[i]) + strlen(evars[i]) + 1;
            free(evars[i]);
        }
        delete[] evars;
        *p = 0;
    }
    ip.login = getJavaString(env, request, d.ip_class, d.ip_login);
    ip.password = getJavaString(env, request, d.ip_class, d.ip_password);
    ip.timeLimit = env->GetLongField(request, d.ip_timeLimit);
    ip.memoryLimit = env->GetLongField(request, d.ip_memoryLimit);
    ip.idlenessLimit = env->GetLongField(request, d.ip_idlenessLimit);
    ip.requiredProcessorLoad = env->GetDoubleField(request, d.ip_requiredProcessorLoad);
    ip.flags = env->GetIntField(request, d.ip_flags);
    ip.inputFileName = getJavaString(env, request, d.ip_class, d.ip_inputFileName);
    ip.outputFileName = getJavaString(env, request, d.ip_class, d.ip_outputFileName);
    ip.errorFileName = getJavaString(env, request, d.ip_class, d.ip_errorFileName);

    if (callback == NULL) {
        invoke(&ip, &ir, NULL);
    } else {
        JavaCallback* jcb = new JavaCallback();

        jcb->env = env;
        jcb->data = &d;
        jcb->callbackObject = callback;

        ip.userInfo = jcb;

        invoke(&ip, &ir, jniCallbackWrapper);

        delete jcb;
    }

    jobject outcome;
    switch (ir.outcome) {
        case SUCCESS:
            outcome = env->GetStaticObjectField(d.no_class, d.no_success);
            break;
        case TIME_LIMIT_EXCEEDED:
            outcome = env->GetStaticObjectField(d.no_class, d.no_time_limit_exceeded);
            break;
        case MEMORY_LIMIT_EXCEEDED:
            outcome = env->GetStaticObjectField(d.no_class, d.no_memory_limit_exceeded);
            break;
        case CRASH:
            outcome = env->GetStaticObjectField(d.no_class, d.no_crash);
            break;
        case IDLENESS_LIMIT_EXCEEDED:
            outcome = env->GetStaticObjectField(d.no_class, d.no_idleness_limit_exceeded);
            break;
        case SECURITY_VIOLATION:
            outcome = env->GetStaticObjectField(d.no_class, d.no_security_violation);
            break;
        case USER_TERMINATED:
            outcome = env->GetStaticObjectField(d.no_class, d.no_user_terminated);
            break;
        default:
            outcome = env->GetStaticObjectField(d.no_class, d.no_fail);
            break;
    }

    jstring comment = NULL;
    if (ir.comment != NULL) {
        comment = env->NewStringUTF(ir.comment);
        free(ir.comment);
    }

    if (ir.outcome == CRASH) {
        char* buffer = getExceptionName(ir.exceptionCode);
        comment = env->NewStringUTF(buffer);
        free(buffer);
    }

    jobject result = env->NewObject(d.ir_class, d.ir_init,
        outcome, comment, ir.forcedToTerminate, ir.exitCode, ir.exceptionCode,
        ir.timeConsumed, ir.timePassed, ir.peakMemoryConsumed);

    if (ip.program != NULL) free(ip.program);
    if (ip.argc > 0) {
        for (int i = 0; i < ip.argc; i++) {
            free(ip.argv[i]);
        }
        delete[] ip.argv;
    }
    if (ip.directory != NULL) free(ip.directory);
    if (ip.login != NULL) free(ip.login);
    if (ip.password != NULL) free(ip.password);
    if (ip.inputFileName != NULL) free(ip.inputFileName);
    if (ip.outputFileName != NULL) free(ip.outputFileName);
    if (ip.errorFileName != NULL) free(ip.errorFileName);

    return result;
}
