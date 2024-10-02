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

    ListView {
        id: listView
        x: 8
        y: 8
        width: 566
        height: 464
        model: ListModel {
            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "White"
                colorCode: "white"
            }
        }
        delegate: Row {
            spacing: 5
            Rectangle {
                width: 100
                height: 20
                color: colorCode
            }

            Text {
                width: 100
                text: name
            }
        }

        Rectangle {
            id: rectangle1
            width: parent.width
            height: parent.height
            color: "#00ffffff"
        }
    }

    RoundButton {
        id: searchButton
        x: 580
        y: 8
        text: ""
        flat: true
        icon.color: "#feffffff"
        icon.source: "../resources/icons/refresh-cw.svg"
    }

    RoundButton {
        id: connectionButton
        x: 580
        y: 66
        text: ""
        flat: true
        icon.color: "#ffffff"
        icon.source: "../resources/icons/link-2.svg"
    }

    RoundButton {
        id: backButton
        x: 580
        y: 420
        flat: true
        icon.source: "../resources/icons/check-square.svg"
        icon.color: "#ffffff"
    }

}
