import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: btPage
    width: 800
    height: 600
    property bool deviceState: device.state
    onDeviceStateChanged: {
        if (!device.state)
            info.visible = false;
    }

    Button {
        id: buttonMap
        text: qsTr("Map")
        anchors.right: parent.right
        anchors.top: parent.top

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 40
            anchors.right: parent.right
            anchors.top: parent.top
            color: "#363636"
            border.width: 1
            border.color: "#E3E3E3"
            radius: 5

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    buttonMap.width = buttonMap.width - 7
                    buttonMap.height = buttonMap.height - 5
                }

                onReleased: {
                    buttonMap.width = buttonMap.width + 7
                    buttonMap.height = buttonMap.height + 5
                }
                onClicked: {
                    btPage.StackView.view.push("qrc:/MapViewer.qml")
                }
            }
        }

        contentItem: Text {
           id: buttonMapText
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           anchors.fill: parent
           text: buttonMap.text
           elide: Text.ElideMiddle
           color: "#E3E3E3"
           wrapMode: Text.WordWrap
        }

    }

    Header {
        id: header
        anchors.top: parent.top
        headerText: "Start Discovery"
    }

    Dialog {
        id: info
        anchors {
            left: parent.left
            verticalCenter: parent.verticalCenter
        }
        visible: false
    }

    ListView {
        id: theListView
        width: 250
        clip: true

        anchors.top: header.bottom
        anchors.bottom: connectToggle.top
        model: device.devicesList

        delegate: Rectangle {
            id: box
            height:100
            width: 250
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
                text: modelData.deviceName
                anchors.top: parent.top
                anchors.topMargin: 5
            }

            Label {
                id: deviceAddress
                text: modelData.deviceAddress
                font.pointSize: deviceName.font.pointSize*0.7
                anchors.bottom: box.bottom
                anchors.bottomMargin: 5
            }
        }
    }

    Menu {
        id: connectToggle

        width: 250
        anchors.top: menu.top
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
        width: 250
        height: 80
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
