import QtQuick 2.0

Item {

    width: 800
    height: 600

    Image {
        id: bg
        anchors.fill: parent
        source: "images/bg.jpg"
        fillMode: Image.Tile
    }

    // *** Game View ***
    GameView {
        id: gameView
        // Gameview is disabled when gameViewHider is shown
        enabled: gameViewHider.state == "hide"
    }

    // *** Game View Hider ***
    Rectangle {
        id: gameViewHider
        anchors.fill: parent
        color: "black"
        opacity: 0.7

        states: [
        State {
            name: "hide"
            when: menuPanel.state == "hide"
            PropertyChanges {
                target: gameViewHider
                opacity: 0.0
            }
        }
        ]

        transitions: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 400
            }
        }
    }

    // *** Main Menu panel ***
    MenuPanel {
        id: menuPanel
    }

    ResultPanel {
        id: resultPanel
        visible: false
    }

}
