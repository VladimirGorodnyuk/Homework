#include <windows.h>
#include <tchar.h>
#include <time.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Timer");

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
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Работа с таймером"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}
int shagY=1, shagX=1;
VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	RECT r;
	GetWindowRect(hWnd, &r);
	int x1 = r.left, y1 = r.top, width = r.right - r.left, height = r.bottom - r.top;
	int R = (GetSystemMetrics(SM_CXSCREEN) - width);//правый край
	int D = (GetSystemMetrics(SM_CYSCREEN) - height);//низ
	if (y1 == D)
		shagY = -1;
	if (x1 == R)
		shagX = -1;
	if (y1 == 0)
		shagY = 1;
	if (x1 == 0)
		shagX = 1;
	MoveWindow(hWnd, x1 + shagX, y1 + shagY, width, height, true);
	/*time_t t;
	TCHAR str[100];
	t = time(NULL);
	lstrcpy(str, _tctime(&t));
	str[lstrlen(str) - 1] = '\0';
	SetWindowText(hWnd, str);*/

	/*int shag = 1;
	if ((x1<(GetSystemMetrics(SM_CXSCREEN) - width)) && x1 != 0 && (y1 != (GetSystemMetrics(SM_CYSCREEN) - height)))
	MoveWindow(hWnd, (x1 + shag), y1, width, height, true);
	else if ((x1 == (GetSystemMetrics(SM_CXSCREEN) - width)) && (y1 != (GetSystemMetrics(SM_CYSCREEN) - height)))
	MoveWindow(hWnd, x1, y1 + shag, width, height, true);
	else if (y1 == GetSystemMetrics(SM_CYSCREEN) - height&&x1 != 0)
	MoveWindow(hWnd, x1 - shag, y1, width, height, true);
	else if (x1 == 0 && y1 != 0)
	MoveWindow(hWnd, x1, y1 - shag, width, height, true);
	else if (x1<GetSystemMetrics(SM_CXSCREEN) - width&&x1 >= 0 && (y1 != GetSystemMetrics(SM_CYSCREEN) - height || y1 == 0))
	MoveWindow(hWnd, (x1 + shag), y1, width, height, true);*/
}

//if (parseInt(ball.style.left) <= 0 || parseInt(ball.style.left) >= 450)
//x = -x;
//if ((parseInt(ball.style.top) <= 0 && parseInt(ball.style.left) + 400 >= parseInt(block.style.left) && parseInt(ball.style.left) + 400 <= parseInt(block.style.left) + 100) || parseInt(ball.style.top) >= 550)
//y = -y;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
			SetTimer(hWnd, 1, 1, TimerProc);
		else if (wParam == VK_ESCAPE)
			KillTimer(hWnd, 1);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
