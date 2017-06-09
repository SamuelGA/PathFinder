#include "udp_send.h"

UDP_SEND::UDP_SEND()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 64523, QUdpSocket::ShareAddress);

}

void UDP_SEND::sendData()
{
    QByteArray Data;
    Data.append("Hello from UDP");

       // Sends the datagram datagram
       // to the host address and at port.
       // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
       //                      const QHostAddress & host, quint16 port)
    udpSocket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}
