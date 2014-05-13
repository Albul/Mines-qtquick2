#include "mainwidget.h"

MainWidget::MainWidget()
{
    m_context = rootContext();
    m_context->setContextProperty("gameProxy", &m_gameProxy);
    m_context->setContextProperty("gameModel", m_gameProxy.getGameModel());
    setMainQmlFile(QStringLiteral("qml/Mines/MainView.qml"));
}
