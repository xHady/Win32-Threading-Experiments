#include <iostream>
#include <windows.h>
#include <vector>
HANDLE hdlMutex;
DWORD WINAPI threadVisualization(LPVOID args)
{
    int threadNum = *(int*)args;
    std::string tabs = "";
    while(true)
    {
        WaitForSingleObject(hdlMutex, INFINITE);
        Sleep(500);
        tabs = "";
        for(int i = 0;i<(threadNum);i++)
        {
            tabs += "\t";
        }
        std::cout<<tabs<<threadNum<<":Thread\n";
        ReleaseMutex(hdlMutex);
    }
    return 0;
}
int main()
{
    int threadNum = 0;
    const int threadsCount = 3;
    int thdNums[threadsCount];
    std::vector<HANDLE> hdlVec;
    HANDLE hdl;
    hdlMutex = CreateMutex(NULL, 0, NULL);
    if(hdlMutex == NULL)
    {
        std::cout<<"Error while Creating Mutex\n";
        return 0;
    }
    for(int i = 0;i<threadsCount;i++)
    {
        DWORD threadId;
        thdNums[i] = i;
        hdl = CreateThread(NULL, 0, threadVisualization, (LPVOID)&thdNums[i], 0, &threadId); // Creating Thread
        if(hdl != NULL)
        {
            hdlVec.push_back(hdl);
        }
        else
        {
            std::cout<<"Failed Creating Thread "<<i;
        }
    }

    for(int i = 0;i<threadsCount;i++)
    {
        WaitForSingleObject(hdlVec[i], INFINITE);
        CloseHandle(hdlVec[i]);
    }
    CloseHandle(hdlMutex);
    return 0;
}