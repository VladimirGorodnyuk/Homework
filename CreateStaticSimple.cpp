#include <windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatic1;
POINT LeftTop;
POINT RightDown;
int count = 0;
TCHAR XY[20];
HINSTANCE hInst;

const int LEFT = 15, TOP = 110, WIDTH = 380, HEIGHT = 50;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
		/*hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
			LEFT, TOP, WIDTH, HEIGHT, hWnd, 0, hInst, 0);*/
	case WM_LBUTTONDOWN:
		count++;
		if (count == 1)
		{
			LeftTop.x = LOWORD(lParam);
			LeftTop.y = HIWORD(lParam);
		}
		if (count == 2)
		{
			RightDown.x = LOWORD(lParam);
			RightDown.y = HIWORD(lParam);
			hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0,
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
				LeftTop.x, LeftTop.y, (RightDown.x - LeftTop.x), (RightDown.y - LeftTop.y), hWnd, 0, hInst, 0);
			wsprintf(XY, TEXT("LeftTop.x=%d LeftTop.y=%d RightDown.x=%d RightDown.y=%d"), LeftTop.x, LeftTop.y, RightDown.x, RightDown.y);
			SetWindowText(hStatic1, XY);
			count = 0;
		}
		return TRUE;
	}
	return FALSE;
}
