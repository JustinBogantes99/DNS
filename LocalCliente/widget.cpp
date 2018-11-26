#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        ui->listWidget->addItem(T.readAll());
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
    connect(mSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &Widget::displayError);
    QString servidorActual = ui->server->text();
    cout<<servidorActual.toStdString();
}

void Widget::on_Quitar_clicked()
{
    close();
}
using namespace std;
void Widget::on_buscar_clicked()
{
   QString pagina = ui->pagina->text();
   if (pagina==""){
       QMessageBox::information(this,"Cliente","para realizar la busqueda por favor ingrese un dominio que desea visitar");
   }
   else
   {

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
