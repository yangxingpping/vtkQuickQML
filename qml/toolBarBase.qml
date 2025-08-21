import QtQuick
import QtQuick.Controls.Material
Rectangle {
    id: root
    width: 600
    height: 200
    MenuBar{
        id: mbFaker
        anchors.centerIn: parent
        width: 0
        height: 0
    }
    color:  mbFaker.background.color //Material.background
    Material.theme: youngConf.darkMode ? Material.Dark : Material.Light
    Row{
        id: row
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: rtRight.left
        spacing: 1
        Repeater{
            model: ["hello", "world", "next", "last"] //youngConf.toolBar
            YoungButton{
                id: rt0
                text: modelData
                height: root.height
                width: implicitWidth + 30
                hoverEnabled: true
                onHoveredChanged: function(){
                    var pos = rt0.mapToGlobal(0,0);
                    if(hovered){
                        youngNotify.hoveEnterToolbar(Qt.point(pos.x, pos.y+rt0.height), Qt.size(150, 500), index)
                    }
                }
                onClicked: function(){
                    var pos = rt0.mapToGlobal(0,0);
                    youngNotify.clickToolbar(Qt.point(pos.x, pos.y+rt0.height), Qt.size(150, 3000), index)
                }
            }
        }
    }
    
    Rectangle{
        id: rtRight
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 120
        color: "transparent"
        Switch{
            anchors.fill: parent
            text: "Dark"
            checked: Material.theme === Material.Dark
            onCheckedChanged: function(){
                root.setTheme(checked)
            }
        }
    }
    function setTheme(theme){
        youngConf.darkMode = theme
    }
}
