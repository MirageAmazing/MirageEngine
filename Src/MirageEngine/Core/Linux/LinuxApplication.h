#pragma once

#include "../BasePlatform/BaseApplication"

/**
 *Linux application
 */
class LinuxApplication:public BaseApplication
{
public:
    static LinuxApplication* CreateApplication();

public:
    ~LinuxApplication();

private:
    LinuxApplication();
};