import QtQuick 2.2

Item {
    id: askPassword

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
            focus: true
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -screen.height/720
            onCursorPositionChanged: { label.text = ""; input.visible = true }
            onAccepted: {
                if (input.text !== '') {
                    root.passwordHandleSIGNAL_QML(input.text, false, false)
                    if (root.fail_password) {
                        input.visible = false
                        label.color = Qt.rgba(0.1, 0.1, 0.1, 1)
                        label.text = "WRONG PASSWORD"
                    }
                }
            }
            Keys.onPressed: {
                if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
                    root.quitSIGNAL_QML()
                    event.accepted = true;
                }
            }
        }
    }
}
