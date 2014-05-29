#include "mainwidget.h"

MainWidget::MainWidget()
{
    m_context = rootContext();
    m_context->setContextProperty("factor", 2);
    m_context->setContextProperty("gameProxy", &m_gameProxy);
    m_context->setContextProperty("gameModel", m_gameProxy.getGameModel());
    m_context->setContextProperty("recordsModel", m_gameProxy.getRecordsModel());    

    setMainQmlFile(QStringLiteral("qml/MainView.qml"));
}
