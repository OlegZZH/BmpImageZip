import "../widgets"
import QtQuick

Item {
    id: item1
    CustomButton {
        id: button
        text: "Zip"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.rightMargin: 10
        anchors.top: parent.top
        onClicked: {
            mainStackView.push(selectFilePage)
        }
    }

    CustomButton {
        id: button1
        text: qsTr("Unzip")
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        borderColor: "#4b489f"
        onClicked: {
            mainStackView.push(selectFilePage)
        }
    }
}
