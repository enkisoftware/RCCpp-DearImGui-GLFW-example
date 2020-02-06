#pragma once

// abstract interface to our RCCppMainLoop class, using I at end to denote Interface
struct RCCppMainLoopI
{
    virtual void MainLoop() = 0;
};
