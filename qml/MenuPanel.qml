import QtQuick 2.0

Item {
    id: menuPanel
    width: parent.width
    height: parent.height
    visible: true

    Frame {
        id: menuPanelFrame
        width: 540 * factor
        height: 415 * factor
        anchors.centerIn: parent

        Text {
            id: title
            anchors.top: parent.top
            anchors.topMargin: 10 * factor * factor
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Sans"
            font.pixelSize: 78 * factor
            smooth: true
            color: "#12938d"
            style: Text.Raised
            styleColor: "black"
            text: "Сапёр"
        }

        Row {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.top: title.bottom
            anchors.topMargin: 10 * factor
            anchors.margins: 10 * factor
            spacing: 10 * factor

            Frame {
                id: aboutArea
                width: 290 * factor
                height: 285 * factor

                gradient: Gradient {
                    GradientStop {position: 0.0; color: "#ffffff"}
                    GradientStop {position: 1.0; color: "#eeeeee"}
                }

                Flickable {
                    id: aboutAreaFlickable
                    anchors.fill: parent
                    contentWidth: aboutArea.width
                    contentHeight: aboutAreaText.height + 20
                    flickableDirection: Flickable.VerticalFlick
                    clip: true
                    Text {
                        id: aboutAreaText
                        width: parent.width - 20 * factor
                        anchors.horizontalCenter: parent.horizontalCenter
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignJustify
                        font.family: "Helvetica"
                        font.pixelSize: 20 * factor
                        textFormat: Text.RichText
                        text: "<br>Эта игра - клон классиче-ского сапера. " +
                              "Смысл игры заключается в том чтобы открыть " +
                              "все ячейки на поле в которых не заложены мины. " +
                              "Цифра в открытой ячейке, указывает на коли-чество мин в соседних ячейках. " +
                              "Эта информация поможет вычислить в каких именно ячейках " +
                              "содержатся мины, и поставить на них флаги. " +
                              "<br><br>Игра создана с помощью технологии Qt Quick. " +
                              "Логика игры реализована на C++, интерфейс на QML. " +
                              "Игра со-здана как обучающее посо-бие для сайта <a href=\"http://gamecook.org\">gamecook.org</a><br>"
                        onLinkActivated: Qt.openUrlExternally(link)
                    }
                }
            }

            Column {
                width: parent.width - aboutArea.width - 10 * factor
                spacing: 10 * factor

                Button {
                    id: buttonRecords
                    text: "Рекорды"
                    onClicked: {
                        menuPanel.state = "hidden";
                        recordsPanel.state = "shown";
                    }
                }

                RadioGroup {
                    id: buttonLevel
                }

                Button {
                    id: buttonNewGame
                    text: "Новая игра"
                    onClicked: {
                        var numCols, numRows, numMines;
                        switch (buttonLevel.state) {
                        case 0:
                            numCols = numRows = 8;
                            numMines = 5;
                            break;
                        case 1:
                            numCols = numRows = 10;
                            numMines = 10;
                            break;
                        case 2:
                            numCols = numRows = 16;
                            numMines = 40;
                            break;
                        }
                        gameView.boardGrid.columns = numCols;
                        gameProxy.createNewGame(numCols, numRows, numMines)
                        menuPanel.state = "hidden";
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges {
                target: menuPanel
                opacity: 0.0
                y: - menuPanelFrame.height
                visible: false
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            properties: "opacity, y"
            duration: 800
        }
        NumberAnimation {
            properties: "visible"
            duration: 900
        }
    }
}
