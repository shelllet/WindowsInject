// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <iostream>
#include <ostream>
#include  <thread>

std::thread::id tid;

void DoWork()
{
	MessageBox(NULL, L"Title", L"this is dll messagebox!", MB_OK);

		MSG msg;
		BOOL result;

		for (;;)
		{
			result = GetMessage(&msg, nullptr, 0, 0);

			if (result <= 0)
			{
				break;
			}

			std::cout << msg.message << " " << msg.wParam << " " << msg.lParam << std::endl;

			//TranslateMessage(&msg);
			//DispatchMessage(&msg);
		}

}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	    {
        std::thread t([]()
        {
                DoWork();
        });

        tid = t.get_id();

        t.detach();

	    }
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        ::PostThreadMessageW(tid._Get_underlying_id(), WM_QUIT, 0, 0);
        break;
    }
    return TRUE;
}

