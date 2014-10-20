import QtQuick 2.2

Item {
    id: finder

    property string enableFilter
    property int xFilters: screen.width

    TextInput {
        id: userInput
        color: "black"
        font.family: pidFont.name
        font.bold: true
        font.capitalization: Font.AllUppercase
        font.pixelSize: parent.height/23
        maximumLength: 25
        visible: { if (buttonsFiltersColumn.opacity === 1 && !root.welcome) true; else false }
        enabled: { if (buttonsFiltersColumn.opacity === 1) true; else false }
        anchors.centerIn: parent
        onAccepted: { root.input = userInput.text; root.findSIGNAL_QML(root.input, root.director, root.category, root.quality, root.full, 0, true) }
        onCursorPositionChanged: { if (noResultLabel.visible) noResultLabel.visible = false; userInput.visible = true }
        Keys.onPressed: {
            if (event.key === Qt.Key_H && (event.modifiers & Qt.ControlModifier)) {
                if (!loaderFilter.active) {
                    root.welcome = false
                    screen.state = "showHelp"
                    event.accepted = true
                }
            } else if (event.key === Qt.Key_P && (event.modifiers & Qt.ControlModifier) && !root.welcome) {
                if (!loaderFilter.active)
                    screen.state = "showSetPassword"
                event.accepted = true
            } else if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
                root.quitSIGNAL_QML()
                event.accepted = true
            }
        }
    }
    Text {
        id: noResultLabel
        text: "NO RESULT"
        color: "black"
        font.family: pidFont.name
        font.bold: true
        font.pixelSize: screen.height/23
        visible: false
        anchors.centerIn: parent
    }

    Column {
        id: buttonsFiltersColumn
        spacing: parent.height/54
        visible: { !root.news && screen.state !== "showSetPassword" && screen.state !== "showHelp" && !root.welcome }
        enabled: { !root.news && screen.state !== "showSetPassword" && screen.state !== "showHelp" && !root.welcome }
        opacity: 0      
        anchors.left: parent.left
        anchors.leftMargin: parent.width/24.61
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -parent.height/17.7
        z: 2
        onEnabledChanged: { if (enabled) userInput.forceActiveFocus() }
        Button {
            id: categoryFilter
            width: screen.width/4.75
            height: screen.height/16.61
            label: "CATEGORY"
            labelSize: screen.height/11.5
            labelInColor: Qt.rgba(0.1, 0.1, 0.1, 1)
            labelOutColor: "white"
            onClicked: {
                finder.state = "showFilter"
                enableFilter = "CATEGORY"
            }
        }
        Button {
            id: directorFilter
            width: screen.width/4.68
            height: screen.height/16.61
            label: "DIRECTOR"
            labelSize: screen.height/11.5
            labelInColor: Qt.rgba(0.1, 0.1, 0.1, 1)
            labelOutColor: "white"
            onClicked: {
                finder.state = "showFilter"
                enableFilter = "DIRECTOR"
            }
        }
    }
    Loader {
        id: loaderFilter
        source: "Filters.qml"
        asynchronous: true
        active: false
        anchors.fill: parent
    }
    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            finder.state = "hideFilter"
            event.accepted = true;
            userInput.forceActiveFocus()
        } else if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
            root.quitSIGNAL_QML()
        }
    }
    function filtersManager(filter, label) {
        if (filter === 'categoryFilter')
            root.category = label.toUpperCase()
        else
            root.director = label.toUpperCase()
        finder.state = "hideAll"
        root.findSIGNAL_QML('', root.director, root.category, root.quality, root.full, 0, true)
        noResultLabel.visible = false
    }
    Loader {
        id: loaderSelectors
        source: "Selectors.qml"
        asynchronous: true
        active: true
        visible: { !root.news && screen.state !== "showSetPassword" && screen.state !== "showHelp" && !root.welcome }
        enabled: { !root.news && screen.state !== "showSetPassword" && screen.state !== "showHelp" && !root.welcome }
        opacity: 0
        anchors.fill: parent
    }

    Column {
        id: welcomeRow
        spacing: -parent.height/54
        visible: { root.welcome && !root.news && buttonsFiltersColumn.opacity === 1 }
        anchors.left: parent.left
        anchors.leftMargin: parent.width/20.7
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -parent.height/13.5
        Text {
            id: welcomeLabel
            text: "WELCOME"
            color: "white"
            font.family: pidFont.name
            font.pixelSize: screen.height/11.5
        }
        Text {
            id: welcomeHelpLabel
            text: "CTRL H TO HELP"
            color: Qt.rgba(0.1, 0.1, 0.1, 1)
            font.family: pidFont.name
            font.pixelSize: screen.height/21.5
            anchors.horizontalCenter: welcomeLabel.horizontalCenter
        }
    }

    states: [
        State {
            name: "showNews"
        },
        State {
            name: "show"
        },
        State {
            name: "hide"
        },
        State {
            name: "showFilter"
        },
        State {
            name: "hideFilter"
        },
        State {
            name: "hideAll"
        }
    ]
    transitions: [
        Transition {
            to: "showNews"
            SequentialAnimation {
                NumberAnimation { target: logo; easing.amplitude: 1.65; properties: "opacity"; to: 1.0; duration: 400; easing.type: Easing.OutInElastic }
                ParallelAnimation {
                    NumberAnimation { target: blur; properties: "opacity"; to: 1; duration: 900; easing.type: Easing.InOutQuart }
                    NumberAnimation { target: blur; properties: "radius"; to: 40; duration: 900; easing.type: Easing.InOutQuart }
                }
                PropertyAction { target: buttonsFiltersColumn; property: "opacity"; value: 1.0 }
                PropertyAction { target: loaderSelectors; property: "opacity"; value: 1.0 }
                PropertyAction { target: loader; property: "source"; value: "News.qml" }
            }
        },
        Transition {
            to: "show"
            SequentialAnimation {
                NumberAnimation { target: logo; easing.amplitude: 1.65; properties: "opacity"; to: 1.0; duration: 400; easing.type: Easing.OutInElastic }
                ParallelAnimation {
                    NumberAnimation { target: blur; properties: "opacity"; to: 1; duration: 900; easing.type: Easing.InOutQuart }
                    NumberAnimation { target: blur; properties: "radius"; to: 40; duration: 900; easing.type: Easing.InOutQuart }
                }
                NumberAnimation { target: buttonsFiltersColumn; properties: "opacity"; to: 1.0; duration: 200; easing.type: Easing.InOutQuart }
                NumberAnimation { target: loaderSelectors; properties: "opacity"; to: 1.0; duration: 200; easing.type: Easing.InOutQuart }
            }
        },
        Transition {
            to: "hide"
            SequentialAnimation {
                PropertyAction { target: loaderFilter; property: "source"; value: "" }
                PropertyAction { target: loaderFilter; property: "active"; value: false }
                PropertyAction { target: userInput; property: "opacity"; value: 0 }
                PropertyAction { target: noResultLabel; property: "opacity"; value: 0 }
                PropertyAction { target: buttonsFiltersColumn; property: "opacity"; value: 0 }
                PropertyAction { target: loaderSelectors; property: "opacity"; value: 0 }
                PropertyAction { target: loaderSelectors; property: "source"; value: "" }
                PropertyAction { target: loaderSelectors; property: "active"; value: false }
                PropertyAction { target: blur; property: "opacity"; value: 0 }
                PropertyAction { target: logo; property: "opacity"; value: 0 }
                PropertyAction { target: loader; property: "source"; value: "Wait.qml" }
                PropertyAction { target: loader_finder_output; property: "source"; value: "Output.qml" }
            }
        },
        Transition {
            to: "showFilter"
            SequentialAnimation {
                PropertyAction { target: userInput; property: "visible"; value: false }
                PropertyAction { target: userInput; property: "focus"; value: true }
                PropertyAction { target: noResultLabel; property: "visible"; value: false }
                PropertyAction { target: buttonsFiltersColumn; property: "visible"; value: false }
                PropertyAction { target: loaderSelectors; property: "visible"; value: false }
                PropertyAction { target: loaderFilter; property: "active"; value: true }
                NumberAnimation { target: finder; easing.amplitude: 1.7; properties: "xFilters"; to: 0; duration: 1100; easing.type: Easing.OutQuart }
            }
        },
        Transition {
            to: "hideFilter"
            SequentialAnimation {
                NumberAnimation { target: finder; easing.amplitude: 1.7; properties: "xFilters"; to: screen.width; duration: 1100; easing.type: Easing.OutQuart }
                PropertyAction { target: loaderFilter; property: "active"; value: false }
                PropertyAction { target: buttonsFiltersColumn; property: "visible"; value: true }
                PropertyAction { target: loaderSelectors; property: "visible"; value: true }
                PropertyAction { target: userInput; property: "visible"; value: true }
            }
        },
        Transition {
            to: "hideAll"
            SequentialAnimation {
                PropertyAction { target: loaderSelectors; property: "source"; value: "" }
                PropertyAction { target: loaderSelectors; property: "active"; value: false }
                PropertyAction { target: blur; property: "opacity"; value: 0 }
                PropertyAction { target: logo; property: "opacity"; value: 0 }
                NumberAnimation { target: finder; easing.amplitude: 1.7; properties: "xFilters"; to: screen.width; duration: 1100; easing.type: Easing.OutQuart }
                PropertyAction { target: loaderFilter; property: "source"; value: "" }
                PropertyAction { target: loaderFilter; property: "active"; value: false }
                PropertyAction { target: buttonsFiltersColumn; property: "visible"; value: true }
                PropertyAction { target: loader; property: "source"; value: "Wait.qml" }
                PropertyAction { target: loader_finder_output; property: "source"; value: "Output.qml" }
            }
        }
    ]

    Connections {
        target: cppSignals
        onShowOutputSIGNAL:{
            if (root.director !== "" || root.category !== "")
                finder.state = "hideAll"
            else
                finder.state = "hide"
        }
        onNoResultSIGNAL: {
            userInput.visible = false
            noResultLabel.visible = true
        }
    }

    Component.onCompleted: {
        if(root.news)
            finder.state = "showNews"
        else
            finder.state = 'show'
        root.input = ""
        root.director = ""
        root.category = ""
        userInput.forceActiveFocus()
    }
}
