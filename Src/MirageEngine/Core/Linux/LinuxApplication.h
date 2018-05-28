#pragma once

#include "../BasePlatform/BaseApplication.h"

/**
 *Linux application
 */
class LinuxApplication:public BaseApplication
{
public:
    static LinuxApplication* CreateApplication();

public:
    ~LinuxApplication();

	virtual void Tick(float deltaTime) override {
	
	}
private:
    LinuxApplication();
};