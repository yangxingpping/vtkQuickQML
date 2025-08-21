import QtQuick
import QtQuick.Controls.Material

Rectangle {
    width: 400
    height: 400
    Material.theme: youngConf.darkMode ? Material.Dark : Material.Light
    color: Material.backgroundColor
    Button{
        text: "hello"
    }
}
