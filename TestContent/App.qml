import QtQuick
import Test
import QtQuick.Controls 6.8
import "widgets"
import "pages"
import "modals"

Window {
    width: 1280
    height: 720

    visible: true
    title: "Test"

    StackView {
        id: mainStackView
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        initialItem: startPage
    }

    Component {
        id: startPage
        StartPage {}
    }
    Component {
        id: selectFilePage
        SelectFilePage {}
    }
    Component {
        id: previewPage
        PreviewPage {}
    }
    CustomModal {
        id: waitDialog
        contentItem: WaitModal {
            id: waitDialogContent
        }
        function fillAndOpen() {
            waitDialog.open()
        }
    }
    CustomModal {
        id: errorDialog
        contentItem: ErrorModal {
            id: errorDialogContent
        }
        function fillAndOpen() {
            errorDialog.open()
        }
    }
}
