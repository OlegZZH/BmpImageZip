import QtQuick
import QtQuick.Controls
import "../widgets"

Item {
    id: root
    width: 1280
    height: 720
    BackButton {
    }
    Text {
        id: text1
        text: qsTr("Please select a file")
        anchors.top: parent.top
        anchors.topMargin: 100
        font.pixelSize: 46
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Button {
        id: selectButton
        text: "Select file"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: text1.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 200
        anchors.rightMargin: 200
        anchors.topMargin: 150
        anchors.bottomMargin: 100
        font.pointSize: 20
        background: Rectangle {
            id: rectangle
            color: selectButton.down ? Qt.darker("#e0e0e0") : "#e0e0e0"
            radius: 22
            border.color: "#979797"
            border.width: 2
        }
        onClicked: {
            mainStackView.push(previewPage)
        }
    }
}
