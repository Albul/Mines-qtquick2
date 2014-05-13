import QtQuick 2.0

Rectangle {
    id: container

    property int state: 0

    border.color: "#999999"
    border.width: 1
    radius: 10
    smooth: true
    gradient: Gradient {
        GradientStop {position: 0.0; color: "#666666"}
        GradientStop {position: 1.0; color: "#222222"}
    }

    Text {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 8
        anchors.topMargin: 2
        font.family: "Sans"
        font.pointSize: 9
        font.italic: true
        smooth: true
        color: "white"
        text: "Уровень сложности:"
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: 26
        spacing: 10

        RadioButton {
            id: buttonEasy
            text: "Легкий"
            checked: true
            onStateChanged: {
                if (state) {
                    buttonHard.checked = false;
                    buttonMiddle.checked = false;
                    container.state = 0;
                }
            }
        }

        RadioButton {
            id: buttonMiddle
            text: "Средний"
            onStateChanged: {
                if (state) {
                    buttonEasy.checked = false;
                    buttonHard.checked = false;
                    container.state = 1;
                }
            }
        }

        RadioButton {
            id: buttonHard
            text: "Сложный"
            onStateChanged: {
                if (state) {
                    buttonEasy.checked = false;
                    buttonMiddle.checked = false;
                    container.state = 2;
                }
            }
        }
    }
}
