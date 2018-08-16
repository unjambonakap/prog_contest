/*
 * Invoke for NT test.
 *   outcome = time_limit_exceeded
 */
#include <windows.h>

__int64 now() {
    SYSTEMTIME current_time_sys;
    FILETIME current_time;
    
    GetSystemTime(&current_time_sys);
    SystemTimeToFileTime(&current_time_sys, &current_time);
    return *(reinterpret_cast<__int64*>(&current_time));
}

int main() {
    __int64 start = now();    
    while (now() - start < 3.0 * 10000 * 1000);
    return 0;
}
