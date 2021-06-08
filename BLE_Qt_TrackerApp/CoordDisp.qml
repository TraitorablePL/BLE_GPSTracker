import QtQuick 2.15
Item {
    id: root
    width: 320
    height: 480

    Rectangle {
        color: "#FFFFFF"
        border.width: 2
        border.color: "#E3E3E3"
        width: 320
        height: 480
    }


    Rectangle {

        width: 300
        height: 460
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Column {
            spacing: 20

            Text {
                text:'Coordinates in memory:'
                color: "black"

            }
            ListView {
                width: 300; height: 420

                model: markerModel
                delegate: Text {
                text: " " + position;
                }
            }
        }
    }
}
