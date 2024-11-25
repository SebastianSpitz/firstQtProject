// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2

Window {
    id: mainWindow
    width: Constants.width
    height: Constants.height

    visible: true
    title: "SBCGui"

    Screen01 {
        id: mainScreen
        width: mainWindow.width
        height: mainWindow.height
        palette: {
            accent: "red"
            highlight: "blue"
        }
    }

}

