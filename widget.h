#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mysockettwo.h"
//#include "mytcpsockets.h"
#include <QTimer>
#include "mysocketfile.h"

//class QTcpSocket;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    QString filePath;

private slots:

    void on_btnConnect_clicked();

    void on_btnSend_clicked();

    void readText(const QString &str);

//    void on_btn_ChooseFile_clicked();

//    void on_btn_SendFile_clicked();

    void on_btnConnectFile_clicked();

signals:
    void con(const QString &ip, int port);
    void con1(const QString &ip, int port);

    void sendText(const QString &text);
    void sendFileHead(const QString &fileData);
    void sendFileData();
    void disConnect();



private:
    Ui::Widget *ui;

    MySocketTwo *two;
    MySocketFile *mySocketFile;
};
#endif // WIDGET_H
