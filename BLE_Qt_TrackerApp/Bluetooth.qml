import QtQuick 2.0
import QtQuick.Controls 2.15

Page {
    id: btPage
    Column {
        id: column
        x: 0
        y: 0
        width: 200
        height: 600
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 454

        Button {
            id: buttonStart
            y: 800
            width: 200
            text: qsTr("Start")
            font.family: "Tahoma"
            font.pointSize: 20
        }
    }

    Column {
        id: column1
        x: 200
        y: 0
        width: 200
        height: 600
        anchors.top: parent.top
        anchors.topMargin: 454

        Button {
            id: buttonStop
            y:800
            width: 200
            text: qsTr("Stop")
            font.family: "Tahoma"
            font.pointSize: 20
        }
    }

    Column {
        id: column3
        x: 400
        y: 8
        width: 200
        height: 1046
        anchors.top: parent.top
        anchors.bottom: column.bottom
        anchors.topMargin: 8
    }

    Column {
        id: column2
        x: 226
        y: 53
        width: 572
        height: 1040
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 0
    }

    Column {
        id: column4
        x: 598
        y: 8
        width: 200
        height: 1046
        anchors.top: parent.top
        anchors.bottom: column.bottom
        anchors.topMargin: 454

        Button {
            id: buttonReset
            width: 200
            text: qsTr("Reset")
            font.family: "Tahoma"
            font.pointSize: 20
        }

        Button {
            id: buttonDownload
            width: 200
            text: qsTr("Download")
            font.family: "Tahoma"
            font.pointSize: 20
        }
    }

    Column {
        id: column5
        x: 0
        y: 0
        width: 200
        height: 400

        Button {
            id: button
            text: qsTr("Map")
            font.family: "Tahoma"
            font.pointSize: 20
            onClicked: btPage.StackView.view.push("qrc:/MapViewer.qml")
        }
    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.25;height:1040;width:1920}
}
##^##*/
