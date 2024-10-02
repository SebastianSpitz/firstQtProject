pragma Singleton
import QtQuick 6.2
import QmlInterface


QtObject {
    // Define the color themes as a mapping
    property var themes: {
        "light": {
            "backgroundColor":  "#ffffff",
            "textColor":        "#000000",
            "accentColor":      "#ff0000",
            "borderColor":      "#000000",
        },
        "dark": {
            "backgroundColor":  "#333333",
            "textColor":        "#ffffff",
            "accentColor":      "#00dbff",
            "borderColor":      "#ffffff",
        },
        "blue": {
            "backgroundColor":  "#0000ff",
            "textColor":        "#ffffff",
            "accentColor":      "#ffdb00",
            "borderColor":      "#ffffff",
        },
        "green": {
            "backgroundColor":  "#00ff00",
            "textColor":        "#000000",
            "accentColor":      "#ff00ff",
            "borderColor":      "#000000",
        }
    }

    // Get the current theme colors based on the active theme
    property var currentTheme: themes[QmlInterface.getTheme() || "light"]

    // Use these colors throughout the app
    property color backgroundColor: currentTheme.backgroundColor
    property color textColor:       currentTheme.textColor
    property color accentColor:     currentTheme.accentColor
    property color borderColor:     currentTheme.borderColor
}
