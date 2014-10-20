import QtQuick 2.2
import QtGraphicalEffects 1.0

Rectangle {
    id: buttonFilter
    height: screen.height/4
    color: "black"
    radius: 2

    ColorAnimation on color { to: "black" }
    ColorAnimation on color { id: inColor; running: false; to: "white"; duration: 200 }
    ColorAnimation on color { id: outColor; running: false; to: "black"; duration: 200 }

    property bool enter
    property bool directorsVisible
    property alias labelText: label.text
    property alias numberLabelText: numberLabel.text
    property alias sourceImage: directorPic.source

    signal clicked()
    
    RectangularGlow {
        id: effect
        color: Qt.rgba(1, 1, 1, 0.4)
        glowRadius: 15
        spread: 0
        cornerRadius: 20
        opacity: 0
        anchors.fill: buttonFilter
    }
    Image {
        id: directorPic
        width: screen.width/11.29
        height: screen.height/5.4
        sourceSize.width: 170
        sourceSize.height: 200
        opacity: 0
        anchors.centerIn: parent
    }

    Text {
        id: numberLabel
        color: "black"
        font.family: pidFont.name
        font.pixelSize: screen.height/21.5
        visible: false
        opacity: 0
        anchors.left: label.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -screen.height/3600
    }
    Text {
        id: label
        color: "white"
        font.family: pidFont.name
        font.capitalization: Font.AllUppercase
        font.pixelSize: screen.height/23
        anchors.centerIn: parent
        ColorAnimation on color { id: inLabelColor; running: false; to: "black"; duration: 200 }
        ColorAnimation on color { id: outLabelColor; running: false; to: "white"; duration: 200 }
    }
    MouseArea {
        id: mousearea
        hoverEnabled: true
        onEntered: { enter = true }
        onHoveredChanged: { enter = false }
        onClicked: { buttonFilter.clicked() }
        anchors.fill: parent
    }
    onEnterChanged: {
        if (enter) {
            if (directorsVisible) {
                inStarPic.start()
                inLabel.start()
                inNLabel.start()
                inColor.start()
                inEffect.start()
            } else {
                inLabelColor.start()
                inNLabel.start()
                inColor.start()
            }
        } else {
            if (directorsVisible) {
                inStarPic.stop()
                inLabel.stop()
                inNLabel.stop()
                inColor.stop()
                inEffect.stop()
                outStarPic.start()
                outLabel.start()
                outNLabel.start()
                outColor.start()
                outEffect.start()
            } else {
                inLabelColor.stop()
                inNLabel.start()
                inColor.stop()
                outLabelColor.start()
                outNLabel.start()
                outColor.start()
            }
        }
    }

    NumberAnimation { id: inStarPic; target: directorPic; properties: "opacity"; to: 1; duration: 1000; easing.type: Easing.InOutQuart }
    NumberAnimation { id: inLabel; target: label; properties: "opacity"; to: 0; duration: 200; easing.type: Easing.InOutQuart }
    NumberAnimation { id: inNLabel; target: numberLabel; properties: "opacity"; to: 1; duration: 200; easing.type: Easing.InOutQuart }
    NumberAnimation { id: inEffect; target: effect; properties: "opacity"; to: 1; duration: 200; easing.type: Easing.InOutQuart }
    NumberAnimation { id: outStarPic; target: directorPic; properties: "opacity"; to: 0; duration: 100; easing.type: Easing.InOutQuart }
    NumberAnimation { id: outLabel; target: label; properties: "opacity"; to: 1; duration: 200; easing.type: Easing.InOutQuart }
    NumberAnimation { id: outNLabel; target: numberLabel; properties: "opacity"; to: 0; duration: 200; easing.type: Easing.InOutQuart }
    NumberAnimation { id: outEffect; target: effect; properties: "opacity"; to: 0; duration: 200; easing.type: Easing.InOutQuart }

    Component.onCompleted: {
        buttonFilter.forceActiveFocus()
        if (directorsVisible)
            numberLabel.visible = false
        else
            numberLabel.visible = true
    }
}
