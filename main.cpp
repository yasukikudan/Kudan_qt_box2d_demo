#include "widget.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    qDebug() << QStyleFactory::keys();
    Widget w;
    w.show();

    return a.exec();
}
