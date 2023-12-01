#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //QObject::connect(&app, &QGuiApplication::aboutToQuit, LTDev::QtPdfViewerInitializer::getInstance(), LTDev::QtPdfViewerInitializer::deleteInstance)
    return a.exec();
}
