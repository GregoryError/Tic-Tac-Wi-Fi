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


    Connections{
            target: network_core

            onServerConnectedState:{
                console.log(game_engine.showPlayerName())
                bigbusy.visible = false
                startItemDisAppear.running = true
                cells.visible = true
                statusTxt.visible = false

                secondtimer.running = true

                fillGroundDisAppear.running = true

               // network_core.gameProcess();

                firsttimer.running = true;

            }

            onClientConnectedState:{
                console.log(game_engine.showPlayerName())
                bigbusy.visible = false
                startItemDisAppear.running = true
                cells.visible = true
                statusTxt.visible = false

                secondtimer.running = true

                fillGroundDisAppear.running = true



            }


        }


    Connections{
        target: network_core

        onOpponentMove:{
            console.log("OPPONENT MOVE")

            statusTxt.text = game_engine.showOpponentName() + " move!";
            statusTxt.color = "#2ba1f3";
            statusTxt.visible = true;



            buttons.enabled = false

        }

        onYourMove:{
            console.log("YOUR MOVE")

            statusTxt.text = "Your move!";
            statusTxt.y = cells.y - 70
            statusTxt.color = "#2ba1f3";
            statusTxt.visible = true;

            buttons.enabled = true
        }

    }



    Timer {
        id: firsttimer
            interval: 50;

            onTriggered:{
                    network_core.gameProcess();
            }
        }











    Timer {
        id: secondtimer
            interval: 500;

           // running:

            onTriggered:{

                firstName.text = game_engine.showPlayerName();
                secondName.text = game_engine.showOpponentName();
                firstName.visible = true
            }
        }





        Rectangle{
            id: head
            width: main.width
            height: main.height / 15
            anchors.top: main.top
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




        Rectangle{
            id: mainfield
            width: main.width
            height: main.height
            anchors.top: head.bottom
            anchors.fill: main





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
                id: fillGround
                visible: false
                color: "#2cbaf1"
                anchors.horizontalCenter: startItem.horizontalCenter
                y: findButton.y + 130
                width: 5
                height: 3
                radius: 2

                ScaleAnimator{
                    id: fillGroundAnim
                    target: fillGround
                    running: fillGround.visible
                    from: 1
                    to: 1000
                    duration: 3500
                    easing.type: Easing.OutExpo
                    onStopped: {
                       // some soundeffects
                       // startItem.visible = false
                        //startItemDisAppear.running = true
                    }
                }


                OpacityAnimator{
                    id: fillGroundDisAppear
                    target: fillGround
                    from: 1
                    to: 0
                    running: false
                    duration: 300
                    onStopped: {
                        fillGround.visible = false
                    }

                }

            }




            Item {
                id: startItem
                width: mainfield.width
                height: mainfield.height
                anchors.horizontalCenter: mainfield.horizontalCenter
                anchors.top: statusTxt.bottom

            TextField{
                id: nameInput
                maximumLength: 20
                width: main.width / 2
                height: main.height / 13
                anchors.horizontalCenter: startItem.horizontalCenter
                anchors.top: startItem.top
                anchors.topMargin: 70

                font.pixelSize: 30
                font.family: "Lato Light"
                placeholderText: "Your name"
                background: Rectangle {
                radius: 7
                implicitWidth: nameInput.width
                implicitHeight: nameInput.height
                border.color: "#2cbaf1"
                border.width: 2
            }

                //onAccepted: passwordInput.forceActiveFocus()
                color: "#2cbaf1"
                font.pointSize: nameInput.width / 25
                //KeyNavigation.tab: passwordInput

                // here must be reading from QSettings


            }

            Button{
                id: findButton
                width: nameInput.width
                height: nameInput.height
                anchors.top: nameInput.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: nameInput.horizontalCenter
                background: Rectangle{
                    id: findButtonBack
                    anchors.fill: parent
                    color: "#2cbaf1"
                    radius: 7
                }
                Text{
                anchors.centerIn: parent
                color: "white"
                font.pointSize: findButton.width / 11
                font.family: "Sawasdee"
                text: "Find game";
                }


                onClicked: {
                    fillGround.visible = true
                    game_engine.setPlayerName(nameInput.text)
                    bigbusy.running = true

                    startItem.visible = false


                    statusTxt.text = "Searching for server..."
                    statusTxtAnim.running = true

                    network_core.client_Find()



                }

            }

            Button{
                id: createButton
                width: nameInput.width
                height: nameInput.height
                anchors.top: findButton.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: nameInput.horizontalCenter
                background: Rectangle{
                    id: createButtonBack
                    anchors.fill: parent
                    color: "#2cbaf1"
                    radius: 7
                }
                Text{
                anchors.centerIn: parent
                color: "white"
                font.pointSize: createButton.width / 11
                font.family: "Sawasdee"
                text: "Start server";
                }
                onClicked: {

                    startItem.visible = false

                    fillGround.visible = true

                    game_engine.setPlayerName(nameInput.text)

                    statusTxt.text = "Waiting for player..."

                    statusTxtAnim.running = true

                    createButtonDis.running = true

                    network_core.slotListen()


                    bigbusy.running = true

                   // startItemDisAppear.running = true


                   // cells.visible = true    // this is temporary
                }


                ScaleAnimator{
                    id: createButtonDis
                    target: createButton
                    running: false
                    from: 1
                    to: 1000
                    duration: 2300
                    easing.type: Easing.OutExpo
                    onStopped: {
                       // some soundeffects
                       // startItem.visible = false
                        //startItemDisAppear.running = true
                    }
                }




            }

           OpacityAnimator{
               id: startItemDisAppear
               target: startItem
               from: 1
               to: 0
               running: false
               duration: 200
               onStopped: {
                   startItem.visible = false
               }

           }


}

             Grid{
                 id: cells
                 anchors.horizontalCenter: parent.horizontalCenter
                 y: mainfield.height / 2

                // anchors.fill: parent

                 visible: false

                 columns: 3
                 rows: 3
                 spacing: 7


                 Repeater{
                     id: rpt
                     model: 9

                     Button{
                        id: buttons
                       // width: mainfield.width / 18
                       // height: width

                        width: 60
                        height: width

                        background: Rectangle{
                            id: buttBack
                            anchors.fill: parent
                            radius: 3
                            color: "#2cbaf1"

                        }

                        Text{
                            id: buttontxt
                            anchors.centerIn: parent
                            font.family: "Lato Light"
                            font.pointSize: (main.height / 9) / 2 -15
                            color: "white"
                            //text: index


                        }
                            onClicked: {

                                  game_engine.nextMove(index);





                                  buttBack.color = "pink"

                                  buttons.enabled = false

                                                                   //buttontxt.visible = false
                                //buttons.visible = false



                            }

                       }

                  }

             ScaleAnimator{
                 id: cellAppear
                 target: cells
                 running: cells.visible
                 from: 200
                 to: 1
                 duration: 1000
                 easing.type: Easing.OutExpo
                 onStopped: {
                    // some soundeffects
                 }
             }


            }


        //     TextArea{
        //         id: testZone
        //         width: Screen.width - 100
        //         height: 250
        //
        //         anchors.horizontalCenter: mainfield.horizontalCenter
        //         anchors.top: cells.bottom
        //         font.family: "Sawasdee"
        //         font.pixelSize: 20
        //         text: network_core.test_showIp()
        //
        //     }
        //




             Text {
                 id: statusTxt
                 anchors.horizontalCenter: mainfield.horizontalCenter
                 y: head.y + 15
                 font.pointSize: createButton.width / 11
                 font.family: "Sawasdee"
                 color: "white"
                 OpacityAnimator{
                     id: statusTxtAnim
                     target: statusTxt
                     from: 0
                     to: 1
                     duration: 700
                     running: false
                     loops: Animation.Infinite
                 }
             }





             Text {
                 id: firstName
                 visible: false
                 anchors.horizontalCenter: mainfield.horizontalCenter
                 y: head.y + statusTxt.height + 30
                 font.pointSize: createButton.width / 9
                 font.family: "Sawasdee"
                 color: "#2ba1f3"
                 OpacityAnimator{
                     id: firstNameTxtAnim
                     target: firstName
                     from: 0
                     to: 1
                     duration: 700
                     running: firstName.visible
                     loops: 7
                 }
             }

             Text {
                 id: vsTxt
                 visible: firstName.visible
                 anchors.horizontalCenter: mainfield.horizontalCenter
                 anchors.top: firstName.bottom
                 anchors.topMargin: 5
                 font.pointSize: createButton.width / 11 - 2
                 font.family: "Sawasdee"
                 color: "#2cbaf1"
                 text: "VS"
                 OpacityAnimator{
                     id: vsTxttAnim
                     target: vsTxt
                     from: 0
                     to: 1
                     duration: 700
                     running: firstName.visible
                     loops: 7
                 }
             }

             Text {
                 id: secondName
                 visible: firstName.visible
                 anchors.horizontalCenter: mainfield.horizontalCenter
                 anchors.top: vsTxt.bottom
                 anchors.topMargin: 5
                 font.pointSize: createButton.width / 9
                 font.family: "Sawasdee"
                 color: "#2ba1f3"
                 OpacityAnimator{
                     id: secondNameTxtAnim
                     target: secondName
                     from: 0
                     to: 1
                     duration: 700
                     running: firstName.visible
                     loops: 7
                 }
             }










}



       // Timer {
       //     id: firsttimer
       //         interval: 1750;
       //
       //         //running:
       //
       //         onTriggered:{
       //             network_core.client_Find()
       //             bigbusy.running = false
       //             statusTxt.visible = false
       //             cells.visible = true
       //
       //
       //         }
       //     }
       //

        BusyIndicator {
              id: bigbusy
              opacity: 0
              width: parent.width / 3
              height: parent.width / 3
              y: head.y + 150
              anchors.horizontalCenter: mainfield.horizontalCenter
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
                                    duration: 700
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
                                    color: "white"
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






















