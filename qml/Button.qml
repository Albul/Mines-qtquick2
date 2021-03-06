import QtQuick 2.0

Item {
    id: container

    property string text
    property bool disabled: false
    signal clicked

    //    width: label.paintedWidth
    width: parent.width
    height: 60 * factor

    Rectangle {
        id: normal
        anchors.fill: parent
        border.color: "#999999"
        border.width: 1 * factor
        radius: 10 * factor
        smooth: true
        gradient: Gradient {
            GradientStop {position: 0.0; color: "#666666"}
            GradientStop {position: 1.0; color: "#222222"}
        }
    }

    Rectangle {
        id: pressed
        anchors.fill: parent
        border.color: "#999999"
        border.width: 1 * factor
        radius: 10 * factor
        smooth: true
        opacity: 0
        gradient: Gradient {
            GradientStop {position: 0.0; color: "#999999"}
            GradientStop {position: 1.0; color: "#333333"}
        }
    }

    Rectangle {
        id: disabled
        anchors.fill: parent
        border.color: "#999999"
        border.width: 1 * factor
        radius: 10 * factor
        smooth: true
        opacity: 0
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#dddddd" }
            GradientStop { position: 1.0; color: "#999999" }
        }
    }

    Text {
        id: label
        anchors.centerIn: parent
        font.family: "Sans"
        font.pixelSize: normal.height / 2
        smooth: true
        color: {
            if (container.disabled)
                "#dddddd"
            else
                "#ffffff"
        }
        text: container.text
    }


    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!container.disabled)
                container.clicked();
        }
        onPressed: {
            if (!container.disabled)
                container.state = "Pressed"
        }
        onReleased: {
            if (!container.disabled)
                container.state = ""
        }
    }

    states: [
        State {
            name: "Pressed"
            PropertyChanges {
                target: pressed; opacity: 1
            }
        },
        State {
            name: "Disabled"
            when: container.disabled == true
            PropertyChanges {
                target: disabled; opacity: 1
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {properties: "opacity"; duration: 100}
    }

}
