#include <Windows.h>
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));
	WCHAR* str = new wchar_t[200];
	int max = 500;
	int min = 0;
	int num = rand() % max;
	int count = 1;
	wsprintf(str, TEXT("%d"), num);
	int A = MessageBox(NULL, str, TEXT("Попробую угадать число от 0 до 500"), MB_YESNOCANCEL | MB_ICONINFORMATION);
	do{
		if (A == IDYES)
		{
			max = num - 1;
			num = rand() % (max - min) + min;
			wsprintf(str, TEXT("%d"), num);
			A = MessageBox(NULL, str, TEXT("Попробую угадать число от 0 до 500"), MB_YESNOCANCEL | MB_ICONINFORMATION);
		}
		if (A == IDNO)
		{
			min = num + 1;
			num = rand() % (max - min) + min;
			wsprintf(str, TEXT("%d"), num);
			A = MessageBox(NULL, str, TEXT("Попробую угадать число от 0 до 500"), MB_YESNOCANCEL | MB_ICONINFORMATION);
		}
		count++;
	} while (A != IDCANCEL);
	wsprintf(str, TEXT("Число угадано за %d попыток"), count);
	MessageBox(NULL, str, TEXT("Число угадано за ..."), MB_OK | MB_ICONINFORMATION);
	return 0;
}

