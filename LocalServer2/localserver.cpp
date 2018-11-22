#include "localserver.h"
#include <QTcpSocket>
#include <QTextStream>
LocalServer::LocalServer(QObject *parent) : QTcpServer(parent)
{
    mSocket = nullptr;

    connect(this,&LocalServer::newConnection, [&]() {
        mSocket = nextPendingConnection();
    });
}
void LocalServer::envia(const QString &msj)
{
    if (mSocket) {
        QTextStream T(mSocket);
        T<<msj;
        mSocket->flush();
    }
}
