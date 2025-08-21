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
    color: mbFaker.background.color
    //color: Material.background
    //property var model: youngConf.curMenu1
    
    ListView{
        id: cc0
        model: youngConf.toolBarMenu1
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        delegate: YoungButton{
            id: c1
            text: modelData
            enabled: root.visible
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
                    var pos = parent.mapToGlobal(parent.width,0);
                    youngToolbar.onMoveEnterToolsubMenu1(Qt.point(pos.x, pos.y), index)
                }
                onMouseYChanged: function(){
                    var pos = parent.mapToGlobal(parent.width,0);
                    youngToolbar.onMoveEnterToolsubMenu1(Qt.point(pos.x, pos.y), index)
                }
                onClicked: function(mouse){
                    mouse.accepted = false
                }
            }
            onClicked: function(){
                var bhide = youngToolbar.onClickSubMenu1(index);
            }
        }
    }
}
