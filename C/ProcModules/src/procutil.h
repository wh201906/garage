#ifndef PROCUTIL_H
#define PROCUTIL_H

#include <QObject>
#include <windows.h>

// migrated from
// https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
class ProcUtil : public QObject
{
    Q_OBJECT
public:
    explicit ProcUtil(QObject *parent = nullptr);

    struct ProcInfo
    {
        quint32 PID;
        QString name;
    };

    static QVector<ProcInfo> GetProcessList();
    static QVector<QString> ListProcessModules(DWORD dwPID);
    static void printError(TCHAR* msg);

signals:

};

#endif // PROCUTIL_H
