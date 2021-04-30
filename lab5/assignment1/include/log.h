#ifndef LOG_H
#define LOG_H

#define DEBUG 5
#define INFO 10
#define ERROR 15

int printf_debug(const char *const fmt, ...);
int printf_error(const char *const fmt, ...);
int printf_info(const char *const fmt, ...);

#endif

