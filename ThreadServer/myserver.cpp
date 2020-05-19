#include "myserver.h"
//#include "mythread.h"
MyServer::MyServer(QObject *parent) : QTcpServer(parent)
{

}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    static int i = 0;
    MyThread *thread = new MyThread(0,socketDescriptor);
    thread->start();

    connect(thread,&MyThread::finished,[&]{
        qDebug()<<"thread is over";
    });
    connect(thread,&MyThread::finished,&MyThread::deleteLater);
    connect(thread,&MyThread::readText,this,&MyServer::readText);
    connect(this,&MyServer::sendText,thread,&MyThread::sendText);
}
