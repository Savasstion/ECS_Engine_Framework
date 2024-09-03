#include "WindowProcedure.h"
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}