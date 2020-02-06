#pragma once

#include "RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE; //recompile runtime files when this changes

struct RCCppMainLoopI;
struct ImGuiContext;

struct SystemTable
{
    RCCppMainLoopI* pRCCppMainLoopI = 0;
    ImGuiContext*   pImContext      = 0;
};
