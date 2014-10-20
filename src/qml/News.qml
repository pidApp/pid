import QtQuick 2.2

Item {
    id: news

    Rectangle {
      id: backgroundLayer
      color: Qt.rgba(0.5, 0.5, 0.5, 0.7)
      anchors.fill: parent
    }

    Rectangle {
        id: layer
        width: parent.width/4
        height: parent.height
        color: "black"
        anchors.centerIn: parent
        Flickable {
            id: flickAreaNews
            contentWidth: newsColumn.width
            contentHeight: newsColumn.height
            flickableDirection: Flickable.VerticalFlick
            clip: true
            anchors.fill: parent
            Column {
                id: newsColumn
                anchors.left: parent.left
                anchors.leftMargin: parent.width/12
                anchors.top: parent.top
                anchors.topMargin: parent.height/43
                spacing: parent.height/216
                Text {
                    id: binary
                    text: "NEWS PID "+binaryVersion+"."+release
                    color: "white"
                    font.family: pidFont.name
                    font.pixelSize: screen.height/23
                }
                Text {
                    text: binaryNews
                    color: "white"
                    font.family: pidFont.name
                    font.bold: true
                    font.pixelSize: screen.height/54
                }
                Text {
                    id: database
                    text: "NEWS DATABASE "+databaseVersion
                    color: "white"
                    font.family: pidFont.name
                    font.pixelSize: screen.height/23
                }
                Text {
                    text: databaseNews
                    color: "white"
                    font.family: pidFont.name
                    font.bold: true
                    font.pixelSize: screen.height/54
                }
            }
        }
        Button {
            id: close
            width: parent.width/22.85
            height: parent.height/34.2
            label: "X"
            labelColor: "white"
            labelSize: screen.height/23
            labelInColor: Qt.rgba(0.1, 0.1, 0.1, 1)
            labelOutColor: "white"
            anchors.right: parent.right
            anchors.rightMargin: parent.width/13.71
            anchors.top: parent.top
            anchors.topMargin: parent.height/47.57
            onClicked: {
                root.news = false
                loader.source = ""
            }
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
            root.quitSIGNAL_QML()
            event.accepted = true;
        }
    }

    Component.onCompleted: { news.forceActiveFocus() }
}
