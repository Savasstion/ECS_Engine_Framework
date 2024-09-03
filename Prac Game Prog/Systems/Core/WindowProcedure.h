#ifndef WINDOW_PROC_H
#define WINDOW_PROC_H

#include <windows.h>

// No need for extern here
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // WINDOW_PROC_H