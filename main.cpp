#include "mainwindow.h"
#include <QApplication>
#include "udp_send.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    UDP_SEND *udpSend = new UDP_SEND();
    udpSend->sendData();

    return a.exec();
}
