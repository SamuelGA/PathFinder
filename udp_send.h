#ifndef UDP_SEND_H
#define UDP_SEND_H

#include <QUdpSocket>
#include <QObject>
#include <QMainWindow>
#include <vector>
#include <glm/glm.hpp>
#include "conelist.h"

class UDP_SEND : public QObject
{
    Q_OBJECT
public:
    UDP_SEND();
    void sendOriginalTrack(ConeList leftSide, ConeList rightSide);
    void sendSplineLine(ConeList splineLine);
private:
    QUdpSocket *udpSocket;  
};

#endif // UDP_SEND_H
