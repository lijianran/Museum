
import QtQuick 2.0
Item{
    id:coverFlow

    property ListModel model
    property int itemCount:5

    Rectangle{
        id:content
        anchors.fill:parent
        color:"black"
    }
    PathView{
       id:pathView

       model:coverFlow.model
       delegate:MyDelegate{}
       path:coverFlowPath
       pathItemCount:coverFlow.itemCount
       anchors.fill:parent
       preferredHighlightBegin:0.5
       preferredHighlightEnd:0.5
    }
    Path{
        id:coverFlowPath
        startX:0
        startY:coverFlow.height/3
        PathAttribute{name:"iconZ";value:0}
        PathAttribute{name:"iconAngle";value:70}
        PathAttribute{name:"iconScale";value:0.6}

        PathLine{x:coverFlow.width*0.5;y:coverFlow.height/3;  }
        PathAttribute{name:"iconZ";value:100}
        PathAttribute{name:"iconAngle";value:0}
        PathAttribute{name:"iconScale";value:1.0}

        PathLine{x:coverFlow.width;y:coverFlow.height/3;}
        PathAttribute{name:"iconZ";value:0}
        PathAttribute{name:"iconAngle";value:-70}
        PathAttribute{name:"iconScale";value:0.6}
        PathPercent{value:1.0}
    }
}
