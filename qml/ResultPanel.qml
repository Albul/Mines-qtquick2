import QtQuick 2.0

Item {
    id: resultPanel
    width: parent.width
    height: parent.height

    Frame {
        id: resultPanelFrame
        width: 440
        height: 415
        anchors.centerIn: parent

        Image {
            id: gameLogo
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            source: "images/mine100.png"
            Text {
                anchors.centerIn: parent
                font.family: "Sans"
                font.pointSize: 34
                smooth: true
                color: "#12938d"
                style: Text.Outline
                styleColor: "black"
                text: "Вы проиграли"
            }
        }
    }

    states: [
        State {
            name: "shown"
            when: gameModel.isCompleted
            PropertyChanges {
                target: resultPanel
                visible: true
            }
        }

    ]
}
