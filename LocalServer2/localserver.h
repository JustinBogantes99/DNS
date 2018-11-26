#ifndef LOCALSERVER_H
#define LOCALSERVER_H
#include <QObject>

#include <QTcpServer>
class QTcpSocket;

class LocalServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit LocalServer(QObject *parent = nullptr);
    void recibe();
    void envia(const QString &msj);
private:
    QTcpSocket *mSocket;
    QString* servidorActual;
    QString* paginaWeb;

};

#endif // LOCALSERVER_H
