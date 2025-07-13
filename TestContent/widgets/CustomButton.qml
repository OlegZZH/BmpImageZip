import QtQuick
import QtQuick.Controls 6.8

Button {
    id: customButton
    text: qsTr("Button")
    property alias rectangleBorderwidth: rectangle.border.width
    property alias borderColor: rectangle.border.color
    opacity: enabled ? 1 : 0.7
    font.pointSize: 21
    background: Rectangle {
        id: rectangle
        color: customButton.down ? Qt.darker("#d6d6d6") : "#d6d6d6"
        radius: 65
        border.color: "#569f48"
        border.width: 10
    }
}
