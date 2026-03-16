#include <iostream>
#include <windows.h>

DWORD WINAPI testThread(LPVOID args)
{
    char *name = (char*)args;
    std::cout<<"Hello "<<name<<"\n";
    std::cout<<"Thread started now.\n";
    Sleep(2000);
    std::cout<<"\nThread stopped now.\n";
    return 0;
}
int main()
{
    const char *name = "Hady";
    DWORD threadId;
    HANDLE hdl;
    hdl = CreateThread(NULL, 0, testThread, (LPVOID)name, 0, &threadId);
    system("pause");
    CloseHandle(hdl);
    return 0;
}