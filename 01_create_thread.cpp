#include <iostream>
#include <windows.h>

DWORD WINAPI testThread(LPVOID args)
{
    std::cout<<"Thread started now.\n";
    Sleep(2000);
    std::cout<<"Thread stopped now.\n";
    return 0;
}
int main()
{
    DWORD threadId;
    HANDLE hdl;
    hdl = CreateThread(NULL, 0, testThread, NULL, 0, &threadId); // Creating Thread
    system("pause");
    CloseHandle(hdl);
    return 0;
}