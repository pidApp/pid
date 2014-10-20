import QtQuick 2.2

Rectangle {
    id: buttonScenne
    width: screen.width/22.58
    height: screen.height/12.70
    color: "transparent"

    property bool enter
    property string magnet
    property int scene
    property int fit
    property int size: screen.height/12.70
    
    Image {
        id: icon
        width: size
        height: size
        source: "qrc:/resources/images/output/openScene.png"
        smooth: true
        anchors.centerIn: parent
    }
    MouseArea {
        id: mousearea
        hoverEnabled: true
        onEntered: { enter = true }
        onHoveredChanged: { enter = false }
        onClicked: {
            if (!onShowPlayerLayer) {
                onShowPlayerLayer = true
                root.torrentHandleSIGNAL_QML(magnet, scene, fit, false)
            }
        }
        anchors.fill: parent
    }
    onEnterChanged: {
        if (enter) {
            inEffect.start()
        } else {
            inEffect.stop()
            outEffect.start()
        }
    }
    NumberAnimation { id: inEffect; target: buttonScenne; properties: "size"; to: screen.height/12; duration: 200; easing.type: Easing.InOutQuart }
    NumberAnimation { id: outEffect; target: buttonScenne; properties: "size"; to: screen.height/12.70; duration: 300; easing.type: Easing.InOutQuart }
}
