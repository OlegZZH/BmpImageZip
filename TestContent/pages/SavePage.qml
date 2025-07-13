import QtQuick
import QtQuick.Controls
import "../widgets"
import QtQuick.Dialogs

Item {
    id: savePageContent
    width: 1280
    height: 720

    BackButton {
        id: backButton
        onClicked: {
            mainStackView.replace(selectFilePage, StackView.PopTransition)
        }
    }

    Text {
        id: saveAsLabel
        text: qsTr("Save as")
        anchors.top: parent.top
        anchors.leftMargin: 50
        anchors.topMargin: 150
        font.pixelSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: pathField
        width: 300
        text: testAppModel.saveToPath
        anchors.top: saveAsLabel.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Path")
        enabled: false
    }
    CustomButton {
        text: " Select "
        anchors.verticalCenter: pathField.verticalCenter
        anchors.left: pathField.right
        anchors.leftMargin: 20
        topPadding: 10
        rectangleBorderwidth: 5
        font.pointSize: 10
        FolderDialog {
            id: folderDialog
            onAccepted: {
                const path = selectedFolder.toString().replace("file://", "")
                testAppController.selectSaveAsPath(path)
            }
        }
        onClicked: {

            folderDialog.open()
        }
    }
    TextField {
        id: nameField
        width: 300
        text: testAppModel.currentFile.name.split('.').slice(0, -1).join(
                  '.') + (testAppModel.mode ? "_unpacked" : "_packed")
        anchors.top: pathField.bottom
        anchors.leftMargin: 16
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        placeholderText: qsTr("Name")
    }

    CustomButton {
        id: saveButton
        height: 100
        text: qsTr("Save")
        anchors.left: nameField.left
        anchors.right: nameField.right
        anchors.top: nameField.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 40

        borderColor: "#9f4848"
        onClicked: {
            waitDialog.fillAndOpen()
            var result = testAppController.saveFile(nameField.text + (testAppModel.mode ? ".bmp" : ".barch"))
            result.statusChanged.connect(function (status) {
                waitDialog.close()
                mainStackView.replace(selectFilePage, StackView.PopTransition)
                testAppController.selectPath(testAppModel.currentPath)
            })
        }
    }

    Text {
        id: unitLabel
        text: "+ " + (testAppModel.mode ? ".bmp" : ".barch")
        anchors.verticalCenter: nameField.verticalCenter
        anchors.left: nameField.right
        anchors.leftMargin: 20
        font.pixelSize: 24
    }
}
