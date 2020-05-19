#include "mythreadfile.h"
#include "mysocketfile.h"


MyThreadFile::MyThreadFile(QObject *parent, qintptr socket)
{
    this->p = socket;
    connect(this,SIGNAL(finished()),SLOT(deleteLater()));
}

void MyThreadFile::run()
{
    MySocketFile *socket = new MySocketFile(0,this->p);
    connect(socket,&MySocketFile::disconnected,this,&MyThreadFile::quit,Qt::DirectConnection);
    connect(this,&MyThreadFile::sendFileHead,socket,&MySocketFile::sendFileHead);
    connect(socket,&MySocketFile::sendOK,this,&MyThreadFile::sendOK);
    this->exec();
}

