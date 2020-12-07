#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

#ifdef _DEBUG
void Log(const char *message) {
	std::cout << message;
}
#endif

int main()
{
	int session{ 0 };
	const char *procWindow = "Cube 2: Sauerbraten";
	HWND FindProcessWindow = FindWindowA(NULL, procWindow);

	std::cout << "Searching for Cube2: Sauerbraten...\n";

	do
	{

		FindProcessWindow = FindWindowA(NULL, procWindow);;

		if (FindProcessWindow)
		{
			std::cout << "Game found!\n";

			DWORD processId;

			GetWindowThreadProcessId(FindProcessWindow, &processId);

			HANDLE attachToProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);

			if (processId == NULL)
			{
				std::cout << "Cannot obtain process.\n";
			}
			else
			{

				if (attachToProcess)
				{
					std::cout << "Process sucessfully attached!\n";
				}
				else
				{
					std::cout << "Failed to attach the process.";
				}

			}
		}

		session++;
		Sleep(250);

	} while (FindProcessWindow == NULL && session <= 500);

	if (session > 500)
	{
		std::cout << "Session expired.\n";
	}
}

