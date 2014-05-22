import QtQuick 2.0

Item {
    id: controlPanel
    width: 180 * factor
    height: parent.height

    Frame {
        id: box1
        height: 120 * factor
        y: 10 * factor

        Image {
            id: sunImage
            scale: factor
            anchors.top: parent.top
            anchors.topMargin: 10 * factor * factor
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
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5 * factor
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Helvetica"
            font.pixelSize: 48 * factor
            smooth: true
            color: "gray"
            style: Text.Outline
            styleColor: "black"
            text: gameProxy.gameTime
        }
    }

    Frame {
        id: box2
        height: 80 * factor
        anchors.top: box1.bottom
        anchors.topMargin: 10 * factor

        Button {
            id: buttonMainMenu
            width: parent.width - 20 * factor
            anchors.centerIn: parent
            text: "Выход"
            onClicked: {
                gameProxy.finishGame(false);
            }
        }
    }
}
