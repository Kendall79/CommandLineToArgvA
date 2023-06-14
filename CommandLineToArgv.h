#ifndef WINDOWS32_PLATFORM_COMMAND_LINE_TO_ARGV_H
#define WINDOWS32_PLATFORM_COMMAND_LINE_TO_ARGV_H

#ifdef __cplusplus
extern "C"
char ** CommandLineToArgvA_ola(char * commandLine, int *argc);
#else
extern
char ** CommandLineToArgvA_ola(char * commandLine, int *argc);
#endif // __cplusplus

/* #define CommandLineToArgv macro */
#if defined(UNICODE)|| defined(_UNICODE)
/* include <Windows.h> */
#define CommandLineToArgv CommandLineToArgvW
#else
#define CommandLineToArgv CommandLineToArgvA_ola
#endif //defined(UNICODE)|| defined(_UNICODE)


#endif // WINDOWS32_PLATFORM_COMMAND_LINE_TO_ARGV_H

