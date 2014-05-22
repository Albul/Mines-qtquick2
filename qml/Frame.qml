import QtQuick 2.0

Rectangle {
    width: parent.width
    height: parent.height
    border.color: "#999999"
    border.width: 2 * factor
    radius: 10 * factor
    smooth: true

    gradient: Gradient {
        GradientStop {position: 0.0; color: "#eeeeee"}
        GradientStop {position: 1.0; color: "#dddddd"}
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
        }
    }
}
