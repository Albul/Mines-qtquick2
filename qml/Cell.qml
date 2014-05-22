import QtQuick 2.0
import QtQuick.Window 2.1

Item {
    id: cell
//    property int screenSize: Screen.desktopAvailableHeight > Screen.desktopAvailableWidth? Screen.desktopAvailableHeight : Screen.desktopAvailableWidth;
    width: 60 * factor
    height: this.width

    // Closed cell
    Rectangle {
        id: closed
        anchors.fill: parent
        border.color: "#999999"
        border.width: 1 * factor
        radius: 6 * factor
        smooth: true
        gradient: Gradient {
            GradientStop {position: 0.0; color: "#666666"}
            GradientStop {position: 1.0; color: "#222222"}
        }
    }

    // Opened cell
    Rectangle {
        id: opened
        anchors.fill: parent
        border.color: "#999999"
        border.width: 1 * factor
        radius: 6 * factor
        smooth: true
        gradient: Gradient {
            GradientStop {position: 0.0; color: "#c2ded0"}
            GradientStop {position: 1.0; color: "#aed7c4"}
        }
        visible: false
    }

    // Mine
    Image {
        id: mine
        scale: factor
        anchors.centerIn: parent
        source: "qrc:///images/mine.png"
        visible: false
    }

    // Flag
    Image {
        id: flag
        scale: factor
        anchors.centerIn: parent
        source: "qrc:///images/flag.png"
        visible: false
    }

    // Stroke
    Image {
        id: stroke
        scale: factor
        anchors.centerIn: parent
        source: "qrc:///images/stroke.png"
        opacity: 0.7
        visible: false
    }

    Text {
        id: minesAround
        anchors.centerIn: parent
        font.pixelSize: 38 * factor
        color: gameProxy.getColor(modelData.minesBeside)
        text: modelData.minesBeside > 0? modelData.minesBeside : ""
        visible: false
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        enabled: !model.isOpened
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button == Qt.RightButton) {
                gameProxy.flag(index);
            } else {
                gameProxy.flip(index);
            }
        }
        onPressAndHold: {
            gameProxy.flag(index);
        }
        onPressed: {
            gameProxy.isPressed = true;
        }
        onReleased: {
            gameProxy.isPressed = false;
        }
    }

    states: [
        State {
            name: "openedBlank"
            when: modelData.isOpened && !modelData.hasMine
            PropertyChanges {
                target: closed
                visible: false
            }
            PropertyChanges {
                target: opened
                visible: true
            }
            PropertyChanges {
                target: minesAround
                visible: true
            }
            PropertyChanges {
                target: mouseArea
                enabled: false
            }
        },
        State {
            name: "openedMine"
            when: modelData.isOpened && modelData.hasMine
            PropertyChanges {
                target: closed
                visible: false
            }
            PropertyChanges {
                target: opened
                visible: true
            }
            PropertyChanges {
                target: mine
                visible: true
            }
            PropertyChanges {
                target: mouseArea
                enabled: false
            }
        },
        State {
            name: "closedFlag"
            when: (!gameProxy.isCompleted && modelData.hasFlag) || (gameProxy.isCompleted && modelData.hasFlag && modelData.hasMine)
            PropertyChanges {
                target: flag
                visible: true
            }
        },
        State {
            name: "closedMine"
            when: gameProxy.isCompleted && modelData.hasMine && !modelData.hasFlag
            PropertyChanges {
                target: mine
                visible: true
            }
        }
        ,
        State {
            name: "closedStroked"
            when: gameProxy.isCompleted && modelData.hasFlag && !modelData.hasMine
            PropertyChanges {
                target: flag
                visible: true
            }
            PropertyChanges {
                target: stroke
                visible: true
            }
        }

    ]
}
