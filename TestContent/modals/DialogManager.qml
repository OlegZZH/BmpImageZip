import QtQuick
import QtQuick.Controls

Item {
    id: dialogManager

    property alias loader: dialogLoader

    Loader {
        id: dialogLoader
        active: false
        asynchronous: false
        onLoaded: {
            if (item && item.open) {
                item.open()
            }
        }
    }

    function showModal(modal, props = {}) {
        if (dialogLoader.active) {
            return
        }
        dialogLoader.sourceComponent = modal

        Qt.callLater(() => {
                         if (dialogLoader.item) {
                             for (var key in props) {
                                 if (key in dialogLoader.item) {
                                     dialogLoader.item[key] = props[key]
                                 }
                             }
                             if (dialogLoader.item.open) {
                                 dialogLoader.item.open()
                             }
                         }
                     })
    }

    function closeModal() {
        if (dialogLoader.item && dialogLoader.item.close) {
            dialogLoader.item.close()
        }
    }
}
