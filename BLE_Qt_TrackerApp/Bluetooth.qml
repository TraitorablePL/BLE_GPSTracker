import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: btPage

        width: parent.width
        height: parent.height
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
            implicitHeight: 45
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
        anchors.bottom: buttonDownRec.top
        anchors.left: buttonDownRec.left
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
        width: 250
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

    Button {
        id: buttonStart
        text: qsTr("Start")
        anchors.left: parent.left
        anchors.bottom: menu.top

        background: Rectangle {
            implicitWidth: 125
            implicitHeight: 45
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            color: "#363636"
            border.width: 1
            border.color: "#E3E3E3"
            radius: 5

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    buttonStart.width = buttonStart.width - 7
                    buttonStart.height = buttonStart.height - 5
                }

                onReleased: {
                    buttonStart.width = buttonStart.width + 7
                    buttonStart.height = buttonStart.height + 5
                }
//                onClicked: {
//                    \\something
//                }
            }
        }

        contentItem: Text {
           id: buttonStartText
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           anchors.fill: parent
           text: buttonStart.text
           elide: Text.ElideMiddle
           color: "#E3E3E3"
           wrapMode: Text.WordWrap
        }

    }

Button {
    id: buttonStop
    anchors.left: menu.horizontalCenter
    anchors.bottom: menu.top
    text: qsTr("Stop")

    background: Rectangle {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        implicitWidth: 125
        implicitHeight: 45

        color: "#363636"
        border.width: 1
        border.color: "#E3E3E3"
        radius: 5

        MouseArea {
            anchors.fill: parent
            onPressed: {
                buttonStop.width = buttonStop.width - 7
                buttonStop.height = buttonStop.height - 5
            }

            onReleased: {
                buttonStop.width = buttonStop.width + 7
                buttonStop.height = buttonStop.height + 5
            }
//                onClicked: {
//                    \\something
//                }
        }
    }

    contentItem: Text {
       id: buttonStopText
       horizontalAlignment: Text.AlignHCenter
       verticalAlignment: Text.AlignVCenter
       anchors.fill: parent
       text: buttonStop.text
       elide: Text.ElideMiddle
       color: "#E3E3E3"
       wrapMode: Text.WordWrap
    }

}

    Rectangle{
        id: buttonDownRec
        width: 125
        height: 45
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        Button {
            id: buttonDown
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            text: qsTr("Download")

            background: Rectangle {
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                implicitWidth: 125
                implicitHeight: 45

                color: "#363636"
                border.width: 1
                border.color: "#E3E3E3"
                radius: 5

                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        buttonDown.width = buttonDown.width - 7
                        buttonDown.height = buttonDown.height - 5
                    }

                    onReleased: {
                        buttonDown.width = buttonDown.width + 7
                        buttonDown.height = buttonDown.height + 5
                    }
        //                onClicked: {
        //                    \\something
        //                }
                }
            }

            contentItem: Text {
               id: buttonDownText
               horizontalAlignment: Text.AlignHCenter
               verticalAlignment: Text.AlignVCenter
               anchors.fill: parent
               text: buttonDown.text
               elide: Text.ElideMiddle
               color: "#E3E3E3"
               wrapMode: Text.WordWrap
            }

        }
    }

Button {
    id: buttonRst
    anchors.left: buttonDownRec.right
    anchors.bottom: buttonDownRec.bottom
    text: qsTr("Reset")


    background: Rectangle {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        implicitWidth: 125
        implicitHeight: 45

        color: "#363636"
        border.width: 1
        border.color: "#E3E3E3"
        radius: 5

        MouseArea {
            anchors.fill: parent
            onPressed: {
               buttonRst.width = buttonRst.width - 7
                buttonRst.height = buttonRst.height - 5
            }

            onReleased: {
               buttonRst.width = buttonRst.width + 7
                buttonRst.height = buttonRst.height + 5
            }
//                onClicked: {
//                    \\something
//                }
        }
    }

    contentItem: Text {
       id: buttonRstText
       horizontalAlignment: Text.AlignHCenter
       verticalAlignment: Text.AlignVCenter
       anchors.fill: parent
       text: buttonRst.text
       elide: Text.ElideMiddle
       color: "#E3E3E3"
       wrapMode: Text.WordWrap
    }

}
}
