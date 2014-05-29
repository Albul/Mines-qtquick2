import QtQuick 2.2

Item {
    id: resultPanel
    objectName: "resultPanel"
    width: parent.width
    height: parent.height
    visible: false
    opacity: 0
    y: -resultPanelFrame.height

    signal usernameReceived(string name)

    Frame {
        id: resultPanelFrame
        width: 440 * factor
        height: 415 * factor
        anchors.centerIn: parent

        Image {
            id: gameLogo
            scale: factor
            anchors.top: parent.top
            anchors.topMargin: 20 * factor * factor
            anchors.horizontalCenter: parent.horizontalCenter
            source: gameProxy.isWon? "qrc:///images/face-cool.png" : "qrc:///images/face-sad.png"
        }

        Text {
            id: infoText
            anchors.top: gameLogo.bottom
            anchors.topMargin: 10 * factor * factor
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Sans"
            font.pixelSize: 40 * factor
            smooth: true
            color: gameProxy.isWon? "#0e746f" : "#ca4949"
            style: Text.Raised
            styleColor: "black"
            text: gameProxy.isWon? (gameProxy.isRecord? "Новый рекорд" : "Вы выиграли") : "Вы проиграли"
        }

        Text {
            id: timeText
            anchors.top: infoText.bottom
            anchors.topMargin: 30 * factor
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Sans"
            font.pixelSize: 30 * factor
            color: "#5b5b5b"
            style: Text.Raised
            styleColor: "black"
            smooth: true
            text: "Время игры: " + gameProxy.gameTime
        }

        TextInput {
            id: inputName
            anchors.top: timeText.bottom
            anchors.topMargin: 10 * factor
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 20 * factor
            visible: false
            onAccepted: {
                this.focus = false;
                gameProxy.addRecord(this.text);
                this.visible = false;
            }
        }

        Column {
            width: parent.width / 3 * 2
            anchors.top: inputName.bottom
            anchors.topMargin: 20 * factor
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10 * factor
            Button {
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
            PropertyChanges {
                target: inputName
                text: "Введите ваше имя <Enter>"
                visible: gameProxy.isRecord
                focus: gameProxy.isRecord
            }
            StateChangeScript  {
                script: inputName.selectAll();
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
