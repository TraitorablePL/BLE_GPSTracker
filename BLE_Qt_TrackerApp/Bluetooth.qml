import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: btPage
    width: 300
    height: 600
    property bool deviceState: device.state
    onDeviceStateChanged: {
        if (!device.state)
            info.visible = false;
    }

    Button {
        id: button
        text: qsTr("Map")
        font.family: "Tahoma"
        font.pointSize: 20
        onClicked: btPage.StackView.view.push("qrc:/MapViewer.qml")

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            color: button.down ? "#d6d6d6" : "#f6f6f6"
            border.color: "#26282a"
            border.width: 1
            radius: 4
        }
    }

//    Header {
//        id: header
//        anchors.top: parent.top
//        headerText: "Start Discovery"
//    }

    Dialog {
        id: info
        anchors.centerIn: parent
        visible: false
    }

    ListView {
        id: theListView
        width: parent.width
        clip: true

        anchors.top: header.bottom
        anchors.bottom: connectToggle.top
        model: device.devicesList

        delegate: Rectangle {
            id: box
            height:100
            width: parent.width
            color: "lightsteelblue"
            border.width: 2
            border.color: "black"
            radius: 5

            Component.onCompleted: {
                info.visible = false;
                header.headerText = "Select a device";
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    device.scanServices(modelData.deviceAddress);
                    pageLoader.source = "Services.qml"
                }
            }

            Label {
                id: deviceName
                textContent: modelData.deviceName
                anchors.top: parent.top
                anchors.topMargin: 5
            }

            Label {
                id: deviceAddress
                textContent: modelData.deviceAddress
                font.pointSize: deviceName.font.pointSize*0.7
                anchors.bottom: box.bottom
                anchors.bottomMargin: 5
            }
        }
    }

    Menu {
        id: connectToggle

        menuWidth: parent.width
        anchors.bottom: menu.top
        menuText: { if (device.devicesList.length)
                        visible = true
                    else
                        visible = false
                    if (device.useRandomAddress)
                        "Address type: Random"
                    else
                        "Address type: Public"
        }

        onButtonClick: device.useRandomAddress = !device.useRandomAddress;
    }

    Menu {
        id: menu
        anchors.bottom: parent.bottom
        menuWidth: parent.width
        menuHeight: (parent.height/6)
        menuText: device.update
        onButtonClick: {
            device.startDeviceDiscovery();
            // if startDeviceDiscovery() failed device.state is not set
            if (device.state) {
                info.dialogText = "Searching...";
                info.visible = true;
            }
        }
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
    }
}
