#include "mysockettwo.h"

MySocketTwo::MySocketTwo(QObject *parent) : QTcpSocket(parent)
{
    //初始化信号
    connect(this,&MySocketTwo::connected,this,&MySocketTwo::newFile);
    connect(this,&MySocketTwo::readyRead,this,&MySocketTwo::readData);
}

void MySocketTwo::cnt(const QString &ip, const int &port)
{
    this->connectToHost(ip,port);
    qDebug()<<this->waitForConnected(5000);
    qDebug()<<"connect";
}

void MySocketTwo::newFile()
{
    //连接上服务器之后的操作
    emit connectedOK();

}

void MySocketTwo::readData()
{
    //读取数据处理
    //读到数据的操作
    qDebug() <<"conn";
    QString str = this->readAll();
    emit readText(str);
    str.clear();

}

void MySocketTwo::sendText(const QString &text)
{
    QString str = text;
    this->write(str.toUtf8());
    qDebug()<<"发送: "<<str;
}
