import QtQuick 2.0

Item {
    id: cell
    width: 60
    height: 60

    // Closed cell
    Rectangle {
        id: closed
        anchors.fill: parent
        border.color: "#999999"
        border.width: 1
        radius: 6
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
        border.width: 1
        radius: 6
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
        anchors.centerIn: parent
        source: "images/mine.png"
        visible: false
    }

    // Flag
    Image {
        id: flag
        anchors.centerIn: parent
        source: "images/flag.png"
        visible: false
    }

    // Stroke
    Image {
        id: stroke
        anchors.centerIn: parent
        source: "images/stroke.png"
        opacity: 0.7
        visible: false
    }

    Text {
        id: minesAround
        anchors.centerIn: parent
        font.pointSize: 28
        color: gameProxy.getColor(modelData.minesBeside)
        text: modelData.minesBeside > 0? modelData.minesBeside : ""
        visible: false
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        enabled: !model.isOpened && !gameModel.isCompleted
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button == Qt.RightButton) {
                gameProxy.flag(index);
            } else {
                gameProxy.flip(index);
            }
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
            when: (!gameModel.isCompleted && modelData.hasFlag) || (gameModel.isCompleted && modelData.hasFlag && modelData.hasMine)
            PropertyChanges {
                target: flag
                visible: true
            }
        },
        State {
            name: "closedMine"
            when: gameModel.isCompleted && modelData.hasMine && !modelData.hasFlag
            PropertyChanges {
                target: mine
                visible: true
            }
        }
        ,
        State {
            name: "closedStroked"
            when: gameModel.isCompleted && modelData.hasFlag && !modelData.hasMine
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
