#include <windows.h>

#pragma data_seg("FuckLogitech")
int pid = 0;
#pragma data_seg()
#pragma comment(linker,"/SECTION:FuckLogitech,RWS")

LRESULT CALLBACK MouseWheel(int nCode, WPARAM wParam, LPARAM lParam)
{
	int wData;
	if (nCode >= 0 && wParam == WM_MOUSEWHEEL)
	{
		wData = (int)(((MSLLHOOKSTRUCT *)lParam)->mouseData);
		if (wData > 0)
		{
			keybd_event(VK_VOLUME_UP, 0, 0, 0);
		}
		else
		{
			keybd_event(VK_VOLUME_DOWN, 0, 0, 0);
		}
		return true;
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (pid > 0)
	{
		HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
		TerminateProcess(hProcess, 0);
		return 0;
	}
	pid = GetCurrentProcessId();

	SetWindowsHookEx(
		WH_MOUSE_LL,
		MouseWheel,
		hInstance,
		NULL
	);
	keybd_event(VK_VOLUME_UP, 0, 0, 0);
	keybd_event(VK_VOLUME_DOWN, 0, 0, 0);

	MSG Msg;
	GetMessage(&Msg, NULL, 0, 0);
	return 0;
}