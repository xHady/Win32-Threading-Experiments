#include <iostream>
#include <windows.h>
#include <vector>
int counter = 0;
HANDLE hdlMutex;
DWORD WINAPI testThread(LPVOID args)
{
    int Counts = *(int*)args;
    int internalCounter = 0;
    for(int i = 0;i<Counts;i++)
    {
        internalCounter++;
    }
    WaitForSingleObject(hdlMutex, INFINITE);
    counter += internalCounter;
    ReleaseMutex(hdlMutex);
    return 0;
}
int main()
{
    const int Counts = 100000;
    const int threadsCount = 2;
    char MtxName[] = "MutexTest";
    std::vector<HANDLE> hdlVec;
    HANDLE hdl;
    hdlMutex = CreateMutex(NULL, false, MtxName);
    if(hdlMutex == NULL)
    {
        std::cout<<"Failed Creating Mutex\n";
        return 0;
    }
    for(int i = 0;i<threadsCount;i++)
    {
        DWORD threadId;
        hdl = CreateThread(NULL, 0, testThread, (LPVOID)&Counts, 0, &threadId); // Creating Thread
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
    std::cout<<counter; // as we added mutex race condition solved
    return 0;
}