import QtQuick 2.15
import QtLocation 5.6
import QtPositioning 5.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.15
import "."

Window {
    id: appWindow

    title: qsTr("TrackerApp GPS")
    height: Screen.height
    width: Screen.width
    visible: true

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Bluetooth {}
    }
}
