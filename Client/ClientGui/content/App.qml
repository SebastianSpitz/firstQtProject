// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import QmlInterface

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "ClientGui"

    Screen01 {
        id: mainScreen
        visible: true
    }

    Screen02 {
        id: settingsScreen
        visible: false
    }

    Screen03 {
        id: bluetoothScreen
        visible: false
    }

    Connections {
        target: mainScreen
        onButtonClicked: function() {
            QmlInterface.buttonPressed()
        }
    }

    Connections {
        target: mainScreen
        onListViewItemClicked: function(name) {
            QmlInterface.listViewItemClicked(name);
        }
    }

    Connections {
        target: mainScreen
        onSettingsButtonClicked: function() {
            QmlInterface.settingsButtonClicked();
        }
    }

    Connections {
        target: mainScreen
        onConnectionButtonClicked: function() {
            QmlInterface.connectionButtonClicked();
        }
    }

    Connections {
        target: QmlInterface
        onSigNewButtonText: function(buttonText) {
            mainScreen.sendButton.text = buttonText;
        }
    }

    Connections {
        target: QmlInterface
        onSigNewListViewItem: function(itemText) {
            console.log("Signal newListViewItem: " + itemText);
            mainScreen.listModel.append({"name": itemText});
        }
    }
}

