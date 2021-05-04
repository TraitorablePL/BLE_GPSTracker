import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Window 2.0

Rectangle {
    width: Screen.width
    height: Screen.height
    visible: true

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: mapview
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(50.0647, 19.9450)
        zoomLevel: 14

        MapItemView{
            model: markerModel
            delegate: mapcomponent
        }
    }

    Component {
        id: mapcomponent
        MapQuickItem {
            id: marker
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: position

            sourceItem: Image {
                id: image
                source: "http://maps.gstatic.com/mapfiles/ridefinder-images/mm_20_red.png"
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.RightButton

        onPressAndHold:  {
            var coordinate = mapview.toCoordinate(Qt.point(mouse.x,mouse.y))
            markerModel.addMarker(coordinate)
        }
    }
}


//import QtQuick 2.6
//import QtQuick.Controls 2.0
//import io.qt.examples.backend 1.0

//ApplicationWindow {
//    id: root
//    width: 300
//    height: 480
//    visible: true

//    BackEnd {
//        id: backend
//    }

//    TextField {
//        text: backend.userName
//        placeholderText: qsTr("User name")
//        anchors.centerIn: parent

//        onTextChanged: backend.userName = text
//    }
//}
