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



        Rectangle{
            id: head
            width: mainfield.width
            height: mainfield.height / 15
            color: "#2cbaf1"
            Text {
                id: headText
                color: "#ffffff"
                anchors.verticalCenter: head.verticalCenter
                anchors.left: head.left
                anchors.margins: 20

                text: qsTr("Tic-Tac Wi-Fi")
                font.family: "Levenim MT"
                styleColor: "#e5ecee"
                font.pointSize: 18
            }
        }



        Button{
            id: butt
            anchors.top: head.bottom
            anchors.margins: 50
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 100
            text: "Start Server"
            onPressed: {
                network_core.slotListen()


            }
        }

        Button{
            id: butt2
            anchors.top: butt.bottom
            anchors.margins: 50
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 100
            text: "Find Server"
            onPressed: {

                bigbusy.running = true
                firsttimer.running = true

            }
        }

        Button{
            id: butt3
            anchors.top: butt2.bottom
            anchors.margins: 50
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 100
            text: "Disconnect client"
            onPressed: {

                network_core.server_stop()

            }
        }

        Button{
            id: butt4
            anchors.top: butt3.bottom
            anchors.margins: 50
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 100
            text: "Send Hello"
            onPressed: {

                network_core.client_sendToServer()

            }
        }





        Timer {
            id: firsttimer
                interval: 200;

                //running:

                onTriggered:{
                    network_core.client_FindAndConnect()
                   // while(true)
                   // {
                    //    if(network_core.client_is_Connected())
                    //    {
                            bigbusy.running = false
                            //break
                       // }
                  //  }



                }
            }


        BusyIndicator {
              id: bigbusy
              opacity: 0
              width: parent.width / 3
              height: parent.width / 3
              anchors.centerIn: parent
              running: false

              OpacityAnimator {
                      id: bigbusyappear
                      target: bigbusy;
                      from: 0;
                      to: 1;
                      duration: 1300
                      running: true
                      easing.type: Easing.InOutExpo
                  }


              contentItem: Item {
                            id: item
                           // x: parent.width / 2 - 32
                           // y: parent.height / 2 - 32
                            //anchors.fill: parent
                            //width: 64
                            //height: 64
                            opacity: bigbusy.running ? 1 : 0

                            Behavior on opacity {
                                OpacityAnimator {
                                    duration: 1700
                                }
                            }

                            RotationAnimator {
                                target: item
                                running: bigbusy.visible && bigbusy.running
                                from: 0
                                to: 360
                                loops: Animation.Infinite
                                duration: 1500
                            }

                            Repeater {
                                id: repeater
                                model: 6

                                Rectangle {
                                    x: item.width / 2 - width / 7
                                    y: item.height / 2 - height / 7
                                    implicitWidth: 30
                                    implicitHeight: 30
                                    radius: 50
                                    color: "#4B94FF"
                                    transform: [
                                        Translate {
                                            y: -Math.min(item.width, item.height) * 0.7
                                        },
                                        Rotation {
                                            angle: index / repeater.count * 360
                                            origin.x: 5
                                            origin.y: 5
                                        }
                                    ]
                                    }
                                }

                       }

              }


    }

}




















