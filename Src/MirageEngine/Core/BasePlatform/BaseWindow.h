#pragma once

#include "../HAL/Platform.h"

enum class eWindowMode
{
     // The window is in true fullscreen mode
     FullScreen,
     // The window has no border and takes up the entire area of the screen
     WindowedFullScreen,
     // The window have a border and may not take up the entire screen area
     Windowed,
     // Prepare for devices like HMDs( Helmet mounted display and sight)
     WindowedMirror,

     WindowModesCount
};

class BaseWindow
{
public:
    BaseWindow();
    virtual ~BaseWindow();

    virtual void Destory();
    virtual void Minimize();
    virtual void Maximize();
    virtual void Show();
    virtual void Hide();
    virtual void Resize(int32 width, int32 height);
    virtual void MoveTo(int32 x, int y);
    virtual void GotoFront(bool bForce = false);

    virtual bool GetFullScreenInfo(int32& x, int32 y, int32& width, int32 height) const;
    eWindowMode GetWindowMode() const;
    virtual bool IsMaximized() const;
    virtual bool IsMinimized() const;
    virtual bool IsVisible() const;
    virtual bool IsPointInWindow(int32 x, int32 y) const;

    virtual void SetWindowMode(eWindowMode mode);
    virtual void SetFocus();

protected:
    eWindowMode mWindowMode = eWindowMode::Windowed;
};