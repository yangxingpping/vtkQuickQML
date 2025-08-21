import QtQuick
import QtQuick.Controls.Material

Rectangle {
    id: root
    MenuBar{
        id: mbFaker
        anchors.centerIn: parent
        width: 0
        height: 0
    }
    z: 99999
    width: 150
    property int subToolHeight: 50
    height: model.length * subToolHeight
    //Material.theme: Material.Dark
    Material.theme: youngConf.darkMode ? Material.Dark : Material.Light
    //color: Material.background
    color: mbFaker.background.color
    //property var model: youngConf.curMenu2
    ListView{
        id: cc0
        model: youngConf.toolBarMenu2
        boundsBehavior: Flickable.StopAtBounds
        anchors.fill: parent
        delegate: YoungButton{
            id: c1
            text: modelData
            width: root.width
            height: root.subToolHeight
            hoverEnabled: true
            onHoveredChanged: function(){
                
            }
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                propagateComposedEvents: true
                acceptedButtons: Qt.NoButton
                onMouseXChanged: function(){
                    
                }
                onMouseYChanged: function(){
                    
                }
                onClicked: function(mouse){
                    mouse.accepted = false
                }
            }
            onClicked: function(){
                youngToolbar.onClickSubMenu2(index);
            }
        }
    }
}
