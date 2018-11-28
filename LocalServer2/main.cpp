#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Widget w;
    w.show();
    /**
    struct node* hola = nullptr;
    hola=insert(hola,"hola","192.0.0.1");
    hola=insert(hola,"cmamo","192.168.0.17");
    hola=insert(hola,"ha","192.0.0.1");
    hola=insert(hola,"a","192.0.0.1");
    hola=insert(hola,"www.h12ola.com","192.0.0.1");
    hola=insert(hola,"www.hdwa.com","192.0.0.1");
    hola=insert(hola,"www.hqwa.org","192.0.0.1");
    hola=insert(hola,"m.facebook.com","192.0.0.1");
    hola=insert(hola,"www.ieee.org","192.0.0.1");
    //imprimirArbol(hola,0);
    //struct node* hole=getToPythonFormat(passToPythonFormat(hola));
    imprimirArbol(hola,0);
    //struct node* hola2=newNode("www.cmamo.com","192.168.0.17");
    **/
    return a.exec();
}
