#include "localserver.h"
#include <QTcpSocket>
#include <QTextStream>
#include <iostream>
LocalServer::LocalServer(QObject *parent) : QTcpServer(parent)
{
    mSocket = nullptr;

    connect(this,&LocalServer::newConnection, [&]() {
        mSocket = nextPendingConnection();
    });
}
using namespace std;
void LocalServer::recibe()
{
    QByteArray data = mSocket->readAll();
    mSocket->flush();
    cout<<data.toStdString();
    //cout<<data.toStdString()<<endl;
}
void LocalServer::envia(const QString &msj)
{
    if (mSocket) {
        QTextStream T(mSocket);
        T<<msj;
        mSocket->flush();
    }
}

