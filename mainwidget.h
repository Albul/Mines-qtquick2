#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QQmlContext>
#include <QQuickItem>
#include "qtquick2applicationviewer.h"
#include "gameproxy.h"

class MainWidget : public QtQuick2ApplicationViewer
{
public:
    MainWidget();

private:
    QQmlContext* m_context;
    GameProxy m_gameProxy;
};

#endif // MAINWIDGET_H
