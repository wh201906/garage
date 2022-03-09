#include "procutil.h"

#include <tlhelp32.h>
#include <tchar.h>

ProcUtil::ProcUtil(QObject *parent)
    : QObject{parent}
{

}

QVector<ProcUtil::ProcInfo> ProcUtil::GetProcessList()
{
    QVector<ProcUtil::ProcInfo> result;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
        return(result);
    }

    // Set the size of the structure before using it.
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if(!Process32First(hProcessSnap, &pe32))
    {
        printError(TEXT("Process32First"));   // show cause of failure
        CloseHandle(hProcessSnap);            // clean the snapshot object
        return(result);
    }

    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do
    {
        result.append(ProcInfo{pe32.th32ProcessID, QString::fromWCharArray(pe32.szExeFile)});
    }
    while(Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return(result);
}


QVector<QString> ProcUtil::ListProcessModules(DWORD dwPID)
{
    QVector<QString> result;
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if(hModuleSnap == INVALID_HANDLE_VALUE)
    {
        printError(TEXT("CreateToolhelp32Snapshot (of modules)"));
        return(result);
    }

    // Set the size of the structure before using it.
    me32.dwSize = sizeof(MODULEENTRY32);

    // Retrieve information about the first module,
    // and exit if unsuccessful
    if(!Module32First(hModuleSnap, &me32))
    {
        printError(TEXT("Module32First"));    // show cause of failure
        CloseHandle(hModuleSnap);             // clean the snapshot object
        return(result);
    }

    // Now walk the module list of the process,
    // and display information about each module
    do
    {
        result.append(QString::fromWCharArray(me32.szExePath));
    }
    while(Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return(result);
}

void ProcUtil::printError(TCHAR* msg)
{
    DWORD eNum;
    TCHAR sysMsg[256];
    TCHAR* p;

    eNum = GetLastError();
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, eNum,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  sysMsg, 256, NULL);

    // Trim the end of the line and terminate it with a null
    p = sysMsg;
    while((*p > 31) || (*p == 9))
        ++p;
    do
    {
        *p-- = 0;
    }
    while((p >= sysMsg) &&
            ((*p == '.') || (*p < 33)));

    // Display the message
    _tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}
