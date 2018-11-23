#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QMessageBox>
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

void Widget::on_conectar_clicked()
{
    mSocket->connectToHost(ui->server->text(),ui->puerto->value());
    QMessageBox::information(this,"Servidor","Se ha conectado...");
}

void Widget::on_Quitar_clicked()
{
    close();
}

void Widget::on_buscar_clicked()
{
    if (mSocket)
    {
        QMessageBox::information(this,"Servidor","Se ha encontrado");
    }else{
        QMessageBox::critical(this,"Error","No se ha conectado al servidor");
    }
}
