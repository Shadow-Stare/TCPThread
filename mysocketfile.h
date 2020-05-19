#ifndef MYSOCKETFILE_H
#define MYSOCKETFILE_H

#include <QTcpSocket>
#include <QIODevice>
#include <QHostAddress>
#include <QFile>
#define BUF_SIZE 1024*4

class MySocketFile : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocketFile(QObject *parent = nullptr);


    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;
    bool isStart = true;
    qint64 recvSize;

public slots:
    void cnt(const QString &ip, const int &port);
//    void sendFileHead(const QString &filePath);
//    void sendFileData();
    void disConnect();
    void readData();

    void connectOK();





signals:

};

#endif // MYSOCKETFILE_H
