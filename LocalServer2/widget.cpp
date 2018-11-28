#include "widget.h"
#include "ui_widget.h"
#include "localserver.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mLocalServer = new LocalServer(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Iniciar_clicked()
{
    if(!mLocalServer->listen(QHostAddress::Any, ui->puerto->value())){
        QMessageBox::critical(this,"Error",mLocalServer->errorString());
    }else {
        QMessageBox::information(this,"Servidor","Iniciado...");

    }
}
void Widget::escucha()
{
    mLocalServer->recibe();
}

void Widget::on_Quitar_clicked()
{
    close();
}
