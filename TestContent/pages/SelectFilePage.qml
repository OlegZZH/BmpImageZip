import QtQuick
import QtQuick.Controls
import "../widgets"
import QtQuick.Dialogs

Item {
    id: selectFilePageContent
    width: 1280
    height: 720

    Text {
        id: pleaseLabel
        text: qsTr("Please select a file")
        anchors.left: previewImage.right
        anchors.top: parent.top
        anchors.leftMargin: 100
        anchors.topMargin: 100
        font.pixelSize: 36
    }

    TextField {
        id: pathField
        width: 300
        anchors.left: previewImage.right
        anchors.top: pleaseLabel.bottom
        anchors.leftMargin: 50
        anchors.topMargin: 50
        placeholderText: qsTr("Path")
        text: testAppModel.currentPath
        enabled: false
    }

    CustomButton {
        id: customButton
        text: "Select"
        anchors.verticalCenter: pathField.verticalCenter
        anchors.left: pathField.right
        anchors.leftMargin: 20
        font.pointSize: 17
        rectangleBorderwidth: 4
        FolderDialog {
            id: folderDialog
            onAccepted: {
                const path = selectedFolder.toString().replace("file://", "")
                testAppController.selectPath(path)
            }
        }
        onClicked: {

            folderDialog.open()
        }
    }

    ListView {
        id: filesListView
        anchors.left: pathField.left
        anchors.right: customButton.right
        anchors.top: pathField.bottom
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 60
        anchors.bottomMargin: 160
        clip: true
        spacing: 6
        model: testAppModel.filesListModel
        delegate: FileDelegate {
            width: filesListView.width
            sizeB: sizeRole
            fileNameText: nameRole
            selected: ListView.isCurrentItem
            mouseArea.onClicked: {
                filesListView.currentIndex = index
            }
        }
        onCurrentIndexChanged: {
            testAppController.selectFile(currentIndex)
        }
    }

    Image {
        id: previewImage
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 50
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        source: {
            if (testAppModel.currentFile) {
                const parts = testAppModel.currentFile.name.split(".")
                const extension = parts.length > 1 ? parts.pop() : ""
                if (extension !== "barch") {
                    return "file://" + testAppModel.currentPath + "/" + testAppModel.currentFile.name
                }
            }
            return "../images/tabler--mood-empty.svg"
        }
        fillMode: Image.PreserveAspectFit
    }

    CustomButton {
        id: convertButton
        height: 60
        text: testAppModel.mode ? "Uncompress" : "Compress"
        anchors.left: filesListView.left
        anchors.right: filesListView.right
        anchors.top: filesListView.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.topMargin: 20
        borderColor: "#9f4848"
        enabled: testAppModel.currentFile
        onClicked: {
            waitDialog.fillAndOpen()
            var result = testAppController.convert()
            result.statusChanged.connect(function (status) {
                if (status) {
                    waitDialog.close()
                    mainStackView.replace(savePage)
                } else {
                    waitDialog.close()
                }
            })
        }
    }
}
