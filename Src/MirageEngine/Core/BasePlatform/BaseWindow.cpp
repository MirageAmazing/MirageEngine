#include "BaseWindow.h"

BaseWindow::BaseWindow()
{

}
BaseWindow::~BaseWindow()
{

}

void BaseWindow::Destory()
{

}
void BaseWindow::Minimize()
{

}
void BaseWindow::Maximize()
{

}
void BaseWindow::Show()
{

}
void BaseWindow::Hide()
{

}
void BaseWindow::Resize(int32 width, int32 height)
{

}
void BaseWindow::MoveTo(int32 x, int32 y)
{

}
void BaseWindow::GotoFront(bool bForce)
{

}

bool BaseWindow::GetFullScreenInfo(int32& x, int32 y, int32& width, int32 height) const
{
    // some platform don't need fullscreeninfo, such as consles, etc.
    return false;
}
eWindowMode BaseWindow::GetWindowMode() const
{
    return mWindowMode;
}
bool BaseWindow::IsMaximized() const
{
    return false;
}
bool BaseWindow::IsMinimized() const
{
    return false;
}
bool BaseWindow::IsVisible() const
{
    return false;
}
bool BaseWindow::IsPointInWindow(int32 x, int32 y) const
{
    return false;
}

void BaseWindow::SetWindowMode(eWindowMode mode)
{
    mWindowMode = mode;
}
void BaseWindow::SetFocus()
{
    
}