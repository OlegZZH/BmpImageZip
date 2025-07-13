import QtQuick
import QtQuick.Controls
import "../widgets"

Rectangle {
    id: errorModal
    width: 360
    height: 240
    radius: 20
    property string message: " somthing wrong"
    implicitWidth: 360
    implicitHeight: 240
    Text {
        id: name
        color: "#ff0000"
        text: qsTr("Error")
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 29
    }
    Text {
        id: messageLabel
        text: qsTr("Message: ") + message
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: name.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        font.pointSize: 16
        font.bold: false
    }

    CustomButton {
        id: customButton
        text: "Ok"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: messageLabel.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 60
        anchors.rightMargin: 60
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        onClicked: {
            errorDialog.close()
        }
    }
}
