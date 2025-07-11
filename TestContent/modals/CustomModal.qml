import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Popup {
    id: customModal
    x: (1280 - width) / 2
    y: (720 - height) / 2
    modal: true
    padding: 0
    closePolicy: Popup.NoAutoClose | Popup.CloseOnPressOutside
    background: Rectangle {
        color: "#00ffffff"
        border.width: 0
    }
}
