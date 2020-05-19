#ifndef MYSERVERFILE_H
#define MYSERVERFILE_H

#include <QTcpServer>

class MyServerFile : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServerFile(QObject *parent = nullptr);

    void incomingConnection(qintptr socketDescriptor) override;

signals:

    void sendFileHead(const QString &fileData);
    void sendOK();
};

#endif // MYSERVERFILE_H
