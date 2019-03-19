#pragma once

#define PAL_LOG_LEVEL_ALL       0
#define PAL_LOG_LEVEL_VERBOSE   1
#define PAL_LOG_LEVEL_DEBUG     2
#define PAL_LOG_LEVEL_INFO      3
#define PAL_LOG_LEVEL_WARN      4
#define PAL_LOG_LEVEL_ERROR     5
#define PAL_LOG_LEVEL_FATAL     6
#define PAL_LOG_LEVEL_NONE      PAL_LOG_LEVEL_FATAL

#ifndef PAL_LOG_LEVEL
#define PAL_LOG_LEVEL PAL_LOG_LEVEL_ALL
#endif

#if PAL_LOG_LEVEL_VERBOSE > PAL_LOG_LEVEL
#define PAL_LOG_V(...) pal::log_verbose(__VA_ARGS__)
#else
#define PAL_LOG_V(...)
#endif

#if PAL_LOG_LEVEL_DEBUG > PAL_LOG_LEVEL
#define PAL_LOG_D(...)  pal::log_debug(__VA_ARGS__)
#else
#define PAL_LOG_D(...)
#endif

#if PAL_LOG_LEVEL_INFO > PAL_LOG_LEVEL
#define PAL_LOG_I(...) pal::log_info(__VA_ARGS__)
#else
#define PAL_LOG_I(...)
#endif

#if PAL_LOG_LEVEL_WARN > PAL_LOG_LEVEL
#define PAL_LOG_W(...) pal::log_warn(__VA_ARGS__)
#else
#define PAL_LOG_W(...)
#endif

#if PAL_LOG_LEVEL_ERROR > PAL_LOG_LEVEL
#define PAL_LOG_E(...) pal::log_error(__VA_ARGS__)
#else
#define PAL_LOG_E(...)
#endif

#if PAL_LOG_LEVEL_FATAL > PAL_LOG_LEVEL
#define PAL_LOG_F(...) pal::log_fatal(__VA_ARGS__)
#else
#define PAL_LOG_F(...)
#endif

namespace pal {
    void log_verbose(const char *tag, const char *format, ...);

    void log_debug(const char *tag, const char *format, ...);

    void log_info(const char *tag, const char *format, ...);

    void log_warn(const char *tag, const char *format, ...);

    void log_error(const char *tag, const char *format, ...);

    void log_fatal(const char *tag, const char *format, ...);
}
