#pragma once

/**
 *Platform application interface
 */
class BaseApplication
{
  public:
    BaseApplication() {}
    virtual ~BaseApplication() {}

    virtual void Tick(float deltaTime){}
};