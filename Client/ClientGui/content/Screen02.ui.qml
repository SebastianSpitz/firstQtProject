/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import Designs

Rectangle {
    id: rectangle
    anchors.fill: parent
    color: Designs.backgroundColor

    ComboBox {
        id: comboBox
        x: 24
        y: 21
        width: 130
        height: 28

        Rectangle {
            id: rectangle1
            width: parent.width
            height: parent.height
            color: "#00ffffff"
            border.color: "#ffffff"
        }

        Label {
            id: label
            x: 151
            y: 9
            color: "#ffffff"
            text: qsTr("Designs")
        }
    }

    RoundButton {
        id: backButton
        x: 580
        y: 420
        text: ""
        icon.color: "#ffffff"
        icon.source: "../resources/icons/check-square.svg"
        flat: true
    }

}
