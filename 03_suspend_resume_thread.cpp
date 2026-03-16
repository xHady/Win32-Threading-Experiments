#include <iostream>
#include <windows.h>

DWORD WINAPI testThread(LPVOID args)
{
    char *name = (char*)args;
    std::cout<<"Hello "<<name<<"\n";
    while(true)
    {
        std::cout<<"Thread started now.\n";
        Sleep(2000);
        std::cout<<"\nThread stopped now.\n";
    }
    return 0;
}
int main()
{
    const char *name = "Hady";
    std::string command = "";
    DWORD threadId;
    HANDLE hdl;
    hdl = CreateThread(NULL, 0, testThread, (LPVOID)name, 0, &threadId);
    while(command != "exit")
    {
        std::cin>>command;
        if(command == "suspend")
        {
            SuspendThread(hdl);
        }
        else if(command == "resume")
        {
            ResumeThread(hdl);
        }
    }
    CloseHandle(hdl);
    return 0;
}