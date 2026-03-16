#include <iostream>
#include <windows.h>
#include <vector>
int counter = 0;
DWORD WINAPI testThread(LPVOID args)
{
    int *Counts = (int*)args;
    for(int i = 0;i<*Counts;i++)
    {
        counter++;
    }
    return 0;
}
int main()
{
    const int Counts = 100000;
    const int threadsCount = 2;
    std::vector<HANDLE> hdlVec;
    HANDLE hdl;
    for(int i = 0;i<threadsCount;i++)
    {
        DWORD threadId;
        hdl = CreateThread(NULL, 0, testThread, (LPVOID)&Counts, 0, &threadId); // Creating Thread
        hdlVec.push_back(hdl);
    }
    for(int i = 0;i<threadsCount;i++)
    {
        WaitForSingleObject(hdlVec[i], INFINITE);
        CloseHandle(hdlVec[i]);
    }
    std::cout<<counter; // Expected (Counts * threads), but output is gonna be wrong (less) due to race condition, cause more than thread trying to access counter at the same time
    return 0;
}