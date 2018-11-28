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
    void envia(const QString &msj);
public slots:
    void recibe();
private:
    QTcpSocket *mSocket;
    QString* servidorActual;
    QString* paginaWeb;

};

#endif // LOCALSERVER_H
