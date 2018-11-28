#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include <QDataStream>
#include <QHostAddress>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead, [&](){QTextStream T(mSocket);ui->pantalla->addItem(T.readAll());
    });
}

Widget::~Widget()
{
    delete ui;
}
using namespace std;
void Widget::on_conectar_clicked()
{
    mSocket->connectToHost(ui->server->text(),ui->puerto->value());
    connect(mSocket,SIGNAL(readyRead()),this,SLOT (leer_socketservidor()));
    connect(mSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &Widget::displayError);
    servidorActual = ui->server->text();
    QMessageBox::information(this,"Client","Se ha conectado al servidor");
    /**
    if(mSocket->state() == QAbstractSocket::ConnectedState)
    {
        QMessageBox::information(this,"Client","Se ha conectado al servidor");**/
    /**}
    else {
        QMessageBox::critical(this,"Cliente","Error no hay conexion con el servidor");
    }**/
}

void Widget::leer_socketservidor()
{
  QByteArray buffer;
  buffer.resize((mSocket->bytesAvailable()));
  mSocket->read(buffer.data(),buffer.size());
  ui->pantalla->addItem(QString (buffer.data()));
}
void Widget::on_Quitar_clicked()
{
    close();
}
using namespace std;
void Widget::on_buscar_clicked()
{
   QString paginaWeb = ui->pagina->text();
   if (paginaWeb==""){
       QMessageBox::information(this,"Cliente","para realizar la busqueda por favor ingrese un dominio que desea visitar");
   }
   else
   {
       if(mSocket->state() == QAbstractSocket::ConnectedState)
       {
           QByteArray array;
           //cout<<servidorActual.toStdString();
           //cout<<paginaWeb.toStdString();
           array.append(servidorActual);
           array.append(paginaWeb);
           mSocket->write(array , array.size());
           ui->pagina->clear();
           //mSocket->write(paginaWeb.toLocal8Bit());
       }
       else
           QMessageBox::critical(this,"Cliente","Error no hay conexion con el servidor");
   }

}

void Widget::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Cliente"),
                                 tr("El servidor no se ha encontrado. Por favor verifica  "
                                    "el nombre del servidor y tu dirreccion IP."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Cliente"),
                                 tr("La conexion fue rechazada. "
                                    "Asegurese de que el servidor este activo, "
                                    "verifica el puerto y tu dirreccion IP"));
        break;
    default:
        QMessageBox::information(this, tr("Cliente"),tr("Error inesperado : %1.").arg(mSocket->errorString()));
    }
}

