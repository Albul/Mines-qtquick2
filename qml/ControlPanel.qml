import QtQuick 2.0

Item {
    id: controlPanel
    width: 180
    height: parent.height

    Frame {
        id: box1
        height: 120
        y: 10

        Image {
            id: sunImage
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            source: {
                if (gameProxy.isPressed)
                    "qrc:///images/face-worried.png"
                else if (!gameProxy.isCompleted)
                    "qrc:///images/face-smile.png"
                else if (gameProxy.isWon)
                    "qrc:///images/face-cool.png"
                else
                    "qrc:///images/face-sad.png"
            }
        }

        Text {
            anchors.top: sunImage.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Helvetica"
            font.pointSize: 28
            smooth: true
            color: "gray"
            style: Text.Outline
            styleColor: "black"
            text: gameProxy.gameTime
        }
    }

    Frame {
        id: box2
        height: 80
        anchors.top: box1.bottom
        anchors.topMargin: 10

        Button {
            id: buttonMainMenu
            width: parent.width - 20
            anchors.centerIn: parent
            text: "Выход"
            onClicked: {
                gameProxy.finishGame(false);
            }
        }
    }
}
