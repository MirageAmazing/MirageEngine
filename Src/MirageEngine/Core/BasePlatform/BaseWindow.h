#pragma once

#include "../HAL/Platform.h"

// Show mode of Window 
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

// Description of Window.
struct WindowDescription
{
    float PositionX = 0;
    float PositionY = 0;
    int32 Width = 800;
    int32 Height = 600;

    bool HasOSWindowBorder = true;
	bool AppearsInTaskbar = true;
	bool IsTopmostWindow = true;
	bool AcceptsInput = true;
	bool ActivateWhenFirstShown = true;

	bool HasCloseButton = true;
	bool SupportsMinimize = true;
	bool SupportsMaximize = true;

	bool IsModalWindow = false;
	bool SizeWillChangeOften = true;
	int32 ExpectedMaxWidth = 1920;
	int32 ExpectedMaxHeight = 1080;

	CHAR8* Title = "NoTitle";
};

// Base define for behaviour of MirgaeEngine's window 
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