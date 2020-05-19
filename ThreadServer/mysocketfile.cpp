#include "mysocketfile.h"
#include "QFileInfo"

MySocketFile::MySocketFile(QObject *parent, qintptr socket) : QTcpSocket(parent)
{
    this->setSocketDescriptor(socket);

    connect(this,SIGNAL(readyRead()),this,SLOT(on_connected()));

    connect(this,&MySocketFile::disconnected,[]
    {
        qDebug() << "disconnected";
    });
}

void MySocketFile::sendFileHead(const QString &filePath)
{
    //发送按钮已经点击，发送过程中不能再点击，恢复按钮初始化


    fileName.clear();
    fileSize = 0;
    //获取文件信息：名字、大小
    QFileInfo info(filePath);
    fileName = info.fileName();
    fileSize = info.size();
    sendSize = 0;   //已经发送文件大小

    //以只读方式打开文件
    file.setFileName(filePath);
    if(false == file.open(QIODevice::ReadOnly)){
        qDebug() <<"只读方式打开文件失败";
    }
    //提示已经打开的文件路径
    qDebug()<<filePath;

        //先发送文件头信息:文件名##大小
        //构造头部信息
        QString head = QString("%1##%2").arg(fileName).arg(fileSize);
        //发送头部信息
        qint64 len = this->write(head.toUtf8());

        if(len < 0){
            qDebug()<<"文件头部信息发送失败！";
            //关闭文件
            file.close();
        }
}

void MySocketFile::sendFileData()
{
    qint64 len = 0;
        do{
            //一次发送的大小
            char buf[BUF_SIZE] = {0};
            len = 0;
            len = file.read(buf,BUF_SIZE);  //len为读取的字节数
            len = this->write(buf,len);    //len为发送的字节数
            //已发数据累加
            sendSize += len;
        }while(len > 0);

}


void MySocketFile::on_connected()
{
    QByteArray buf = this->readAll();
//    this->waitForReadyRead();

    //////////////////////////////////////////////////
//    this->waitForReadyRead();
    //采用回射信息进行粘包处理
    if("FileHead recv" == QString(buf)){
        //ui->textEdit->append("文件头部接收成功，开始发送文件...");
        sendFileData();
    }
    else if("file write done" == QString(buf)){
        //服务器发送的快，而客户端接收的慢，所以要等客户端接收完毕后才能断开连接，以免丢包
        qDebug()<<"对端接收完成";
        file.close();
        this->disconnectFromHost();
//        this->waitForDisconnected();
        this->close();
        emit sendOK();
    }


}

