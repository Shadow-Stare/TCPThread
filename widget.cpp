#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnConnect_clicked()
{
    //线程发送


    QThread *th = new QThread;
    th->start();

    two  = new MySocketTwo();
    connect(this, &Widget::con, two, &MySocketTwo::cnt, Qt::QueuedConnection);
    connect(this,&Widget::sendText,two,&MySocketTwo::sendText,Qt::QueuedConnection);
    connect(two,&MySocketTwo::readText,this,&Widget::readText);
    connect(two,&MySocketTwo::connectedOK,[=]()
    {
            ui->btnConnect->setEnabled(false);
    });
    connect(two,&MySocketTwo::disconnected,[=]()
    {
        ui->btnConnect->setEnabled(true);
    });


    two->moveToThread(th);


    emit this->con(ui->lineEdit->text(), 8888);
    qDebug()<<"111111";






    return ;
}

void Widget::on_btnSend_clicked()
{   //通过信号与槽 发送sendText(str)信号 传参    线程中 槽sendText(text)接收

    QString str = ui->textEditWrite->toPlainText();
    emit this->sendText(str);
    ui->textEditWrite->clear();
}

void Widget::readText(const QString &str)
{
    ui->textEditRead->setText(str);
}

void Widget::on_btnConnectFile_clicked()
{
    QThread *fileth = new QThread;
    fileth->start();
    mySocketFile = new MySocketFile;
    connect(this, &Widget::con1, mySocketFile, &MySocketFile::cnt, Qt::QueuedConnection);
//    connect(this,&Widget::sendFileHead,mySocketFile,&MySocketFile::sendFileHead,Qt::QueuedConnection);
    connect(this,&Widget::disConnect,mySocketFile,&MySocketFile::disConnect,Qt::QueuedConnection);
    connect(mySocketFile,&MySocketFile::disconnected,fileth,&QThread::quit);
    mySocketFile->moveToThread(fileth);


    emit this->con1(ui->lineEditFile->text(),3333);
}
