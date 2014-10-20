import QtQuick 2.2

Item {
    id: errorDatabaseMessage

    Rectangle {
        id: layer
        width: parent.width
        height: parent.height/3.5
        color: "black"
        anchors.centerIn: parent
        Column {
            id: errorColumn
            spacing: parent.height/216
            anchors.centerIn: parent
            Text {
                id: errorInformationLabel
                text: "DATABASE IS CORRUPTED"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                id: getDbInformationLabel
                text:"<style type='text/css'> a:link{color:#1a1a1a;font-style:normal;text-decoration:none} </style>"+
                     "GET LATEST DATABASE &nbsp;<a href=\'http://google.com\'>DL.BINTRAY.COM/DB <font color='#ffffff'>➟<font/></a>" // TODO: Url real db.
                color: Qt.rgba(0.1, 0.1, 0.1, 1)
                font.family: pidFont.name
                font.bold: true
                font.pixelSize: screen.height/54
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
                anchors.horizontalCenter: errorInformationLabel.horizontalCenter
            }
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
            root.quitSIGNAL_QML()
            event.accepted = true;
        }
    }

    Component.onCompleted: errorDatabaseMessage.forceActiveFocus()
}
