import QtQuick 2.2

Item {
    id: progressBar
    width: screen.width-((screen.width/4)*2)
    height: screen.height/108
    clip: true

    property int minimum: 0
    property int maximum: 100
    property int value
    onValueChanged: { progressBar.maximum = root.required }

    Rectangle {
        id: border
        width: progressBar.width
        height: screen.height/540
        color: "transparent"
        border.width: 1
        border.color: Qt.rgba(0.1, 0.1, 0.1, 1)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    Rectangle {
        id: highlight
        height: screen.height/270
        color: "white"
        property int widthDest: ((progressBar.width * (value-minimum))/(maximum-minimum)-4)
        width: highlight.widthDest
        Behavior on width { SmoothedAnimation { velocity: 1200 } }
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
