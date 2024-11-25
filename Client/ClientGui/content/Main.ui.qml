

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import Designs

Rectangle {
    id: rectangle
    anchors.fill: parent
    color: Designs.backgroundColor

    // Expose the objects
    property alias sendButton: sendButton
    property alias textInput: textInput
    property alias listModel: listModel

    // Defined signals for parent
    signal sendButtonClicked
    signal listViewItemClicked(string name)
    signal settingsButtonClicked
    signal connectionButtonClicked

    ListView {
        id: listView
        x: 52
        y: 36
        width: 160
        height: 406
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.rightMargin: 87
        anchors.topMargin: 8
        anchors.bottomMargin: 66
        model: ListModel {
            id: listModel
        }
        delegate: Item {
            width: parent.width
            height: 40

            // Check if the string is a server and make it clickable
            Text {
                id: itemText
                //color: "#ff0000"
                color: Designs.textColor
                text: name
                font.pixelSize: 14
                MouseArea {
                    id: itemTextArea
                    anchors.fill: parent
                    //enabled: isClickable
                    Connections {
                        target: itemTextArea
                        onClicked: listViewItemClicked(name)
                    }
                }
            }
        }

        Rectangle {
            id: rectangle2
            color: "#00ffffff"
            border.color: "#ffffff"
            border.width: 1
            anchors.fill: parent
        }
    }

    TextInput {
        id: textInput
        x: 0
        y: 420
        width: 445
        height: 52
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 142
        anchors.rightMargin: 8
        anchors.bottomMargin: 8
        font.pixelSize: 12
        readOnly: false

        Rectangle {
            id: rectangle1
            color: "#00ffffff"
            border.color: "#ffffff"
            border.width: 1
            anchors.fill: parent
        }
    }

    Button {
        id: sendButton
        x: 155
        y: 420
        width: 128
        height: 52
        text: "Button"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.bottomMargin: 8
        Connections {
            target: sendButton
            onClicked: sendButtonClicked()
        }
    }
    RoundButton {
        id: settingsButton
        x: 559
        y: 8
        width: 73
        height: 52
        opacity: 1
        visible: true
        text: ""
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 8
        flat: true
        icon.color: "#ffffff"
        icon.source: "../resources/icons/settings.svg"
        Connections {
            target: settingsButton
            onClicked: settingsButtonClicked()
        }
    }

    RoundButton {
        id: connectionButton
        x: 559
        y: 66
        width: 73
        height: 52
        text: ""
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 8
        anchors.topMargin: 66
        icon.source: "../resources/icons/bluetooth.svg"
        icon.color: "#ffffff"
        flat: true
        Connections {
            target: connectionButton
            onClicked: connectionButtonClicked()
        }
    }
}
