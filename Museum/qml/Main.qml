import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    Rectangle {
        id: centerRect
        anchors.fill:parent

        property int personsize

        Connections{
            target: m_DataBase
            onPersonChanged: loadData()

            function loadData(){
                var i = 0
                while(i < m_DataBase.personnum)
                {
                    var name = m_DataBase.person[i]
                    var path = m_DataBase.images[i]
                    model.append({
                                 "res": path,
                                 "name": name})
                    i++
                }
            }
        }


        ListModel{
            id:model


        }


        CoverFlow{
            anchors.fill: parent
            model: model
        }
    }
}
