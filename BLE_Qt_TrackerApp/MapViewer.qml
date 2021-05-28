import QtQuick 2.5
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.15
import QtQml 2.15
import "."

Page {
    id: mapPage

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

    Button {
        id: btButton
        x: 0
        y: 0
        text: qsTr("BT")
        font.family: "Tahoma"
        font.pointSize: 20
        onClicked: mapPage.StackView.view.push("qrc:/Bluetooth.qml")

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            color: button.down ? "#d6d6d6" : "#f6f6f6"
            border.color: "#26282a"
            border.width: 1
            radius: 4
        }
    }
}
