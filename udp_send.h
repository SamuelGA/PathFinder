#ifndef UDP_SEND_H
#define UDP_SEND_H

#include <QUdpSocket>
#include <QObject>
#include <QMainWindow>
#include <vector>
#include <glm/glm.hpp>

class UDP_SEND : public QObject
{
    Q_OBJECT
public:
    UDP_SEND();
    void sendOriginalTrack(std::vector<glm::vec2> leftSide, std::vector<glm::vec2> rightSide);

private:
    QUdpSocket *udpSocket;  
};

#endif // UDP_SEND_H
