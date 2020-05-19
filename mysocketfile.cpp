#include "mysocketfile.h"
#include <QFileInfo>

MySocketFile::MySocketFile(QObject *parent) : QTcpSocket(parent)
{
    connect(this,&MySocketFile::connected,this,&MySocketFile::connectOK);
    connect(this,&MySocketFile::readyRead,this,&MySocketFile::readData);
}

void MySocketFile::cnt(const QString &ip, const int &port)
{
    this->connectToHost(ip,port);
//    qDebug()<<this->waitForConnected(5000);
    qDebug()<<"connect";
}

void MySocketFile::disConnect()
{
    this->disconnectFromHost();
//    this->waitForDisconnected();
    this->close();
}

void MySocketFile::readData()
{
    QByteArray buf = this->readAll();



    //    QByteArray buf = this->readAll();
    //    this->waitForReadyRead();
        if(true == isStart)
        {
            isStart = false;
            //接收包头
            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",1,1).toInt();
            recvSize = 0;

            file.setFileName(fileName);
            if(false == file.open(QIODevice::WriteOnly))
            {
                qDebug ()<< "文件创建并打开失败!";
            }
            this->write("FileHead recv");
    //        this->waitForBytesWritten();




        }else
        {
            //接收处理文件
            qint64 len = file.write(buf);
            recvSize += len;

            if(recvSize == fileSize){//接收完毕
                file.close();
                //提示信息
                qDebug()<<"文件接收完成";
                //回射信息
                this->write("file write done");
    //            this->waitForBytesWritten();
                this->disconnectFromHost();
    //            this->waitForDisconnected();
                this->close();
            }
        }




}

void MySocketFile::connectOK()
{
    qDebug()<<"客户端连接成功";
}
