import QtQuick
import QtQuick.Controls

Item {
    id: root
    implicitHeight: 200
    implicitWidth: 200

    BusyIndicator {
        id: busyIndicator
        anchors.fill: parent
        anchors.bottomMargin: 50
    }

    Text {
        id: text1
        color: "#ffffff"
        text: qsTr("Wait, it's being processed")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        font.pixelSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
