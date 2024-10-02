

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import QmlInterface

Rectangle {
    id: rectangle
    color: "#ffffff"
    border.color: "#ffffff"

    Switch {
        id: darkModeSwitch
        width: 68
        height: 36
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 108
        anchors.topMargin: 18

        Connections {
            target: darkModeSwitch
            onToggled: QmlInterface.startBleServer()
        }
    }

    Label {
        id: label
        width: 81
        height: 23
        color: "#000000"
        text: qsTr("Dark Mode")
        anchors.verticalCenter: darkModeSwitch.verticalCenter
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 14
        anchors.topMargin: 24
        anchors.verticalCenterOffset: 0
    }
    states: [
        State {
            name: "Dark Mode"
            when: darkModeSwitch.checked

            PropertyChanges {
                target: rectangle
                color: "#000000"
                border.color: "#000000"
            }

            PropertyChanges {
                target: label
                color: "#ffffffff"
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#00000c"}
}
##^##*/

