#include <windows.h>
#include <stdio.h>

#include <iostream>
using namespace std;

char* getErrorDescription(int error, ...) {
    va_list params;
    va_start(params, error);

    char *buf = 0;
    FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      0,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR) &buf,
      0,
      &params);

    va_end(params);

    char* res = _strdup(buf);

    // Free the buffer
    LocalFree(buf);

    return res;
};

char* getErrorDescription(char* source, int error, ...) {
    va_list params;
    va_start(params, error);

    char *buf = 0;
    FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      0,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR) &buf,
      0,
      &params);

    va_end(params);

    size_t len = strlen(source) + strlen(buf) + 4;
    char* res = (char*) malloc(len);
    sprintf(res, "%s (%s)", buf, source);

    // Free the buffer
    LocalFree(buf);

    return res;
};

char* getExceptionName(int code) {
    char* r;
    switch (code) {
        case EXCEPTION_ACCESS_VIOLATION:
            r = _strdup("EXCEPTION_ACCESS_VIOLATION");
            break;
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            r = _strdup("EXCEPTION_ARRAY_BOUNDS_EXCEEDED");
            break;
        case EXCEPTION_BREAKPOINT:
            r = _strdup("EXCEPTION_BREAKPOINT");
            break;
        case EXCEPTION_DATATYPE_MISALIGNMENT:
            r = _strdup("EXCEPTION_DATATYPE_MISALIGNMENT");
            break;
        case EXCEPTION_FLT_DENORMAL_OPERAND:
            r = _strdup("EXCEPTION_FLT_DENORMAL_OPERAND");
            break;
        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            r = _strdup("EXCEPTION_FLT_DIVIDE_BY_ZERO");
            break;
        case EXCEPTION_FLT_INEXACT_RESULT:
            r = _strdup("EXCEPTION_FLT_INEXACT_RESULT");
            break;
        case EXCEPTION_FLT_INVALID_OPERATION:
            r = _strdup("EXCEPTION_FLT_INVALID_OPERATION");
            break;
        case EXCEPTION_FLT_OVERFLOW:
            r = _strdup("EXCEPTION_FLT_OVERFLOW");
            break;
        case EXCEPTION_FLT_STACK_CHECK:
            r = _strdup("EXCEPTION_FLT_STACK_CHECK");
            break;
        case EXCEPTION_FLT_UNDERFLOW:
            r = _strdup("EXCEPTION_FLT_UNDERFLOW");
            break;
        case EXCEPTION_ILLEGAL_INSTRUCTION:
            r = _strdup("EXCEPTION_ILLEGAL_INSTRUCTION");
            break;
        case EXCEPTION_IN_PAGE_ERROR:
            r = _strdup("EXCEPTION_IN_PAGE_ERROR");
            break;
        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            r = _strdup("EXCEPTION_INT_DIVIDE_BY_ZERO");
            break;
        case EXCEPTION_INT_OVERFLOW:
            r = _strdup("EXCEPTION_INT_OVERFLOW");
            break;
        case EXCEPTION_INVALID_DISPOSITION:
            r = _strdup("EXCEPTION_INVALID_DISPOSITION");
            break;
        case EXCEPTION_NONCONTINUABLE_EXCEPTION:
            r = _strdup("EXCEPTION_NONCONTINUABLE_EXCEPTION");
            break;
        case EXCEPTION_PRIV_INSTRUCTION:
            r = _strdup("EXCEPTION_PRIV_INSTRUCTION");
            break;
        case EXCEPTION_SINGLE_STEP:
            r = _strdup("EXCEPTION_SINGLE_STEP");
            break;
        case EXCEPTION_STACK_OVERFLOW:
            r = _strdup("EXCEPTION_STACK_OVERFLOW");
            break;
        default:
            char buffer[60];
            sprintf(buffer, "EXCEPTION_UNKNOWN: %x", code);
            r = _strdup(buffer);
            break;
    }
    return r;
}