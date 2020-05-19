#ifndef MYSOCKETTWO_H
#define MYSOCKETTWO_H

#include <QTcpSocket>
#include <QIODevice>
#include <QHostAddress>

class QFile;


class MySocketTwo : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocketTwo(QObject *parent = nullptr);

public slots:
    void cnt(const QString &ip, const int &port);

    void newFile();

    void readData();

    void sendText(const QString &text);

signals:
    void sendData(const int &i,const QString &str);
    void readText(const QString &str);
    void connectedOK();
};

#endif // MYSOCKETTWO_H
