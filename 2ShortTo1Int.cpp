#include <Windows.h>
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	short X = 28000;
	short Y = 32000;
	int XY = X & 0xffff | ((Y & 0xffff) << 16);
	TCHAR str[50];
	TCHAR str1[50];
	wsprintf(str, TEXT("X=%d  Y=%d"), X, Y);
	wsprintf(str1, TEXT("XY=%d"), XY);
	MessageBox(0,str,str1,MB_OK | MB_ICONINFORMATION);
	X = XY & 0xffff;
	Y = (XY >> 16) & 0xffff;
	wsprintf(str, TEXT("X=%d  Y=%d"), X, Y);
	wsprintf(str1, TEXT("XY=%d"), XY);
	MessageBox(0, str, str1, MB_OK | MB_ICONINFORMATION);
	return 0;
}
