/*******************************************************************************

 A.L.F.O.N.S
 Author : Emiliano Mazza
 Version : 1.0
 Created on Date : 15/18/2020
 Last update     : 31/01/2023

 CopyRight 2006-2015 all rights are reserved

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE AUTHOR SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

*******************************************************************************/

import QtQuick 2.12
import QtQuick.Layouts 2.12
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.mixer 1.0
import com.alfonso.serialportcontroller 1.0
import com.alfonso.qml.controls 1.0

Rectangle {
    id: splashWindow
    anchors.fill: parent
    color: "transparent"
    border.color: "#33c2ff"
    border.width: 1

    FontLoader { id: mainTitleLabelFont; source: "qrc:/resources/ITCEDSCR.TTF" }
    FontLoader { id: mainTitle2LabelFont; source: "qrc:/resources/FRABK.TTF" }
    FontLoader { id: splashWindowLabelFont; source: "qrc:/resources/arial.ttf" }

    signal isALFONSoUSBPresent()

    Image { source: "qrc:/resources/alum-texture-blue-900x900.jpg"; fillMode: Image.Tile; anchors.fill: parent }

    // Bizarre way to draw lines :)
    Rectangle {
        id:  borderRectangleLeft
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 2
        width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        color: "white"
        border.color: "white"
        border.width: 4
    }

    // Bizarre way to draw lines :)
    Rectangle {
        id:  borderRectangleTop
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 1
        height: 2
        color: "black"
        border.color: "black"
        border.width: 4
    }

    // Bizarre way to draw lines :)
    Rectangle {
        id:  borderRectangleRight
        x: parent.width - 2
        anchors.top: parent.top
        anchors.topMargin: 0
        width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 2
        color: "black"
        border.color: "black"
        border.width: 4
    }

    // Bizarre way to draw lines :)
    Rectangle {
        id:  borderRectangleBotton
        anchors.left: parent.left
        anchors.leftMargin: 0
        y: parent.height - 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        height: 2
        color: "white"
        border.color: "white"
        border.width: 4
    }

    Timer {
        id: timerObj

        function setTimeout(cb, delayTime) {
                timerObj.interval = delayTime;
                timerObj.repeat = false;
                timerObj.triggered.connect(cb);
                timerObj.triggered.connect(function release () {
                    timerObj.triggered.disconnect(cb); // This is important
                    timerObj.triggered.disconnect(release); // This is important as well
                });
                timerObj.start();
            }
    }

    Connections {
        target: SerialPortController

        function onIsALFONSoUSBPresent(bResult) {

            // Set LFOMixer visible
            setALFONSoUSBMixerVisible(bResult);

            // Control if ALFONSo USB Serial found
            if (bResult) {
                // Load last configuration from JSON
                Mixer.loadJSONConfig(Constants.lastConfigJSONFile)
                // Send request about state of all VCO
                Mixer.sendRequestSyncAllVCO();
            }


            //console.log("POT -> " + panelLFOMixer.singleUnitLFO.potDutyCycleLFOValue);
        }
    }

    // Put in Mixer mode or return in USB Serching mode (start mode)
    function setALFONSoUSBMixerVisible(bResult) {

        // Control if ALFONSo USB Serial found
        if (bResult) {

            console.log("ALFONSo Port preesent.")

            // Set Description
            panelConnectionBox.panelConnectionLabelText = Constants.splashUSBDeviceFound;
            panelConnectionBox.panelConnectionLEDSource = "qrc:/resources/GreenLight.svg"

            // Wait for 0.5s
            timerObj.setTimeout(function () {
                // Set Splash window
                splashWindow.visible = false;
                splashWindow.enabled = false;
                // Set LFOMixer window
                panelLFOMixer.visible = true;
                panelLFOMixer.enabled = true;
            }, 500)

        } else {

            console.log("ALFONSo Port not preesent.")

            // Set Splash window
            splashWindow.visible = true;
            splashWindow.enabled = true;
            // Set LFOMixer window
            panelLFOMixer.visible = false;
            panelLFOMixer.enabled = false;
            // Set Description
            panelConnectionBox.panelConnectionLabelText = Constants.splashUSBDeviceNotFound;
            panelConnectionBox.panelConnectionLEDSource = "qrc:/resources/RedLight.svg"

        }

        // Set Power Button
        panelPowerButton.source = "qrc:/resources/PowerButtonUnselected.svg"
    }

    function setALFONSoUSBSeaching() {

        // Set Power Button image
        panelPowerButton.source = "qrc:/resources/PowerButtonSelected.svg"
        // Set Search text
        panelConnectionBox.panelConnectionLabelText = Constants.splashSeachingUSBDevice
        panelConnectionBox.panelConnectionLEDSource = "qrc:/resources/RedLight.svg"
    }

    Text {
        id: mainTitleLabel
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.bottom
        anchors.topMargin: -120
        color: "goldenrod"
        text: Constants.splashMainName
        font.pixelSize: 70
        font.bold: true
        font.weight: Font.ExtraBold
        style: Text.Sunken
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: mainTitleLabelFont.font

        Text {
            id: subTitleLabel
            anchors.left: mainTitleLabel.left
            anchors.top: mainTitleLabel.bottom
            anchors.leftMargin: 5
            anchors.topMargin: -10
            color: "black"
            text: Constants.splashMainSlogan
            font.pixelSize: 20
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: mainTitle2LabelFont.font
        }
    }

    Text {
        id: subVersionLabel
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.bottom
        anchors.topMargin: -30
        color: "black"
        text: qsTr("Embryonal Version " + Constants.swVersion)
        font.pixelSize: 10
        font.weight: Font.Normal
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: mainTitle2LabelFont.font
    }

    Rectangle {
        id: panelPowerBox
        anchors.left: parent.left
        anchors.leftMargin: 40
        y: 30
        width: 180
        height: 230
        color: "transparent"
        border.color: "black"
        border.width: 1
        radius: 10

        Image {
            id: panelPowerButton
            anchors.horizontalCenter: panelPowerBox.horizontalCenter
            anchors.top: panelPowerBox.top
            anchors.topMargin: 20
            width: 80
            height: 80
            source: "qrc:/resources/PowerButtonUnselected.svg"
            fillMode: Image.PreserveAspectFit
            smooth: true

            MouseArea {
                //hoverEnabled: true
                anchors.fill: parent
                onClicked : (mouse)=> {
                    if (mouse.button === Qt.LeftButton) {
                        // Set for searching
                        setALFONSoUSBSeaching();
                        // Wait for 0.5s and emit request for search Serial USB
                        timerObj.setTimeout(function () {
                            // Send signal for USB verify
                            splashWindow.isALFONSoUSBPresent();
                        }, 500);
                    }
                }
            }
        }

        Text {
            id: panelPowerButtonLabel
            anchors.horizontalCenter: panelPowerButton.horizontalCenter
            anchors.top: panelPowerButton.bottom
            anchors.topMargin: 20
            color: "black"
            text: qsTr(Constants.splashUSBPowerButton)
            font.pixelSize: 15
            font.weight: Font.Normal
            font.family: splashWindowLabelFont.font
        }
    }

    Rectangle {
        id: panelConnectionBox
        anchors.left: panelPowerBox.right
        anchors.leftMargin: 20
        anchors.top: panelPowerBox.top
        width: 350
        height: 110
        color: "transparent"
        border.color: "black"
        border.width: 1
        radius: 10
        property alias panelConnectionLabelText: panelConnectionLabel.text
        property alias panelConnectionLEDSource: panelConnectionLED.source

        Image {
            id: panelConnectionLED
            anchors.verticalCenter: panelConnectionBox.verticalCenter
            anchors.left: panelConnectionBox.left
            anchors.leftMargin: 30
            width: 40
            height: 40
            source: "qrc:/resources/RedLight.svg"
            fillMode: Image.PreserveAspectFit
            smooth: true
        }

        Text {
            id: panelConnectionLabel
            anchors.verticalCenter: panelConnectionLED.verticalCenter
            anchors.left: panelConnectionLED.left
            anchors.leftMargin: 60
            color: "black"
            text: qsTr(Constants.splashUSBDeviceNotConnected)
            font.pixelSize: 13
            font.weight: Font.Normal
            font.family: splashWindowLabelFont.font
        }
    }

}
