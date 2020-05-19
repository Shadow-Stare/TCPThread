#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include "mythread.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);

    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void readText(QByteArray buf);
    void sendText(QString buf);
};

#endif // MYSERVER_H
