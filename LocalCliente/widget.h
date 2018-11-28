#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>

namespace Ui {
class Widget;
}
class QTcpSocket;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void displayError(QAbstractSocket::SocketError socketError);
    ~Widget();

private slots:
    void on_conectar_clicked();

    void on_Quitar_clicked();

    void on_buscar_clicked();

public slots:
    void leer_socketservidor();
private:
    Ui::Widget *ui;
    QTcpSocket *mSocket;
    QString servidorActual;
    //QWebView* view;
};

#endif // WIDGET_H
