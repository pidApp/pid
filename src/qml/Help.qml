import QtQuick 2.2

Item {
    id: help

    Rectangle {
        id: pidLayer
        width: parent.width/4
        color: "black"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Column {
            spacing: parent.height/216
            anchors.left: parent.left
            anchors.leftMargin: parent.width/12
            anchors.top: parent.top
            anchors.topMargin: parent.height/43
            Text {
                text: "PID "+binaryVersion+"."+release+" DATABASE "+databaseVersion+"<br/>"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "COLLABORATE"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "<style type='text/css'> a:link{color:#1a1a1a;font-style:normal;text-decoration:none} </style>"+
                      "BUGS &nbsp; <a href=\'http://google.com\'>GITHUB.COM/PIDAPP/BUGS <font color='#ffffff'>➟<font/></a><br/>"+
                      "CODE &nbsp; <a href=\'http://google.com\'>GITHUB.COM/PIDAPP <font color='#ffffff'>➟<font/></a><br/>"+
                      "TORRENTS &nbsp; <a href=\'http://clarin.com\'>GITHUB.COM/PIDAPP/TORRENT <font color='#ffffff'>➟<font/></a><br/>"+
                      "TRANSLATIONS &nbsp; <a href=\'http://google.com\'>GITHUB.COM/PIDAPP/TRANSLATE <font color='#ffffff'>➟<font/></a><br/>"+
                      "BTC &nbsp; <font color='#1a1a1a'>1LtU9rMsQ41rCqsJAvMtw89TA5XT2dW7f9</font><br/>"+
                      "SHARE &nbsp; <a href=\'http://google.com\'>PID.NET <font color='#ffffff'>➟<font/></a><br/>"+
                      "CONTACT &nbsp; <font color='#1a1a1a'>PID@MAIL.COM</font><br/><br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.pixelSize: screen.height/54
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Text {
                text: "LICENSE"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "PID Is Free Software and free. Made by users for users.<br/><br/>"+
                      "GPL 2.0"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/54
            }
            Text {
                text: "<font color='#1a1a1a'>This program is distributed in the hope that it will be useful</font><br/>"+
                      "<font color='#1a1a1a'>but WITHOUT ANY WARRANTY; without even the implied warranty of</font><br/>"+
                      "<font color='#1a1a1a'>MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.</font><br/>"+
                      "<font color='#1a1a1a'>See the GNU General Public License for more details.</font>"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/74
            }
        }
    }
    Rectangle {
        id: shortcutsLayer
        width: parent.width/4
        color: "black"
        anchors.top: parent.top
        anchors.left: pidLayer.right
        anchors.bottom: parent.bottom
        Column {
            spacing: parent.height/216
            anchors.left: parent.left
            anchors.leftMargin: parent.width/5.3
            anchors.top: parent.top
            anchors.topMargin: parent.height/43
            Text {
                text: "SHORTCUTS<br/>"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "GENERAL"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "ESC &nbsp; <font color='#1a1a1a'>BACK</font><br/>"+
                      "CTRL H &nbsp; <font color='#1a1a1a'>HELP</font><br/>"+
                      "CTRL P &nbsp; <font color='#1a1a1a'>PASSWORD</font><br/>"+
                      "CTRL Q &nbsp; <font color='#1a1a1a'>CLOSE</font><br/>"+
                      "ALT TAB &nbsp; <font color='#1a1a1a'>PID DESKTOP</font><br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.pixelSize: screen.height/54
            }
            Text {
                text: "FINDER"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "INTRO &nbsp; <font color='#1a1a1a'>FIND</font><br/>"+
                      "UP DOWN &nbsp; <font color='#1a1a1a'>OFFSET FIVE MOVIES</font><br/>"+
                      "LEFT RIGHT &nbsp; <font color='#1a1a1a'>CHANGE MOVIE</font><br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.pixelSize: screen.height/54
            }
            Text {
                text: "PLAYER"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "SPACE &nbsp; <font color='#1a1a1a'>PAUSE</font><br/>"+
                      "CTRL L &nbsp; <font color='#1a1a1a'>LOOP</font><br/>"+
                      "UP DOWN &nbsp; <font color='#1a1a1a'>VOLUME</font><br/>"+
                      "LEFT RIGHT &nbsp; <font color='#1a1a1a'>OFFSET</font>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.pixelSize: screen.height/54
            }
        }
    }
    Rectangle {
        id: recomendationsLayer
        width: parent.width/4
        color: "black"
        anchors.top: parent.top
        anchors.left: shortcutsLayer.right
        anchors.bottom: parent.bottom
        Column {
            spacing: parent.height/216
            anchors.left: parent.left
            anchors.leftMargin: parent.width/25
            anchors.top: parent.top
            anchors.topMargin: parent.height/43
            Text {
                text: "RECOMENDATIONS<br/>"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "RESOLUTIONS"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "⍿ &nbsp; <font color='#1a1a1a'>1920X1080</font><br/>"+
                      "⍿ &nbsp; <font color='#1a1a1a'>1440X975</font><br/>"+
                      "⍿ &nbsp; <font color='#1a1a1a'>1280X720</font><br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.pixelSize: screen.height/54
            }
            Text {
                text: "UPDATES"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "Accept them. Are fast and mostly of the<br/>"+
                      "database with new movies.<br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/54
            }
            Text {
                text: "TRACKING"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "Those who create this software agree not to<br/>"+
                      "collect any user data. Note that this software<br/>"+
                      "does not use encrypted connections. So it<br/>"+
                      "does not ensure that third parties do not spy<br/>"+
                      "what you see.<br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/54
            }
            Text {
                text: "TAKE PART"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "If you use this software, consider collaborate.<br/>"+
                      "This is the only way we can move forward."
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/54
            }
        }
    }
    Rectangle {
        id: troubleshootingLayer
        width: parent.width/4
        color: "black"
        anchors.top: parent.top
        anchors.left: recomendationsLayer.right
        anchors.bottom: parent.bottom
        Column {
            spacing: parent.height/216
            anchors.left: parent.left
            anchors.leftMargin: parent.width/12
            anchors.top: parent.top
            anchors.topMargin: parent.height/43
            Text {
                text: "TROUBLESHOOTING<br/>"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "BITTORRENT"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "<style type='text/css'> a:link{color:#1a1a1a;font-style:normal;text-decoration:none} </style>"+
                      "<font color='#1a1a1a'>The movies are not downloaded</font><br/>"+
                      "You probably have blocked the ports used<br/>"+
                      "by BitTorrent in your firewall or ISP.<br/>"+
                      "<a href=\'http://google.com\'>Read more <font color='#ffffff'>➟<font/></a><br/><br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/54
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Text {
                text: "CODECS"
                color: "white"
                font.family: pidFont.name
                font.pixelSize: screen.height/23
            }
            Text {
                text: "<style type='text/css'> a:link{color:#1a1a1a;font-style:normal;text-decoration:none} </style>"+
                      "<font color='#1a1a1a'>The movies do not play</font><br/>"+
                      "You probably do not have installed<br/>"+
                      "the necessary video codecs.<br/>"+
                      "<a href=\'http://google.com\'>Read more <font color='#ffffff'>➟<font/></a><br/><br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/54
                textFormat: Text.RichText
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Text {
                text: "If you have problems to use PID, Contact us.<br/>"
                color: "white"
                font.family: pidFont.name
                font.bold: true
                font.italic: true
                font.pixelSize: screen.height/54
            }
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            screen.state = "cleanUp"
            event.accepted = true;
        } else if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
            root.quitSIGNAL_QML()
            event.accepted = true;
        }
    }

    Component.onCompleted: { help.forceActiveFocus() }
}
