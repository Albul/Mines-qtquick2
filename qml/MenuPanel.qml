import QtQuick 2.0

Item {
    id: menuPanel
    width: parent.width
    height: parent.height

    Frame {
        id: menuPanelFrame
        width: 540
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
                text: "Сапёр"
            }
        }

        Row {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.top: gameLogo.bottom
            anchors.margins: 10
            spacing: 10

            Frame {
                id: aboutArea
                width: 290
                height: 285

                gradient: Gradient {
                    GradientStop {position: 0.0; color: "#ffffff"}
                    GradientStop {position: 1.0; color: "#eeeeee"}
                }

                Flickable {
                    id: aboutAreaFlickable
                    anchors.fill: parent
                    contentWidth: aboutArea.width
                    contentHeight: aboutAreaText.height + aboutAreaLogo.height + 20
                    flickableDirection: Flickable.VerticalFlick
                    clip: true
                    Text {
                        id: aboutAreaText
                        width: parent.width - 20
                        anchors.horizontalCenter: parent.horizontalCenter
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Helvetica"
                        font.pointSize: 15
                        text: "\nThis game is the classical 5-in-a-row, also " +
                              "known as tic-tac-toe or Gomoku. Players place their " +
                              "tiles in turns, anywhere in the 19x19 size board. " +
                              "The winner is the first player to get an unbroken " +
                              "row of five stones horizontally, vertically, or " +
                              "diagonally.\n\nGame logic is implemented with Qt " +
                              "C++ and the UI with QML Declarative UI.\n\nEnjoy! =)\n"
                    }
                    Image {
                        id: aboutAreaLogo
                        source: "images/quit.png"
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: aboutAreaText.bottom
                        anchors.topMargin: 10
                    }
                }
            }

            Column {
                width: parent.width - aboutArea.width - 10
                spacing: 10
                opacity: 1
                Button {
                    id: buttonRecords
                    text: "Рекорды"
                }

                RadioGroup {
                    id: buttonLevel
                    width: parent.width
                    height: 146
                }

                Button {
                    id: buttonNewGame
                    text: "Новая игра"
                    onClicked: {
                        var numCols, numRows, numMines;
                        switch (buttonLevel.state) {
                        case 0:
                            numCols = numRows = 8;
                            numMines = 10;
                            break;
                        case 1:
                            numCols = numRows = 10;
                            numMines = 15;
                            break;
                        case 2:
                            numCols = numRows = 16;
                            numMines = 40;
                            break;
                        }
                        gameView.boardGrid.columns = numCols;
                        gameProxy.createNewGame(numCols, numRows, numMines)
                        menuPanel.state = "hide";
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "hide"
            PropertyChanges {
                target: menuPanel
                opacity: 0.0
                y: - menuPanelFrame.height
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            properties: "opacity, y"
            duration: 400
        }
    }
}
