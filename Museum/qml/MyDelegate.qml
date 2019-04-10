//import QtQuick 2.0
//import QtGraphicalEffects 1.0

//Item{
//    id: delegateItem

//    width: content.width/4
//    height: content.height/2
//    z: PathView.iconZ
//    scale:PathView.iconScale

//    Column{
//        id: delegate
//        spacing: 5

//        Image{
//           id: dlgImg
//           source: url
//           width: delegateItem.width
//           height: delegateItem.height

//           MouseArea{
//               anchors.fill: parent
//               //onClicked: database.slot_changecolor()
//               //onDoubleClicked: database.slot_changecolor(name)
//           }
//           Text {
//               id: namecontent
//               text: qsTr(name)
//               font.pixelSize: 20
//               color: "black"
//               anchors.bottom: dlgImg.bottom
//               anchors.horizontalCenter: parent.horizontalCenter
//           }
//        }

//        Item{
//            width:delegateItem.width
//            height:delegateItem.height

//            Image{
//                width:delegateItem.width
//                height:delegateItem.height
//                id:reflection
//                source:dlgImg.source
//                transform:Scale{
//                    yScale:-1
//                    origin.y:delegateItem.height/2
//               }
//            }

//            LinearGradient{
//               width:delegateItem.width
//               height:delegateItem.height
//               gradient:Gradient{
//                   GradientStop{position:0.0;color:Qt.rgba(0,0,0,0.3)}
//                   GradientStop{position:0.6;color:Qt.rgba(0,0,0,0.9)}
//               }
//            }
//        }
//    }

//    Rotation
//    {
//       origin.x:dlgImg.width/2
//       origin.y:dlgImg.height/2
//       axis{x:0;y:1;z:0}
//       angle: delegateItem.PathView.iconAngle
//    }
//}

import QtQuick 2.0
import QtGraphicalEffects 1.0
Item{
    id:delegateItem
    width:content.width/3
    height:content.width/3
    z:PathView.iconZ
    scale:PathView.iconScale

    Column  {
        id:delegate
        spacing:10

        Image{

            id:dlgImg
            source:res
            width:delegateItem.width
            height:delegateItem.height

            Text {
                id: namecontent
                text: qsTr(name)
                font.pixelSize: 20
                color: "black"
                anchors.bottom: dlgImg.bottom
                anchors.horizontalCenter: dlgImg.horizontalCenter
            }

            MouseArea{
                anchors.fill: parent
//                anchors.left: parent.left
//                anchors.right: parent.right
//                anchors.top: parent.top
//                anchors.bottom: parent.bottom
                onDoubleClicked: m_DataBase.slot_ShowData(name)
            }
        }


        Item{
            width:delegateItem.width
            height:delegateItem.height

            Image{
               id:reflection
               width:delegateItem.width
               height:delegateItem.height
               source:dlgImg.source
               transform:Scale{
                   yScale:-1
                   origin.y:delegateItem.height/2
               }
            }

            LinearGradient{
               width:delegateItem.width
               height:delegateItem.height
               gradient:Gradient{
                   GradientStop{position:0.0;color:Qt.rgba(0,0,0,0.3)}
                   GradientStop{position:0.55;color:Qt.rgba(0,0,0,0.9)}
               }
            }
        }
    }

    transform:Rotation{
       origin.x:dlgImg.width/2
       origin.y:dlgImg.height/2
        axis{x:0;y:1;z:0}
       angle:delegateItem.PathView.iconAngle
    }
}
