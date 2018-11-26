#include "widget.h"
#include <QApplication>
#include <splay.cpp>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Widget w;
    w.show();
    struct node* hola=newNode("www.hola.com","192.0.0.1");
    hola=insert(hola,"www.ha.com","192.0.0.1");
    hola=insert(hola,"www.h12ola.com","192.0.0.1");
    hola=insert(hola,"www.hdwa.com","192.0.0.1");
    hola=insert(hola,"www.hqwa.org","192.0.0.1");
    hola=insert(hola,"m.facebook.com","192.0.0.1");
    hola=insert(hola,"www.ieee.org","192.0.0.1");
    imprimirArbol(hola,0);
    struct node* hole=getToPythonFormat(passToPythonFormat(hola));
    imprimirArbol(hole,0);
    return a.exec();
}
