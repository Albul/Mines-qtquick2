import QtQuick 2.0

Item {
    id: resultPanel
    width: parent.width
    height: parent.height
    visible: false
    opacity: 0
    y: -resultPanelFrame.height

    Frame {
        id: resultPanelFrame
        width: 440
        height: 415
        anchors.centerIn: parent

        Image {
            id: gameLogo
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            source: gameProxy.isWon? "qrc:///images/face-cool.png" : "qrc:///images/face-sad.png"
        }

        Text {
            id: infoText
            anchors.top: gameLogo.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Sans"
            font.pointSize: 30
            smooth: true
            color: gameProxy.isWon? "#0e746f" : "#ca4949"
            style: Text.Raised
            styleColor: "black"
            text: gameProxy.isWon? "Ви виграли" : "Ви програли"
        }

        Text {
            id: timeText
            anchors.top: infoText.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Sans"
            font.pixelSize: 26
            color: "#484848"
            smooth: true
            text: "Время игры: " + gameProxy.gameTime
        }

        Column {
            width: parent.width / 3 * 2
            anchors.top: timeText.bottom
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10
            Button {
                anchors.topMargin: 30
                text: "Еще раз"
                onClicked: {
                    gameView.boardGrid.columns = gameModel.getNumCols();
                    gameProxy.createNewGame(gameModel.getNumRows(), gameModel.getNumCols(), gameModel.getNumMines());
                }
            }
            Button {
                text: "В меню"
                onClicked: {
                    menuPanel.state = "";
                    resultPanel.state = "hidden";
                }
            }
        }

    }

    states: [
        State {
            name: "shown"
            when: gameProxy.isCompleted
            PropertyChanges {
                target: resultPanel
                visible: true
                opacity: 1.0
                y: 0
            }
        },
        State {
            name: "hidden"
            when: !gameProxy.isCompleted
            PropertyChanges {
                target: resultPanel
                visible: false
                opacity: 0.0
                y: -resultPanelFrame.height
            }
        }
    ]

    transitions: [
        Transition {
            from: "shown"
            to: "hidden"
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
            from: "hidden"
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
