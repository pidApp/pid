import QtQuick 2.2

Rectangle {
    id: filters
    x: xFilters
    width: screen.width
    height: screen.height
    color: "black"
    z: 1

    Flickable {
        id: flickAreaFilters
        contentWidth: filtersGrid.width
        contentHeight: filtersGrid.height
        flickableDirection: Flickable.VerticalFlick
        clip: true
        anchors.fill: parent
        Grid {
            id: filtersGrid
            spacing: 0
            Repeater {
                id: categoryRows
                model: categoryList[0]
                delegate: ButtonFilter {
                    width: filters.width/4
                    labelText: { if (numberCategoryList[index] !== '0') categoryList[index+1]+"∙"; else categoryList[index+1] }
                    numberLabelText: { if (numberCategoryList[index] !== '0') numberCategoryList[index]; else '' }
                    directorsVisible: false
                    visible: { if (enableFilter === 'CATEGORY' ) true; else false }
                    enabled: { if (enableFilter === 'CATEGORY' ) true; else false }
                    onClicked: { 
                        if (numberCategoryList[index] !== '0')
                            filtersManager('categoryFilter', labelText)
                    }
                }
            }
            Repeater {
                id: directorRows
                model: directorList[0]
                delegate: ButtonFilter {
                    width: filters.width/4
                    sourceImage: {
                        if (nDirectorListList[index] !== '0')
                            "qrc:/resources/images/directors/"+directorList[index+1]+".jpg"
                        else
                            "qrc:/resources/images/available/directorNotAvailable.png"
                    }
                    labelText: directorList[index+1]
                    numberLabelText: ''
                    directorsVisible: true
                    visible: { if (enableFilter === 'DIRECTOR') true; else false }
                    enabled: { if (enableFilter === 'DIRECTOR') true; else false }
                    onClicked: { 
                        if (nDirectorListList[index] !== '0')
                        filtersManager('directorFilter', labelText)
                    }
                }
            }
        }
    }
}
