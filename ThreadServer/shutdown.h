#ifndef SHUTDOWN_H
#define SHUTDOWN_H

#include <QObject>

class Shutdown : public QObject
{
    Q_OBJECT
public:
    explicit Shutdown(QObject *parent = nullptr);
    bool guanji();

    void down();


signals:

};

#endif // SHUTDOWN_H
