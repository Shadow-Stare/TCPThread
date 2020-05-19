#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "myserver.h"
#include "myserverfile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    MyServer *myServer;
    MyServerFile *myServerFile;

    QString filePath;

private:
    Ui::Widget *ui;

private slots:
    void readText(QByteArray buf);
    void on_btn_SendText_clicked();

    void on_btn_ChooseFile_clicked();

    void on_btn_SendFile_clicked();

signals:
    void sendText(QString buf);
    void sendFileHead(const QString &fileData);
};
#endif // WIDGET_H
