#include "mythread.h"
#include "mysocket.h"

MyThread::MyThread(QObject *parent, qintptr socket) : QThread(parent)
{
    this->p = socket;
    connect(this,SIGNAL(finished()),SLOT(deleteLater()));
}

void MyThread::run()
{
    MySocket *socket = new MySocket(0,this->p);
    connect(socket,&MySocket::disconnected,this,&MyThread::quit,Qt::DirectConnection);
    connect(socket,&MySocket::readText,this,&MyThread::readText);
    connect(this,&MyThread::sendText,socket,&MySocket::sendText);
    this->exec();
}
