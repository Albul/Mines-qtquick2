# Add more folders to ship with the application, here
folder_01.source = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT += quick multimedia sql

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    mainwidget.cpp \
    cell.cpp \
    gameproxy.cpp \
    recordsmodel.cpp \
    fieldmodel.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/MainView.qml \
    qml/Cell.qml

HEADERS += \
    mainwidget.h \
    cell.h \
    gameproxy.h \
    recordsmodel.h \
    fieldmodel.h

RESOURCES += \
    res.qrc
