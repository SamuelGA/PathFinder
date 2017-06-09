#include "mainwindow.h"
#include <QApplication>
#include "udp_send.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<glm::vec2> rightCones;
    std::vector<glm::vec2> leftCones;

    rightCones.push_back(glm::vec2(0, 4));
    rightCones.push_back(glm::vec2(4, 6));
    rightCones.push_back(glm::vec2(8, 3));
    rightCones.push_back(glm::vec2(12, 0));
    rightCones.push_back(glm::vec2(16, -1));
    rightCones.push_back(glm::vec2(20, 3));
    rightCones.push_back(glm::vec2(24, 6));
    rightCones.push_back(glm::vec2(28, 9));

    leftCones.push_back(glm::vec2(0, -4));
    leftCones.push_back(glm::vec2(4,-2));
    leftCones.push_back(glm::vec2(8,-5));
    leftCones.push_back(glm::vec2(12,-8));
    leftCones.push_back(glm::vec2(16,-9));
    leftCones.push_back(glm::vec2(20,-5));
    leftCones.push_back(glm::vec2(24,-2));
    leftCones.push_back(glm::vec2(28,1));

    UDP_SEND *udpSend = new UDP_SEND();
    udpSend->sendOriginalTrack(leftCones, rightCones);
    udpSend->sendSplineLine(rightCones);

    return a.exec();
}
