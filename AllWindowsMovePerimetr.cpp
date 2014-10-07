#include <windows.h>
#include <vector>
using namespace std;
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Enum Top Level");
vector <HWND> all_windows;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Перечисление окон верхнего уровня"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	/*MessageBox(hWnd, TEXT("Для перечисления окон верхнего уровня нажмите <CTRL>"), TEXT("Перечисление окон верхнего уровня"), MB_OK | MB_ICONINFORMATION);*/

	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	RECT r;
	GetWindowRect(hWnd, &r);
	int width = r.right - r.left, height = r.bottom - r.top;
	if (width > 200 && height > 200)
		all_windows.push_back(hWnd);
	return TRUE; // продолжаем перечисление окон верхнего уровня
}
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	for (int i = 0; i < int(all_windows.size()); i++)
	{
		RECT r;
		HWND hWND = all_windows.at(i);
		GetWindowRect(hWND, &r);
		int x1 = r.left, y1 = r.top, width = r.right - r.left, height = r.bottom - r.top;
		int R = (GetSystemMetrics(SM_CXSCREEN) - width);//правый край
		int D = (GetSystemMetrics(SM_CYSCREEN) - height);//низ
		if (x1 >= R&&y1 < D)
			MoveWindow(hWND, x1, y1 + 1, width, height, true);
		else if (y1 >= D&&x1>0)
			MoveWindow(hWND, x1 - 1, y1, width, height, true);
		else if (x1 <= 0 && y1>0)
			MoveWindow(hWND, x1, y1 - 1, width, height, true);
		else if (y1 <= 0 && x1 < R)
			MoveWindow(hWND, x1 + 1, y1, width, height, true);
		else
			MoveWindow(hWND, x1 + 1, y1, width, height, true);

	}
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		EnumWindows(EnumWindowsProc, (LPARAM)hWnd);
		SetTimer(hWnd, 1, 1, TimerProc);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			KillTimer(hWnd, 1);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
