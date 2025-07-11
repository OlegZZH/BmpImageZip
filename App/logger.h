#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_LEVEL_DEBUG ""
#define LOGGER_LEVEL_INFO "*.debug=false"
#define LOGGER_LEVEL_WARNING "*.debug=false;*.info=false"
#define LOGGER_LEVEL_CRITICAL "*.debug=false;*.info=false;*.warning=false"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define LOGGER_MESSAGE_LONG_PATTERN \
    "%{if-debug}" ANSI_COLOR_GREEN "%{endif}" \
    "%{if-info}" ANSI_COLOR_BLUE "%{endif}" \
    "%{if-warning}" ANSI_COLOR_YELLOW "%{endif}" \
    "%{if-critical}" ANSI_COLOR_RED "%{endif}" \
    "%{if-fatal}" ANSI_COLOR_MAGENTA "%{endif}" \
    "%{time yyyy-MM-dd h:mm:ss.zzz} [%{type}] file://%{file}:%{line} - " \
    "%{message}" ANSI_COLOR_RESET

#define LOGGER_MESSAGE_SHORT_PATTERN \
    "%{if-debug}" ANSI_COLOR_GREEN "%{endif}" \
    "%{if-info}" ANSI_COLOR_BLUE "%{endif}" \
    "%{if-warning}" ANSI_COLOR_YELLOW "%{endif}" \
    "%{if-critical}" ANSI_COLOR_RED "%{endif}" \
    "%{if-fatal}" ANSI_COLOR_MAGENTA "%{endif}" \
    "%{time yyyy-MM-dd h:mm:ss} [%{type}] %{message}" ANSI_COLOR_RESET

#ifdef NDEBUG
#define LOG_LEVEL LOGGER_LEVEL_DEBUG
#define LOG_MESSAGE_PATTERN LOGGER_MESSAGE_SHORT_PATTERN
#else
#define LOG_LEVEL LOGGER_LEVEL_DEBUG
#define LOG_MESSAGE_PATTERN LOGGER_MESSAGE_LONG_PATTERN
#endif

#endif // LOGGER_H
