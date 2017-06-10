#include "udp_send.h"
#include <iostream>
#include <string>


UDP_SEND::UDP_SEND()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 1234);

}

void UDP_SEND::sendSplineLine(ConeList splineLine)
{
    QByteArray msg;
    msg.append("SET_SPLINE_LINE\n");
    for (TrackedCone cone : splineLine)
    {
        std::string xString = std::to_string(cone.getXPos());
        std::string yString = std::to_string(cone.getYPos());
        QByteArray *xValue = new QByteArray(xString.c_str(), xString.length());
        QByteArray *yValue = new QByteArray(yString.c_str(), yString.length());
        msg.append(*xValue);
        msg.append(" ");
        msg.append(*yValue);
        msg.append("\n");
    }
    //std::cout << "data: " << std::endl << msg.data() << std::endl;
    udpSocket->writeDatagram(msg, msg.size(), QHostAddress::LocalHost, 1234);
}

void UDP_SEND::sendOriginalTrack(ConeList leftSide, ConeList rightSide)
{
    QByteArray msg;
    msg.append("SET_ORIGINAL_TRACK\n");
    msg.append("left_side\n");
    for (TrackedCone cone : leftSide)
    {
        std::string xString = std::to_string(cone.getXPos());
        std::string yString = std::to_string(cone.getYPos());
        QByteArray *xValue = new QByteArray(xString.c_str(), xString.length());
        QByteArray *yValue = new QByteArray(yString.c_str(), yString.length());
        msg.append(*xValue);
        msg.append(" ");
        msg.append(*yValue);
        msg.append("\n");
    }
    msg.append("right_side\n");


    for (TrackedCone cone : rightSide)
    {
        std::string xString = std::to_string(cone.getXPos());
        std::string yString = std::to_string(cone.getYPos());
        QByteArray *xValue = new QByteArray(xString.c_str(), xString.length());
        QByteArray *yValue = new QByteArray(yString.c_str(), yString.length());
        msg.append(*xValue);
        msg.append(" ");
        msg.append(*yValue);
        msg.append("\n");
    }
    //std::cout << "data: " << std::endl << msg.data() << std::endl;
    udpSocket->writeDatagram(msg, msg.size(), QHostAddress::LocalHost, 1234);


}
