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
        Sleep(500);
        tabs = "";
        for(int i = 0;i<(threadNum);i++)
        {
            tabs += "\t";
        }
        WaitForSingleObject(hdlMutex, INFINITE);
        Sleep(20);
        std::cout<<tabs<<threadNum<<":Thread\n";
        ReleaseMutex(hdlMutex);
    }
    return 0;
}
int main()
{
    const int threadsCount = 3;
    std::vector<HANDLE> hdlVec;
    int thdNums[threadsCount];
    int priority[threadsCount] = {
        THREAD_PRIORITY_BELOW_NORMAL,
        THREAD_PRIORITY_NORMAL,
        THREAD_PRIORITY_ABOVE_NORMAL
    };
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
            SetThreadPriority(hdl, priority[i]);
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