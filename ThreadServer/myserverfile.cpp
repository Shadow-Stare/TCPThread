#include "myserverfile.h"
#include "mythreadfile.h"

MyServerFile::MyServerFile(QObject *parent) : QTcpServer(parent)
{

}

void MyServerFile::incomingConnection(qintptr socketDescriptor)
{
    static int i = 0;
    MyThreadFile *thread = new MyThreadFile(0,socketDescriptor);
    thread->start();

    connect(thread,&MyThreadFile::finished,[&]{
        qDebug()<<"thread is over";
    });
    connect(thread,&MyThreadFile::finished,&MyThreadFile::deleteLater);
    connect(this,&MyServerFile::sendFileHead,thread,&MyThreadFile::sendFileHead);
    connect(thread,&MyThreadFile::sendOK,this,&MyServerFile::sendOK);
}
