import QtQuick 2.0

Item {
    id: container

    property string text
    property bool checked: false

    signal stateChanged(bool state)

    width: parent.width
    height: 30

    Item {
        id: basisCircle
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 10
        width: 30
        height: 30

        Rectangle {
            anchors.fill: parent
            border.color: "#8b888b"
            border.width: 1
            radius: width * 0.5
            smooth: true
            color: "#131113"
        }

        Rectangle {
            width: 26
            height: 26
            anchors.centerIn: parent
            border.color: "#434443"
            border.width: 7
            radius: width * 0.5
            smooth: true
            color: "#575757"
        }
    }

    Rectangle {
        id: checkedCircle
        anchors.centerIn: basisCircle
        width: 14
        height: 14
        radius: width * 0.5
        smooth: true
        opacity: 0
        color: "#0db493"
    }

    Text {
//        anchors.centerIn: parent
        anchors.leftMargin: 12
        anchors.left: basisCircle.right
        anchors.horizontalCenter: basisCircle.horizontalCenter

        font.family: "Sans"
        font.pointSize: 15
        smooth: true
        color: "#ffffff"
        text: container.text
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!container.checked) {
                container.checked = !container.checked;
                container.stateChanged(container.checked);
            }
        }
    }

    states: [
        State {
            name: "checked"
            when: checked == true
            PropertyChanges {
                target: checkedCircle; opacity: 1
            }
        },
        State {
            name: "unchecked"
            when: checked == false
            PropertyChanges {
                target: checkedCircle; opacity: 0
            }
        }
    ]

}
