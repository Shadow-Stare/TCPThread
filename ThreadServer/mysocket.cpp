#include "mysocket.h"
#include <QDataStream>
#include <QCryptographicHash>
#include <QSettings>
#include <QMessageBox>
#include "shutdown.h"

enum socketFlag{
    md5 = 1,
    versionFlag
};
MySocket::MySocket(QObject *parent,qintptr socket) : QTcpSocket(parent)
{
    this->setSocketDescriptor(socket);

    connect(this,SIGNAL(readyRead()),this,SLOT(on_connected()));


    connect(this,&MySocket::disconnected,[]
    {
        qDebug() << "disconnected";
    });
}

void MySocket::on_connected()
{
    QByteArray buf = this->readAll();
    emit readText(buf);

    if(buf == "shutdown now")
    {
        Shutdown shutdown;
        shutdown.down();
        qDebug()<<"关机";
    }
}

void MySocket::sendText(QString buf)
{
    this->write(buf.toUtf8());
}
