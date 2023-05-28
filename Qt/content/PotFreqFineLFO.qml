/*******************************************************************************

 A.L.F.O.N.S.o
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
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.mixer 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: potFreqFineLFO
    width: potFreqFineObj.potWidth
    height: potFreqFineObj.potHeight
    property alias potFreqFineLFOID: potFreqFineObj.potID
    property alias potFreqFineLFOValue: potFreqFineObj.potValue

    FontLoader { id: potFreqFineLabelFont; source: "qrc:/resources/arial.ttf" }

    Component.onCompleted: {
        // Force first Potentiometer value
        Mixer.setMixerValue(potFreqFineObj.potID, potFreqFineObj.potType, potFreqFineObj.potValue);
    }

    Image {
        id: potFreqFineGauge
        x: -10
        y: -10
        width: parent.width + 20;
        height: parent.height + 10;
        source: "qrc:/resources/PotGauge.svg"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: label0KHz
        x: -21
        y: 72
        color: "#ffffff"
        text: qsTr("0Hz")
        font.pixelSize: 11
        font.family: potFreqFineLabelFont.font
        font.weight: Font.Normal
    }

    Text {
        id: label165KHz
        x: -46
        y: 30
        color: "#ffffff"
        text: qsTr("165Hz")
        font.pixelSize: 11
        font.family: potFreqFineLabelFont.font
        font.weight: Font.Normal
    }

    Text {
        id: label330Hz
        x: -35
        y: -7
        color: "#ffffff"
        text: qsTr("330Hz")
        font.pixelSize: 11
        font.family: potFreqFineLabelFont.font
        font.weight: Font.Normal
    }

    Text {
        id: label500Hz
        x: 25
        y: -28
        color: "#ffffff"
        text: qsTr("500Hz")
        font.pixelSize: 11
        font.family: potFreqFineLabelFont.font
        font.weight: Font.Normal
    }

    Text {
        id: label665KHz
        x: 75
        y: -7
        color: "#ffffff"
        text: qsTr("665Hz")
        font.pixelSize: 11
        font.family: potFreqFineLabelFont.font
        font.weight: Font.Normal
    }

    Text {
        id: label830Hz
        x: 84
        y: 30
        color: "#ffffff"
        text: qsTr("830Hz")
        font.pixelSize: 11
        font.family: potFreqFineLabelFont.font
        font.weight: Font.Normal
    }

    Text {
        id: label1KHz
        x: 65
        y: 72
        color: "#ffffff"
        text: qsTr("1KHz")
        font.pixelSize: 11
        font.family: potFreqFineLabelFont.font
        font.weight: Font.Normal
    }

    Potentiometer {
        id: potFreqFineObj
        potType: Protocol.freqFinePotType
        potWidth: 70
        potHeight: 70
        potMinRange: 1
        potMaxRange: 255
        potSpreadAngle: 280
        potValue: 127

        onPotValueChanged: (potValue)=> {
            // Save Potentiometer value
            Mixer.setMixerValue(potFreqFineObj.potID, potFreqFineObj.potType, potFreqFineObj.potValue);
        }
    }

    Connections {
        target: potFreqFineObj
        function onPotClockWise(iDeg) {
            knobFreqFineView.rotation += iDeg
        }
        function onPotCouterClockWise(iDeg) {
            knobFreqFineView.rotation -= iDeg
        }
    }

    Connections {
        target: Mixer

        function onUpdateFreqFine(byID, newValue)
        {
            // If update is for this VCO
            if (byID === potFreqFineLFOID) {
                // Set fine frequency
                potFreqFineObj.fromValue(newValue);
            }
        }
    }

    Image {
        id: knobFreqFineView
        width: potFreqFineObj.potWidth
        height: potFreqFineObj.potHeight
        source: "qrc:/resources/PotFrequencyMetal.svg"
        fillMode: Image.PreserveAspectFit

//            Behavior on rotation {
//                NumberAnimation {
//                    duration: 1
//                }
//            }
    }

    MouseArea {
        //hoverEnabled: true
        anchors.fill: parent
        onClicked : (mouse)=> {
            if (mouse.button === Qt.LeftButton) {
                // Cals Angle and fire signals
                potFreqFineObj.toAngle(mouse.x, mouse.y)

                //console.log("mouse.x ", mouse.x)
                //console.log("mouse.y ", mouse.y)
            }
        }

        onMouseXChanged: (mouse)=> {
            // Cals Angle and fire signals
            potFreqFineObj.toAngle(mouse.x, mouse.y)
        }
        onMouseYChanged: (mouse)=> {
            // Cals Angle and fire signals
            potFreqFineObj.toAngle(mouse.x, mouse.y)
        }
    }
}
