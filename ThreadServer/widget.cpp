#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myServer = new MyServer(this);
    myServer->listen(QHostAddress::Any,8888);
    connect(myServer,&MyServer::readText,this,&Widget::readText);
    connect(this,&Widget::sendText,myServer,&MyServer::sendText);

    ui->btn_ChooseFile->setEnabled(false);
    ui->btn_SendFile->setEnabled(false);
    myServerFile = new MyServerFile(this);
    myServerFile->listen(QHostAddress::Any,3333);
    connect(this,&Widget::sendFileHead,myServerFile,&MyServerFile::sendFileHead,Qt::QueuedConnection);
    connect(myServerFile,&MyServerFile::sendOK,[=]()
    {
//        ui->btn_ChooseFile->setEnabled(true);
//        ui->btn_SendFile->setEnabled(true);
    });

    connect(myServerFile,&MyServerFile::newConnection,[=](){
        ui->btn_ChooseFile->setEnabled(true);
        qDebug()<<"有连接进来";
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readText(QByteArray buf)
{
    ui->textEditRead->setText(buf);
}


void Widget::on_btn_SendText_clicked()
{
    QString str = ui->textEditWrite->toPlainText();
    emit sendText(str);
    ui->textEditWrite->clear();
}

void Widget::on_btn_ChooseFile_clicked()
{
    ////////////////////////////////

    filePath = QFileDialog::getOpenFileName(this,"open","../");
    if(false == filePath.isEmpty())  //路径有效
    {
        //可以发送
        ui->btn_ChooseFile->setEnabled(false);  //只能选择一次
        ui->btn_SendFile->setEnabled(true);
    }
    else{
        ui->textEditRead->append("选择文件路径无效：SERVER80");
    }
}

void Widget::on_btn_SendFile_clicked()
{
    ui->btn_ChooseFile->setEnabled(false);
    ui->btn_SendFile->setEnabled(false);
    emit sendFileHead(filePath);
}

