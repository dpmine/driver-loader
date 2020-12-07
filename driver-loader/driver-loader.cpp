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
	DWORD Ammo = 0x157F6E3BFA4;
	int newAmmo = 500;


	std::cout << "Searching for Cube2: Sauerbraten...\n";

	do
	{

		FindProcessWindow = FindWindowA(NULL, procWindow);;

		if (FindProcessWindow)
		{
			std::cout << "Game found!\n";

			DWORD processId;

			GetWindowThreadProcessId(FindProcessWindow, &processId);

			HANDLE pAttach = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);

			if (processId == NULL)
			{
				std::cout << "Cannot obtain process.\n";
			}
			else
			{

				if (pAttach)
				{
					std::cout << "Process sucessfully attached!\n";
					bool memWrite = WriteProcessMemory(pAttach, (LPVOID)Ammo, &newAmmo, sizeof(newAmmo), 0);
					if (memWrite) {
						std::cout << "Memory writed.\n";
						Sleep(5000);
					}
					else {
						std::cout << "Failed to write process memory.\n";
						Sleep(5000);
						exit(1000);
					}
				}
				else
				{
					std::cout << "Failed to attach the processdd.";
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

