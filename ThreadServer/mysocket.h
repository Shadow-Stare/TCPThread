#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>
#include <QFile>

class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent,qintptr socket);
    //处理新来的连接
public slots:

    virtual void on_connected();

public:
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recvSize;



    bool isStart = true;



signals:
    void readText(QByteArray buf);

public    slots:
    void sendText(QString buf);
};

#endif // MYSOCKET_H
