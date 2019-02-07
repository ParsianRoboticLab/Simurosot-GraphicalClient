#include <QApplication>
#include "drawpacket.h"
#include "packet.h"
#include <stdio.h>
#include <QtGui>
#include <QApplication>
#include "soccerview.h"
#include "timer.h"
#include <QtNetwork>
#include <QHostAddress>

GLSoccerView *view;

bool runApp = true;

class MyThread : public QThread
{
protected:
    void run()
    {
        static const double minDuration = 0.01; //100FPS
        QUdpSocket* socket = new QUdpSocket();
        QUdpSocket* socketD = new QUdpSocket();
        socket->bind(QHostAddress::AnyIPv4, 10020, QUdpSocket::ShareAddress);
        socket->joinMulticastGroup(QHostAddress("224.5.23.2"));
        socketD->bind(QHostAddress::AnyIPv4, 10010, QUdpSocket::ShareAddress);
        socketD->joinMulticastGroup(QHostAddress("224.5.23.1"));
        Packet packet;
        DrawPacket dPacket;
        while(runApp) {
            while (socket->hasPendingDatagrams()) {
                QByteArray Buffer;
                Buffer.resize(socket->pendingDatagramSize());

                QHostAddress sender;
                quint16 senderPort;
                socket->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);
                qDebug() << Buffer.data() << senderPort << sender.toString();
                packet.parse(Buffer.data(), Buffer.size());
                view->updatePacket(packet);
            }
            while (socketD->hasPendingDatagrams()) {
                QByteArray Buffer;
                Buffer.resize(socketD->pendingDatagramSize());

                QHostAddress sender;
                quint16 senderPort;
                socketD->readDatagram(Buffer.data(),Buffer.size(),&sender,&senderPort);
                qDebug() << Buffer.data() << senderPort << sender.toString();
//                dPacket.parse(Buffer.data(), Buffer.size());
                view->updateDraws(dPacket);
            }
            Sleep(minDuration);
        }
    }

public:
    MyThread(QObject* parent = 0){}
    ~MyThread(){}
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    view = new GLSoccerView();
    view->show();
    MyThread thread;
    thread.start();
    int retVal = app.exec();
    runApp = false;
    thread.wait();
    return retVal;
}

