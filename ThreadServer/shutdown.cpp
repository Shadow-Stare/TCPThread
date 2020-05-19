#include "shutdown.h"
#include "windows.h"
#include <QProcess>

Shutdown::Shutdown(QObject *parent) : QObject(parent)
{

}


bool Shutdown::guanji()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    //获取进程标志
    if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
        return false;

    //获取关机特权的LUID
    LookupPrivilegeValue(NULL,SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    //获取这个进程的关机特权
    AdjustTokenPrivileges(hToken,false,&tkp,0,(PTOKEN_PRIVILEGES)NULL,0);
    if(GetLastError() != ERROR_SUCCESS)
         return false;
    //强制关闭计算机
    if(!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,0))
        return false;
}

void Shutdown::down()
{

    QString program = "C:/WINDOWS/system32/shutdown.exe";
    QStringList arguments;
    arguments << "-s";
    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);
}


