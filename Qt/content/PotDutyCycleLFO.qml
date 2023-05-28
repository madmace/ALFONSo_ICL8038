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
    id: potDutyCycleLFO
    width: 90
    height: 90
    property alias potDutyCycleLFOID: potDutyCycleObj.potID
    property alias potDutyCycleLFOValue: potDutyCycleObj.potValue

    FontLoader { id: potDutyCycleLabelFont; source: "qrc:/resources/arial.ttf" }

    Component.onCompleted: {
        // Force first Potentiometer value
        Mixer.setMixerValue(potDutyCycleObj.potID, potDutyCycleObj.potType, potDutyCycleObj.potValue);
    }

    Image {
        id: potDutyCycleGauge
        x: -11
        y: -11
        width: parent.width + 20;
        height: parent.height + 10;
        source: "qrc:/resources/PotGauge.svg"
        fillMode: Image.PreserveAspectFit

        Text {
            id: labelMinDutyCycle
            x: 1
            y: 100
            color: "#ffffff"
            text: qsTr("1%")
            font.pixelSize: 12
            font.family: potDutyCycleLabelFont.font
            font.weight: Font.Normal
        }

        Text {
            id: labelMaxDutyCycle
            x: 90
            y: 100
            color: "#ffffff"
            text: qsTr("99%")
            font.pixelSize: 12
            font.family: potDutyCycleLabelFont.font
            font.weight: Font.Normal
        }

        Text {
            id: labelHalfDutyCycle
            x: 46
            y: -14
            color: "#ffffff"
            text: qsTr("50%")
            font.pixelSize: 12
            font.family: potDutyCycleLabelFont.font
            font.weight: Font.Normal
        }
    }

    Potentiometer {
        id: potDutyCycleObj
        potType: Protocol.dutyCyclePotType
        potWidth: 90
        potHeight: 90
        potMinRange: 1
        potMaxRange: 255
        potSpreadAngle: 280
        potValue: 127

        onPotValueChanged: (potValue)=> {
            // Save Potentiometer value
            Mixer.setMixerValue(potDutyCycleObj.potID, potDutyCycleObj.potType, potDutyCycleObj.potValue);
        }
    }

    Connections {
        target: potDutyCycleObj
        function onPotClockWise(iDeg) {
            knobDutyCycleView.rotation += iDeg
        }
        function onPotCouterClockWise(iDeg) {
            knobDutyCycleView.rotation -= iDeg
        }
    }

    Connections {
        target: Mixer

        function onUpdateDutyCycle(byID, newValue)
        {
            // If update is for this VCO
            if (byID === potDutyCycleLFOID) {
                // Set Duty Cycle
                potDutyCycleObj.fromValue(newValue);
            }
        }
    }

    Image {
        id: knobDutyCycleView
        width: potDutyCycleObj.potWidth
        height: potDutyCycleObj.potHeight
        source: "qrc:/resources/PotDutyCycleMetal.svg"
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        anchors.fill: parent
        onClicked : (mouse)=> {
            if (mouse.button === Qt.LeftButton) {
                // Cals Angle and fire signals
                potDutyCycleObj.toAngle(mouse.x, mouse.y)
            }
        }

        onMouseXChanged: (mouse)=> {
            // Cals Angle and fire signals
            potDutyCycleObj.toAngle(mouse.x, mouse.y)
        }
        onMouseYChanged: (mouse)=> {
            // Cals Angle and fire signals
            potDutyCycleObj.toAngle(mouse.x, mouse.y)
        }
    }
}
