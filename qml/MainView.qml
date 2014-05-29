import QtQuick 2.0
//import QtQuick.Controls 1.2

Item {

    width: 800
    height: 600

    Image {
        id: bg
        anchors.fill: parent
        source: "qrc:///images/bg.jpg"
        fillMode: Image.Tile
    }

    // *** Game View ***
    GameView {
        id: gameView
        // Gameview is disabled when gameViewHider is shown
        enabled: gameViewHider.state == "hidden"
    }

    // *** Game View Hider ***
    Rectangle {
        id: gameViewHider
        anchors.fill: parent
        color: "black"
        opacity: 0.7

        states: [
            State {
                name: "shown"
                when: menuPanel.state != "hidden" || resultPanel.state == "shown"
                PropertyChanges {
                    target: gameViewHider
                    opacity: 0.7
                }
            },
            State {
                name: "hidden"
                when: menuPanel.state == "hidden"
                PropertyChanges {
                    target: gameViewHider
                    opacity: 0.0
                }
            }
        ]

        transitions: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 800
            }
        }
    }

    // *** Main Menu panel ***
    MenuPanel {
        id: menuPanel
    }

    ResultPanel {
        id: resultPanel
    }

    RecordsPanel {
        id: recordsPanel
    }
}
