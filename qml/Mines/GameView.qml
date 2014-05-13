import QtQuick 2.0

Item {
    id: gameView
    anchors.fill: parent
    property alias boardGrid: boardGrid

    Image {
        id: bg
        anchors.fill: parent
        source: "images/bg.jpg"
        fillMode: Image.Tile
    }

    // *** Board ***
    Flickable {
        id: boardFlickable
        anchors.centerIn: parent
        anchors.fill: parent
        contentWidth: boardGrid.width
        contentHeight: boardGrid.height + 40
        maximumFlickVelocity: 500
        flickDeceleration: 1000

        Grid {
            id: boardGrid
            anchors.centerIn: parent
            columns: 8
            spacing: 1

            Repeater {
                model: gameModel
                Cell {}
            }
        }
    }

}
