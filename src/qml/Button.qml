import QtQuick 2.2

Rectangle {
    id: button
    color: "transparent"

    property bool enter
    property alias label: label.text
    property alias labelColor: label.color
    property alias labelSize: label.font.pixelSize
    property alias labelBold: label.font.bold
    property color labelInColor
    property color labelOutColor

    signal clicked()
    
    Text {
        id: label
        color: "white"
        font.family: pidFont.name
        font.bold: false
        font.pixelSize: labelSize
        anchors.verticalCenter: parent.verticalCenter
        ColorAnimation on color { id: inColor; running: false; to: labelInColor; duration: 200 }
        ColorAnimation on color { id: outColor; running: false; to: labelOutColor; duration: 300 }
    }
    MouseArea {
        id: mousearea
        hoverEnabled: true
        onEntered: { enter = true }
        onHoveredChanged: { enter = false }
        onClicked: { button.clicked() }
        anchors.fill: parent
    }
    onEnterChanged: {
        if (enter) {
            inColor.start()
        } else {
            inColor.stop()
            outColor.start()
        }
    }
}
