#include <QtGui/QGuiApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainWidget mainWidget;
//    mainWidget.showExpanded();
//    mainWidget.showFullScreen();
    mainWidget.showMaximized();
    return app.exec();
}
