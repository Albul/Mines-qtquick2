import QtQuick 2.0
import QtQuick.Controls 1.1 as Controls

Item {
    id: recordsPanel
    width: parent.width
    height: parent.height
    visible: false
    opacity: 0.0
    y: -recordsPanelFrame.height

    Frame {
        id: recordsPanelFrame
        width: 540 * factor
        height: 405 * factor
        anchors.centerIn: parent

        Text {
            id: title
            anchors.top: parent.top
            anchors.topMargin: 10 * factor * factor
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Sans"
            font.pixelSize: 78 * factor
            smooth: true
            color: "#12938d"
            style: Text.Raised
            styleColor: "black"
            text: "Рекорды"
        }

        Frame {
            id: table
            width: parent.width - 20 * factor
            height: 215 * factor
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: title.bottom
            anchors.topMargin: 10 * factor
            Controls.TableView {
                width: parent.width
                height: parent.height
                Controls.TableViewColumn{ role: "number"  ; title: "№" ; width: 30 * factor}
                Controls.TableViewColumn{ role: "name" ; title: "Имя" ; width: 200 * factor}
                Controls.TableViewColumn{ role: "cells" ; title: "Поле" ; width: 100 * factor}
                Controls.TableViewColumn{ role: "mines" ; title: "Мины" ; width: 80 * factor}
                Controls.TableViewColumn{ role: "time" ; title: "Время" ; width: 80 * factor}
                rowDelegate: Item {
                    height: 24 * factor
                }

                itemDelegate: Item {
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 18 * factor
                        text: styleData.value
                    }
                }
                model: recordsModel
            }
        }

        Button {
            anchors.top: table.bottom
            anchors.topMargin: 10 * factor
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3
            text: "Назад"
            onClicked: {
                recordsPanel.state = ""
                menuPanel.state = ""
            }
        }
    }

    states: [
        State {
            name: "shown"
            PropertyChanges {
                target: recordsPanel
                visible: true
                opacity: 1.0
                y: 0
            }
        }
    ]

    transitions: [
        Transition {
            from: "shown"
            to: ""
            SequentialAnimation  {
                NumberAnimation {
                    properties: "opacity, y"
                    easing.type: Easing.OutQuad
                    duration: 800
                }
                NumberAnimation {
                    properties: "visible"
                    duration: 0
                }
            }
        },
        Transition {
            from: ""
            to: "shown"
            SequentialAnimation {
                NumberAnimation {
                    properties: "visible"
                    duration: 600
                }
                NumberAnimation {
                    properties: "opacity, y"
                    easing.type: Easing.OutQuad
                    duration: 800
                }
            }
        }
    ]
}
