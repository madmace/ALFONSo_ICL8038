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

    signal isALFONSoUSBPresent()

    Timer {
        id: timer
    }

    function delay(delayTime, cb) {
            timer.interval = delayTime;
            timer.repeat = false;
            timer.triggered.connect(cb);
            timer.start();
    }

    Connections {
        target: SerialPortController

        function onIsALFONSoUSBPresent(bResult) {

            // Set LFOMixer visible
            setALFONSoUSBMixerVisible(bResult);
            // Send request about state of all VCO
            Mixer.sendRequestSyncVCO(Protocol.syncAllVCO);


            //console.log("POT -> " + panelLFOMixer.singleUnitLFO.potDutyCycleLFOValue);
        }
    }

    // Put in Mixer mode or return in USB Serching mode (start mode)
    function setALFONSoUSBMixerVisible(bResult) {

        // Control if ALFONSo USB Serial found
        if (bResult) {

            console.log("ALFONSo Port preesent.")

            // Set Splash window
            splashWindow.visible = false;
            splashWindow.enabled = false;
            // Set LFOMixer window
            panelLFOMixer.visible = true;
            panelLFOMixer.enabled = true;
            // Set Description
            panelConnectionBox.panelConnectionLabelText = Constants.splashUSBDeviceFound;
            panelConnectionBox.panelConnectionLEDSource = "qrc:/resources/GreenLight.svg"

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

    Image { source: "qrc:/resources/alum-texture-blue-900x900.jpg"; fillMode: Image.Tile; anchors.fill: parent }


    Text {
        id: mainTitleLabel
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.bottom
        anchors.topMargin: -120
        color: "goldenrod"
        text: qsTr("Alfonso")
        font.pixelSize: 70
        font.bold: true
        font.weight: Font.ExtraBold
        style: Text.Sunken
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Edwardian Script ITC"

        Text {
            id: subTitleLabel
            anchors.left: mainTitleLabel.left
            anchors.top: mainTitleLabel.bottom
            anchors.leftMargin: 5
            anchors.topMargin: -10
            color: "black"
            text: qsTr("Analog Low Frequency Oscillator No linear Sequencer")
            font.pixelSize: 20
            font.weight: Font.Normal
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Franklin Gothic Book"
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
        font.family: "Franklin Gothic Book"
    }

    Rectangle {
        id: panelPowerBox
        anchors.left: parent.left
        anchors.leftMargin: 20
        y: 10
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
                        // Wait for 200 ms and emit request for search Serial USB
                        delay(400, function() {})
                        splashWindow.isALFONSoUSBPresent();
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
            font.family: "Arial"
        }
    }

    Rectangle {
        id: panelConnectionBox
        anchors.left: panelPowerBox.left
        anchors.leftMargin: panelPowerBox.width + 20
        y: 10
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
            font.family: "Arial"
        }
    }

}
