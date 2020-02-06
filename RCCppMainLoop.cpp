#include "ObjectInterfacePerModule.h"
#include "IObject.h"
#include "RCCppMainLoop.h"
#include "SystemTable.h"


// RCC++ uses interface Id's to distinguish between different classes
// here we have only one, so we don't need a header for this enum and put it in the same
// source code file as the rest of the code
enum InterfaceIDEnumConsoleExample
{
    IID_IRCCPP_MAIN_LOOP = IID_ENDInterfaceID, // IID_ENDInterfaceID from IObject.h InterfaceIDEnum

    IID_ENDInterfaceIDEnumConsoleExample
};

struct RCCppMainLoop : RCCppMainLoopI, TInterface<IID_IRCCPP_MAIN_LOOP,IObject>
{
    RCCppMainLoop()
    {
        PerModuleInterface::g_pSystemTable->pRCCppMainLoopI = this;
    }

    void MainLoop() override
    {
    }
};

REGISTERSINGLETON(RCCppMainLoop,true);
