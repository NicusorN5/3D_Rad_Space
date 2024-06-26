#pragma once
#include "IControl.hpp"

class NumericTextbox : public IControl
{
    static WNDPROC editProc;
public:
    NumericTextbox(HWND owner, HINSTANCE hInstance, int x, int y, int cx, int cy, const char* value);

    operator HWND() const;

    virtual void HandleClick(HWND clickedWindow) override;

    friend LRESULT WINAPI NumericTextBoxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

