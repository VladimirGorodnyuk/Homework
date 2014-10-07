#include <windows.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatic1;
POINT First;
POINT Second;
int count = 0,countS=0;
TCHAR St[20];
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
			First.x = LOWORD(lParam);
			First.y = HIWORD(lParam);
		}
		if (count == 2)
		{
			Second.x = LOWORD(lParam);
			Second.y = HIWORD(lParam); 
			if (Second.x > First.x&&Second.y > First.y)//первая верхлево вторая низправо
			{
				hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0,
					WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
					First.x, First.y, (Second.x - First.x), (Second.y - First.y), hWnd, 0, hInst, 0);
				wsprintf(St, TEXT("Static%d"), ++countS);
				SetWindowText(hStatic1, St);
				count = 0;
			}
			if (Second.x < First.x&&Second.y < First.y)//первая низправо вторая верхлево
			{
				hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0,
					WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
					Second.x, Second.y, (First.x - Second.x), (First.y - Second.y), hWnd, 0, hInst, 0);
				wsprintf(St, TEXT("Static%d"), ++countS);
				SetWindowText(hStatic1, St);
				count = 0;
			}
			if (Second.x < First.x&&Second.y > First.y)//первая верхправо вторая низлево
			{
				hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0,
					WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
					Second.x, First.y, (First.x - Second.x), (Second.y-First.y), hWnd, 0, hInst, 0);
				wsprintf(St, TEXT("Static%d"), ++countS);
				SetWindowText(hStatic1, St);
				count = 0;
			}
			if (Second.x > First.x&&Second.y < First.y)//первая низлево вторая верхправо
			{
				hStatic1 = CreateWindowEx(0, TEXT("STATIC"), 0,
					WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
					First.x, Second.y, (Second.x - First.x), (First.y - Second.y), hWnd, 0, hInst, 0);
				wsprintf(St, TEXT("Static%d"), ++countS);
				SetWindowText(hStatic1, St);
				count = 0;
			}
		}
		return TRUE;
	}
	return FALSE;
}
