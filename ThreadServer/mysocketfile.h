#ifndef MYSOCKETFILE_H
#define MYSOCKETFILE_H

#include <QTcpSocket>
#include <QIODevice>
#include <QFile>
#define BUF_SIZE 1024*4

class MySocketFile : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocketFile(QObject *parent,qintptr socket);

public slots:
    void sendFileHead(const QString &filePath);
    void sendFileData();
    void on_connected();

public:
        QFile file;
        QString fileName;
        qint64 fileSize;
        qint64 recvSize;
        qint64 sendSize;
        bool isStart = true;

signals:
        void sendOK();


};

#endif // MYSOCKETFILE_H
