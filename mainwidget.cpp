#include "mainwidget.h"

MainWidget::MainWidget()
{
    m_context = rootContext();
    m_context->setContextProperty("factor", 1);
    m_context->setContextProperty("gameProxy", &m_gameProxy);
    m_context->setContextProperty("fieldModel", m_gameProxy.getFieldModel());
    m_context->setContextProperty("recordsModel", m_gameProxy.getRecordsModel());    
    setMainQmlFile(QStringLiteral("qml/MainView.qml"));

    QQuickItem* rootObject = this->rootObject();
    QObject* resultPanel =  rootObject->findChild<QObject*>("resultPanel");
    QObject::connect(resultPanel, SIGNAL(usernameInputed(QString)),
                         &m_gameProxy, SLOT(onUsernameInputed(QString)));
}
