#include "ccontrolblock.h"
#include <QApplication>
#include <QStyleFactory>
#include <QFile>

int main(int argc, char *argv[])
{
#if(QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);
    CControlBlock controlcenter;
    controlcenter.getApp(a);

    return a.exec();
}
