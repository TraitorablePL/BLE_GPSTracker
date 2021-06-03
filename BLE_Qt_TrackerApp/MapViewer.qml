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
        id: buttonBT
        text: qsTr("BT")
        anchors.right: parent.right
        anchors.top: parent.top

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            anchors.right: parent.right
            anchors.top: parent.top
            color: "#E3E3E3"
            border.width: 1
            border.color: "#363636"
            radius: 5

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    buttonBT.width = buttonBT.width - 7
                    buttonBT.height = buttonBT.height - 5
                }

                onReleased: {
                    buttonBT.width = buttonBT.width + 7
                    buttonBT.height = buttonBT.height + 5
                }
                onClicked: {
                    mapPage.StackView.view.push("qrc:/Bluetooth.qml")
                }
            }
        }

        contentItem: Text {
           id: buttonBtText
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           anchors.fill: parent
           text: buttonBT.text
           elide: Text.ElideMiddle
           color: "#363636"
           wrapMode: Text.WordWrap
        }

    }


}
