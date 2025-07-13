import QtQuick
import QtQuick.Controls

Rectangle {
    id: fileDelegate
    height: 40
    implicitWidth: 250
    border.color: selected ? "#569f48" : "#000000"
    property alias mouseArea: mouseArea
    property alias fileNameText: fileName.text
    property int sizeB: 0
    property bool selected: false
    radius: 6
    color: {
        if (mouseArea.containsMouse) {
            if (mouseArea.containsPress) {
                return Qt.darker("#b1b1b1")
            } else {
                return "#b1b1b1"
            }
        } else {
            return "#dbdbdb"
        }
    }

    Text {
        id: fileName
        text: qsTr("Image.bmp")
        elide: Text.ElideMiddle
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: byteLabel.left
        anchors.leftMargin: 5
        anchors.rightMargin: 10
    }

    Text {
        id: byteLabel
        width: 100
        text: sizeB + "B"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
        horizontalAlignment: Text.AlignRight
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }
}
