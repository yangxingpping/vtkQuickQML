import QtQuick
import QtQuick.Controls.Material

Rectangle {
    id: root
    z: 99999
    width: cc0.width
    height: cc0.height
    Material.theme: Material.Dark
    color: Material.background
    property var model: ["first1", "second2", "third3", "fourth4"]
    Column{
        id: cc0
        topPadding: 4
        bottomPadding: 4
        spacing: 0
        Repeater{
            model: root.model
            YoungButton{
                id: c1
                text: modelData
                width: 150
                hoverEnabled: true
                onHoveredChanged: function(){
                    if(index==1){
                    }
                }
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    propagateComposedEvents: true
                    acceptedButtons: Qt.NoButton
                    onMouseXChanged: function(){
                        if(index!==1){
                        }
                    }
                    onMouseYChanged: function(){
                        if(index!==1){
                        }
                    }
                    onClicked: function(mouse){
                        mouse.accepted = false
                    }
                }
                onClicked: function(){
                    console.log("click item")

                }
            }
        }
    }
}
