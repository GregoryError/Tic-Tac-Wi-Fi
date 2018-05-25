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
            fillGroundDisAppear.running = true

            secondtimer.running = true
            
        }
        
        onClientConnectedState:{
            console.log(game_engine.showPlayerName())
            bigbusy.visible = false
            startItemDisAppear.running = true
            cells.visible = true
            statusTxt.visible = false
            fillGroundDisAppear.running = true
            
            secondtimer.running = true

        }
        
    }
    
    
    Timer {
        id: secondtimer
        interval: 400;
        
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
            width: 7
            height: 4
            radius: 10
            
            ScaleAnimator{
                id: fillGroundAnim
                target: fillGround
                running: fillGround.visible
                from: 1
                to: 700
                duration: 4500
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
                    to: 900
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
        

        Connections{
            target: network_core

            onOpponentWin:{
                game_engine.soundLoose();
                statusTxt.font.pointSize = createButton.width / 9
                statusTxt.y = cells.y - 70
                statusTxt.text = game_engine.showOpponentName() + " win!";
                statusTxt.color = "#2ba1f3";
                statusTxt.visible = true;
                restartTimer.running = true;


            }

            onYouWin:{
                game_engine.soundWin()
                statusTxt.font.pointSize = createButton.width / 9
                statusTxt.y = cells.y - 70
                statusTxt.text = " You win!";
                statusTxt.color = "#2ba1f3";
                statusTxt.visible = true;
                restartTimer.running = true;
            }

            onDraw:{
                statusTxt.font.pointSize = createButton.width / 9
                statusTxt.y = cells.y - 70
                statusTxt.text = "Dead heat!";
                statusTxt.color = "#2ba1f3";
                statusTxt.visible = true;
                restartTimer.running = true;
            }


            onOpponentMove:{
                console.log("OPPONENT MOVE")
                
                statusTxt.y = cells.y - 70
                statusTxt.text = game_engine.showOpponentName() + " move!";
                statusTxt.color = "#2ba1f3";
                statusTxt.visible = true;
                
                
                
                cells.enabled = false
                
            }
            
            onYourMove:{
                console.log("YOUR MOVE")
                
                statusTxt.text = "Your move!";
                statusTxt.y = cells.y - 70
                statusTxt.color = "#2ba1f3";
                statusTxt.visible = true;
                
                cells.enabled = true
            }
            

        }



        Timer {
            id: restartTimer
            interval: 1750;
            running: false

            onTriggered:{
                cellsExit.running = true
            }
        }



        

        Connections{
            target: network_core

            onSet_X_on_0:{
                myModel.get(0).backdata = "qrc:/cross.png"
                myModel.get(0).active = false
            }
            onSet_X_on_1:{
                myModel.get(1).backdata = "qrc:/cross.png"
                myModel.get(1).active = false
            }
            onSet_X_on_2:{
                myModel.get(2).backdata = "qrc:/cross.png"
                myModel.get(2).active = false
            }
            onSet_X_on_3:{
                myModel.get(3).backdata = "qrc:/cross.png"
                myModel.get(3).active = false
            }
            onSet_X_on_4:{
                myModel.get(4).backdata = "qrc:/cross.png"
                myModel.get(4).active = false
            }
            onSet_X_on_5:{
                myModel.get(5).backdata = "qrc:/cross.png"
                myModel.get(5).active = false
            }
            onSet_X_on_6:{
                myModel.get(6).backdata = "qrc:/cross.png"
                myModel.get(6).active = false
            }
            onSet_X_on_7:{
                myModel.get(7).backdata = "qrc:/cross.png"
                myModel.get(7).active = false
            }
            onSet_X_on_8:{
                myModel.get(8).backdata = "qrc:/cross.png"
                myModel.get(8).active = false
            }

            ///////////

            onSet_0_on_0:{
                myModel.get(0).backdata = "qrc:/circle.png"
                myModel.get(0).active = false
            }
            onSet_0_on_1:{
                myModel.get(1).backdata = "qrc:/circle.png"
                myModel.get(1).active = false
            }
            onSet_0_on_2:{
                myModel.get(2).backdata = "qrc:/circle.png"
                myModel.get(2).active = false
            }
            onSet_0_on_3:{
                myModel.get(3).backdata = "qrc:/circle.png"
                myModel.get(3).active = false
            }
            onSet_0_on_4:{
                myModel.get(4).backdata = "qrc:/circle.png"
                myModel.get(4).active = false
            }
            onSet_0_on_5:{
                myModel.get(5).backdata = "qrc:/circle.png"
                myModel.get(5).active = false
            }
            onSet_0_on_6:{
                myModel.get(6).backdata = "qrc:/circle.png"
                myModel.get(6).active = false
            }
            onSet_0_on_7:{
                myModel.get(7).backdata = "qrc:/circle.png"
                myModel.get(7).active = false
            }
            onSet_0_on_8:{
                myModel.get(8).backdata = "qrc:/circle.png"
                myModel.get(8).active = false
            }




        }
        
        
        ListModel {
            id: myModel

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }
            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

            ListElement {
                mycolor: "#2cbaf1"
                backdata: "null"
                active: true
            }

        }
        

        GridView{
            id: cells
            interactive: false
            visible: false
            anchors.horizontalCenter: parent.horizontalCenter
            y: mainfield.height / 2
            
            width: cellWidth * 3 + 3
            height: cellHeight * 3 + 3

         //   cellHeight: Screen.width / 5    // for mobile devices
         //   cellWidth: Screen.width / 5


            cellHeight: Screen.width / 15
            cellWidth: Screen.width / 15


            model: myModel
            delegate: Component{
                id: cellDelegat
                Item {
                    id: oneCell
                    width: cells.cellWidth
                    height: cells.cellHeight

                    Button{
                        id: buttons
                        enabled: active
                        width: oneCell.width
                        height: oneCell.height
                        background: Rectangle{
                            id: backOfCell
                            color: mycolor
                            anchors.fill: parent
                            radius: 3
                            anchors.margins: 1
                            Image {
                                id: buttImg
                                smooth: true
                                anchors.fill: parent
                                source: backdata
                                ScaleAnimator{
                                    id: backgroundAppear
                                    target: buttImg
                                    from: 0
                                    to: 1
                                    running: (buttImg.source !== "null")? true : false
                                    duration: 200
                                    // easing.type: "OutBack"
                                    onStopped: {
                                        game_engine.soundTap()
                                    }

                                }

                            }
                        }
                        onClicked: {
                            //game_engine.soundTap()

                            console.log(index)

                            if(network_core.isIcross())
                                myModel.get(index).backdata = "qrc:/cross.png"
                            else
                                myModel.get(index).backdata = "qrc:/circle.png"

                            myModel.get(index).active = false

                            network_core.thisMoveMade(index);

                        }

                    }

                }

            }
            
            
            ScaleAnimator{
                id: cellAppear
                target: cells
                running: cells.visible
                from: 200
                to: 1
                duration: 900
                easing.type: Easing.OutExpo
                onStopped: {
                    // some soundeffects
                    game_engine.soundBegin()
                }
            }



            SequentialAnimation{
                id: cellsExit
                running: false


                ParallelAnimation{

                    NumberAnimation{
                        target: cells
                        properties: "scale"
                        from: 1
                        to: 150
                        duration: 700
                        easing.type: Easing.InExpo


                    }
                    NumberAnimation{
                        target: cells
                        properties: "opacity"
                        from: 1
                        to: 0
                        duration: 800
                        easing.type: Easing.InExpo

                    }

                }

                onStopped: {
                    // Here must be the slot, that reset all of values,
                    // and begin new game again.

                    // if(!network_core.amIServer())
                    // {
                    // network_core.client_disconnect()
                    // connecttimer.running = true
                    // }


                    console.log(myModel.rowCount());


                    for(var i = 0; i !== myModel.count; ++i)
                    {
                        myModel.get(i).backdata = "null"
                        myModel.get(i).active = true
                    }

                    if(network_core.amIServer())
                        network_core.gameRestart()


                    cells.visible = true
                    cells.opacity = 1
                    cellAppear.running = true






                }

            }



        }



        // Timer {
        //     id: connecttimer
        //     interval: 150;
        //
        //     running: false
        //
        //     onTriggered:{
        //         network_core.client_connect()
        //     }
        // }

        
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


    BusyIndicator {
        id: bigbusy
        opacity: 0
        width: parent.width / 4
        height: parent.width / 4
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
                duration: 2200
            }
            
            Repeater {
                id: repeater
                model: 5
                
                Rectangle {
                    x: item.width / 2 - width / 7
                    y: item.height / 2 - height / 7
                    implicitWidth: 18
                    implicitHeight: 18
                    radius: 20
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






















