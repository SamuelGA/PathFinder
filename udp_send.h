#ifndef UDP_SEND_H
#define UDP_SEND_H

#include <QUdpSocket>
#include <QObject>
#include <QMainWindow>

class UDP_SEND : public QObject
{
    Q_OBJECT
public:
    UDP_SEND();
private:
    QUdpSocket *udpSocket;
    QMainWindow *mainWindow;
public slots:
    void sendData();
};

#endif // UDP_SEND_H
