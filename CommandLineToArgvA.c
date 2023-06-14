#include "commandLineToArgv.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <windows.h>


/*************************************************************************
 * CommandLineToArgvA
 *
 * https://github.com/ola-ct/actilog/blob/master/actiwin/CommandLineToArgvA.cpp
 */
char ** CommandLineToArgvA_ola(char * CmdLine, int *_argc) {
    PCHAR *argv;
    PCHAR _argv;
    ULONG len;
    ULONG argc;
    char ch;
    ULONG i, j;

    BOOLEAN in_QM;
    BOOLEAN in_TEXT;
    BOOLEAN in_SPACE;

    assert(CmdLine != NULL);
    assert(_argc != NULL);

    if (_argc != NULL) {
        (*_argc) = 0;
    }

    if (CmdLine == NULL || _argc == NULL) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    len = strlen(CmdLine);
    i = ((len + 2) / 2) * sizeof(PVOID) + sizeof(PVOID);

    argv = (PCHAR *)LocalAlloc(LMEM_FIXED, i + (len + 2) * sizeof(char));
    assert(argv != NULL);

    if (argv == NULL) {
        return NULL;
    }

    _argv = (PCHAR)(((PUCHAR)argv) + i);

    argc = 0;
    argv[argc] = _argv;
    in_QM = FALSE;
    in_TEXT = FALSE;
    in_SPACE = TRUE;
    i = 0;
    j = 0;

    while ((ch = CmdLine[i]) != '\0') {
        if (in_QM) {
            if (ch == '\"') {
                in_QM = FALSE;
            } else {
                _argv[j] = ch;
                j++;
            }
        } else {
            switch (ch) {
            case '\"':
                in_QM = TRUE;
                in_TEXT = TRUE;
                if (in_SPACE) {
                    argv[argc] = _argv + j;
                    argc++;
                }
                in_SPACE = FALSE;
                break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                if (in_TEXT) {
                    _argv[j] = '\0';
                    j++;
                }
                in_TEXT = FALSE;
                in_SPACE = TRUE;
                break;
            default:
                in_TEXT = TRUE;
                if (in_SPACE) {
                    argv[argc] = _argv + j;
                    argc++;
                }
                _argv[j] = ch;
                j++;
                in_SPACE = FALSE;
                break;
            }
        }
        i++;
    }
    _argv[j] = '\0';
    argv[argc] = NULL;

    (*_argc) = (int)argc;
    return argv;
}

