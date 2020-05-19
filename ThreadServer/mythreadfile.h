#ifndef MYTHREADFILE_H
#define MYTHREADFILE_H

#include <QThread>
#include <QWidget>

class MyTcpSocketFile;
class MyThreadFile : public QThread
{
    Q_OBJECT
public:
    explicit MyThreadFile(QObject *parent,qintptr socket);

private:
    qintptr p;
    MyTcpSocketFile *socket;
    void run() override;
signals:
    void sendFileHead(const QString &fileData);
    void sendOK();
};

#endif // MYTHREADFILE_H
