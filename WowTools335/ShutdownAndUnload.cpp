#include "Warden.h"
#include "WardenHelpers.h"
#include <iostream>


Warden::ShutdownAndUnloadtype Warden::OriginalShutdownAndUnload = (Warden::ShutdownAndUnloadtype)0x08dA420;

// Custom implementation of ShutdownAndUnload
int Warden::ShutdownAndUnload()
{

    printf("ShutdownAndUnload ran\n");
    Warden::Clear();
    return OriginalShutdownAndUnload();
}