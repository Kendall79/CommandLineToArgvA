/* Test CommandLineToArgv macro funtion for C */

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>
#include "CommandLineToArgv.h"


int _tmain() {
    int argc = 0;
    LPTSTR* argv;

    //_tsetlocale(LOCALE_ALL, _T("C"));
    argv = CommandLineToArgv(GetCommandLine(), &argc);

    if (argv != NULL) {
        int i;
        for (i = 0; i < argc; i++) {
            _tprintf(_T("argv[%d] = %s\n"), i + 1, argv[i]);
        }
        _tprintf(_T("\n"));
        for (i = 0; i < argc; i++) {
            _tprintf(_T("argument %d: %s\n"), i + 1, argv[i]);
        }
        LocalFree(argv);
    }
    return 0;
}

