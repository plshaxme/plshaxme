#include <3ds.h>

#include "filesystem.h"
#include "boot.h"

// handled in main
// doing it in main is preferred because execution ends in launching another 3dsx
void __appInit()
{
}

// same
void __appExit()
{
}

int main()
{
    srvInit();
    aptInit();
    initFilesystem();
    openSDArchive();

    // offset potential issues caused by homebrew that just ran
    aptOpenSession();
    APT_SetAppCpuTimeLimit(NULL, 0);
    aptCloseSession();

    char *execPath;

    execPath = "/hpls/installer.3dsx";
    }

    // cleanup whatever we have to cleanup
    hidExit();
    exitFilesystem();
    closeSDArchive();
    aptExit();
    srvExit();

    // wait some time to improve boot chance in CFWs
    svcSleepThread(5000000ULL);

    // run application
    return bootApp(execPath);
}
