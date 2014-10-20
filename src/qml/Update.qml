import QtQuick 2.2

Item {
    id: update

    Image {
        id: networkIcon
        width: parent.width/5.36
        height: parent.height/3.01
        source: "qrc:/resources/images/pid/network.png"
        sourceSize.width: 358
        sourceSize.height: 358
        visible: { root.showNetworkIcon }
        anchors.centerIn: parent
    }

    Rectangle {
      id: backgroundLayer
      width: parent.width
      height: parent.height/3.5
      color: "black"
      visible: { !root.showNetworkIcon && statusLabel.text != ""}
      anchors.centerIn: parent
    }
    Column {
        spacing: { if (informationLabel.text !="") -parent.height/72; else parent.height/216 }
        anchors.centerIn: parent

        Text {
            id: statusLabel
            text: root.status
            color: "white"
            font.family: pidFont.name
            font.pixelSize: screen.height/23
        }
        Text {
            id: informationLabel
            text: root.information
            color: Qt.rgba(0.1, 0.1, 0.1, 1)
            font.family: pidFont.name
            font.pixelSize: screen.height/23
            anchors.horizontalCenter: statusLabel.horizontalCenter
        }
        Row {
            id: buttonsRow
            spacing: screen.width/192
            anchors.horizontalCenter: statusLabel.horizontalCenter
            Button {
                id: get
                width: screen.width/25.26
                height: screen.height/36
                label: "GET"
                labelColor: "white"
                labelSize: screen.height/23
                labelInColor: Qt.rgba(0.1, 0.1, 0.1, 1)
                labelOutColor: "white"
                visible: { root.requireConfirmation }
                enabled: { root.requireConfirmation }
                onClicked: {
                    root.status = ""
                    root.information = ""
                    root.getFilesSIGNAL_QML()
                }
            }
            Button {
                id: skip
                width: screen.width/22.32
                height: screen.height/36
                label: "SKIP"
                labelColor: "white"
                labelSize: screen.height/23
                labelInColor: Qt.rgba(0.1, 0.1, 0.1, 1)
                labelOutColor: "white"
                visible: { root.requireConfirmation }
                enabled: { root.requireConfirmation }
                onClicked: { root.skipSIGNAL_QML() }
            }
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
            root.quitSIGNAL_QML()
            event.accepted = true;
        }
    }

    Component.onCompleted: { update.forceActiveFocus() }
}
