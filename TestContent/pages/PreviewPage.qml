import QtQuick
import QtQuick.Controls
import "../widgets"

Item {
    id: root
    width: 1280
    height: 720

    BackButton {
        id: backButton
    }

    Image {
        id: image
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 100
        anchors.bottomMargin: 20
        source: "../../conditions/images/test-image-1-gs.bmp"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: text1
        text: qsTr("Preview")
        anchors.top: parent.top
        anchors.topMargin: 30
        font.pixelSize: 36
        anchors.horizontalCenter: image.horizontalCenter
    }

    Text {
        id: text2
        text: qsTr("Save as")
        anchors.left: image.right
        anchors.top: image.top
        anchors.leftMargin: 50
        anchors.topMargin: 0
        font.pixelSize: 24
    }

    TextField {
        id: textField
        width: 300
        text: "/home/oleg/Test"
        anchors.verticalCenter: text2.verticalCenter
        anchors.left: text2.right
        anchors.leftMargin: 16
        placeholderText: qsTr("Path")
    }
    CustomButton {
        text: " Select "
        anchors.verticalCenter: textField.verticalCenter
        anchors.left: textField.right
        anchors.leftMargin: 20
        topPadding: 10
        rectangleBorderwidth: 5
        font.pointSize: 10
    }

    CustomButton {
        id: button
        height: 200
        text: qsTr("Convert")
        anchors.verticalCenter: image.verticalCenter
        anchors.left: image.right
        anchors.right: parent.right
        anchors.leftMargin: 100
        anchors.rightMargin: 100
        borderColor: "#9f4848"
        onClicked: {
            waitDialog.fillAndOpen()
        }
    }
}
