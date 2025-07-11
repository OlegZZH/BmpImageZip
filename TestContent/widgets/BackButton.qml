import "../widgets"
import QtQuick

CustomButton {
    text: "  <  "
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.leftMargin: 30
    anchors.topMargin: 30
    rectangleBorderwidth: 4
    onClicked: {
        mainStackView.pop()
    }
}
