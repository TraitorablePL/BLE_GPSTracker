import QtQuick 2.5
import QtQuick.Controls 1.4
import QtLocation 5.9
import QtPositioning 5.5

Map {
    id: map

    property int lastX : -1
    property int lastY : -1
    property int pressX : -1
    property int pressY : -1

//    signal showGeocodeInfo()
//    signal geocodeFinished()

    zoomLevel: (maximumZoomLevel - minimumZoomLevel)/2
    center {
        // The Qt Company in Oslo
        latitude: 59.9485
        longitude: 10.7686
    }

//! [mapnavigation]
    focus: true

    PositionSource{
        id: positionSource
        active: followme

        onPositionChanged: {
            map.center = positionSource.position.coordinate
        }
    }

    MapQuickItem {
        id: poiTheQtComapny
        sourceItem: Rectangle { width: 14; height: 14; color: "#e41e25"; border.width: 2; border.color: "white"; smooth: true; radius: 7 }
        coordinate {
            latitude: 59.9485
            longitude: 10.7686
        }
        opacity: 1.0
        anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
    }

    MapQuickItem {
        sourceItem: Text{
            text: "The Qt Company"
            color:"#242424"
            font.bold: true
            styleColor: "#ECECEC"
            style: Text.Outline
        }
        coordinate: poiTheQtComapny.coordinate
        anchorPoint: Qt.point(-poiTheQtComapny.sourceItem.width * 0.5,poiTheQtComapny.sourceItem.height * 1.5)
    }

    MouseArea {
        id: mouseArea
        property variant lastCoordinate
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton //| Qt.RightButton

        onPressed : {
            map.lastX = mouse.x
            map.lastY = mouse.y
            map.pressX = mouse.x
            map.pressY = mouse.y
            lastCoordinate = map.toCoordinate(Qt.point(mouse.x, mouse.y))
        }

        onPositionChanged: {
            if (mouse.button == Qt.LeftButton) {
                map.lastX = mouse.x
                map.lastY = mouse.y
            }
        }
    }
}
