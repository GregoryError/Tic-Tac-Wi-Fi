import QtQuick 2.9
import QtQuick.Window 2.2

import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1


Window {
    visible: true
    id: main
    height: 960       // Don`t forget to change it, before build for target
    width: 540

    // height: Screen.height
    // width: Screen.width

    title: qsTr("Tic-Tac-Wi-fi")


    Rectangle{
        id: mainfield
        width: main.width
        height: main.height
        anchors.fill: parent



     //   Rectangle{
     //       anchors.fill: parent
     //       Image {
     //           anchors.fill: parent
     //           id: backGround
     //           source: "qrc:/background.png"
     //       }
     //
     //   }


        Button{
            id: butt
            anchors.top: mainfield.top
            anchors.margins: 50
            width: 150
            height: 50
            text: "Start Server"
            onPressed: {
                network_core.slotListen()


            }
        }


        Button{
            id: butt2
            anchors.top: butt.bottom
            anchors.margins: 50
            width: 150
            height: 50
            text: "Find Server"
            onPressed: {

                network_core.client_FindAndConnect()

            }
        }


        Button{
            id: butt3
            anchors.top: butt2.bottom
            anchors.margins: 50
            width: 150
            height: 50
            text: "Disconnect client"
            onPressed: {

                network_core.server_stop()

            }
        }


        Button{
            id: butt4
            anchors.top: butt3.bottom
            anchors.margins: 50
            width: 150
            height: 50
            text: "Send Hello"
            onPressed: {

                network_core.client_sendToServer()

            }
        }






    }

}




















