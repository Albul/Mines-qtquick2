import QtQuick 2.0
import QtQuick.Window 2.1

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
        anchors.fill: parent
        contentWidth: boardGrid.width + controlPanel.width
        contentHeight: boardGrid.height
        maximumFlickVelocity: 500
        flickDeceleration: 1000

        Grid {
            id: boardGrid
            columns: 8
            spacing: 1 * factor
            x: gameView.width > boardGrid.width? (gameView.width - boardGrid.width) / 2 : 0
            y: gameView.height > boardGrid.height? (gameView.height - boardGrid.height) / 2 : 0
            Repeater {
                model: gameModel
                Cell {}
            }

        }
        onMovementEnded: {
            gameProxy.isPressed = false;
        }
    }

    ControlPanel {
        id: controlPanel
        anchors.right: boardFlickable.right
        anchors.rightMargin: 10 * factor
    }
}
