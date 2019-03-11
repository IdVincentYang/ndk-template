#include "pal-log.hxx"

#include <cstdarg>
#include <android/log.h>

#define _IMP_LOG(lower, upper) \
void pal::log_##lower(const char *tag, const char *format, ...){ \
    std::va_list va; \
    va_start(va, format); \
    __android_log_vprint(ANDROID_LOG_##upper, tag, format, va); \
    va_end(va); \
}

_IMP_LOG(verbose, VERBOSE)
_IMP_LOG(debug, DEBUG)
_IMP_LOG(info, INFO)
_IMP_LOG(warn, WARN)
_IMP_LOG(error, ERROR)
_IMP_LOG(fatal, FATAL)
