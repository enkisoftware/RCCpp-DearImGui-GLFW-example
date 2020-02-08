#pragma once

#include "RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE; //recompile runtime files when this changes

#include "ObjectInterfacePerModule.h"

struct RCCppMainLoopI;
struct ImGuiContext;
struct IRuntimeObjectSystem;

static SystemTable*& g_pSys  = PerModuleInterface::g_pSystemTable;

struct SystemTable
{
    RCCppMainLoopI* pRCCppMainLoopI            = 0;
    ImGuiContext*   pImContext                 = 0;
    IRuntimeObjectSystem* pRuntimeObjectSystem = NULL;
    bool power_save                            = true;
};
