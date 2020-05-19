#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QWidget>

class MyTcpSocket;
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent,qintptr socket);

private:
    qintptr p;
    MyTcpSocket *socket;
    void run() override;
signals:
    void readText(QByteArray buf);
    void sendText(QString buf);

};

#endif // MYTHREAD_H
