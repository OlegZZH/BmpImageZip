import QtQuick
import QtQuick.Controls 6.8

Button {
    id: button
    text: qsTr("Button")
    property alias rectangleBorderwidth: rectangle.border.width
    property alias borderColor: rectangle.border.color
    font.pointSize: 21
    background: Rectangle {
        id: rectangle
        color: button.down ? Qt.darker("#d6d6d6") : "#d6d6d6"
        radius: 65
        border.color: "#569f48"
        border.width: 10
    }
}
