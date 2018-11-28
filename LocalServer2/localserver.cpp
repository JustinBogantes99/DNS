#include "localserver.h"
#include <QTcpSocket>
#include <QTextStream>
#include <iostream>
#include "splay.cpp"
LocalServer::LocalServer(QObject *parent) : QTcpServer(parent)
{
    mSocket = nullptr;

    connect(this,&LocalServer::newConnection, [&]() {
        mSocket = nextPendingConnection();
        connect(mSocket, SIGNAL(readyRead()),this, SLOT(recibe()));
    });
}
using namespace std;
void LocalServer::recibe()
{
    QByteArray data = mSocket->readAll();
    mSocket->flush();
    cout<<data.toStdString();
}
void LocalServer::envia(const QString &msj)
{
    if (mSocket) {
        QTextStream T(mSocket);
        T<<msj;
        mSocket->flush();
    }
}

