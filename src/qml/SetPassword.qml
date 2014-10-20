import QtQuick 2.2

Item {
    id: setPassword

    Rectangle {
        id: layer
        width: parent.width
        height: parent.height/3.5
        color: "black"
        anchors.centerIn: parent
        Text {
            id: label
            text: "INTRO PASSWORD"
            color: "white"
            font.family: pidFont.name
            font.pixelSize: screen.height/23
            anchors.centerIn: parent
        }
        TextInput {
            id: input
            color: "white"
            font.family: pidFont.name
            font.pixelSize: screen.height/43.2
            maximumLength: 16
            echoMode: TextInput.Password
            visible: false
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -screen.height/720
            onCursorPositionChanged: { label.text = ""; input.visible = true }
            onAccepted: {
                if (input.text !== '') {
                    root.passwordHandleSIGNAL_QML(input.text, false, true)
                    input.visible = false
                    input.enabled = false
                    if (root.ok_password) {
                        label.text = ""
                        screen.state = "cleanUp"
                    } else {
                        label.text = "FAIL. TRY LATER"
                        back.start()
                    }
                }
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Escape) {
                    screen.state = "cleanUp"
                    event.accepted = true
                } else if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
                    root.quitSIGNAL_QML()
                    event.accepted = true;
                }
            }
        }
        Timer {
            id: back
            running: false
            repeat: false
            interval: 2000
            onTriggered: { screen.state = "cleanUp" }
        }
    }

    Component.onCompleted: { input.forceActiveFocus() }
}
