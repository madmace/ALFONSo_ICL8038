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

import com.alfonso.mixer 1.0
import com.alfonso.qml.controls 1.0

Rectangle {
    id: singleUnitLFO
    color: "transparent"
    border.color: "#33c2ff"
    border.width: 1

    FontLoader { id: singleUnitLabelFont; source: "qrc:/resources/arial.ttf" }

    Image { source: "qrc:/resources/alum-texture-blue-900x900.jpg"; fillMode: Image.Tile; anchors.fill: parent;  opacity: 0.3 }

    property int singleUnitLFOID
    property alias singleUnitLFOText : tabButtonLFO.tabButtonLFOLabelText
    property alias singleUnitLFOLabelText: singleUnitLFOLabel.text

    TabButtonLFO {
        id: tabButtonLFO
        anchors.horizontalCenter: parent.horizontalCenter
        y: -35
        width: 86
        height: 22
        tabButtonLFOID : singleUnitLFO.singleUnitLFOID
    }

    Text {
        id: singleUnitLFOLabel
        x: 10
        y: 10
        color: "#ffffff"
        font.pixelSize: 14
        font.family: singleUnitLabelFont.font
        font.weight: Font.Normal
    }

    FreqLabelLFO {
        id: freqLabelLFO
        anchors.right: parent.right
        anchors.rightMargin: 20
        y: 7
        freqLabelLFOID: singleUnitLFO.singleUnitLFOID
    }

    Button {
        id: freqRefreshButtonLFO
        width: 76
        height: freqLabelLFO.height
        text: qsTr(" PROBE ")
        anchors.right: freqLabelLFO.left
        anchors.rightMargin: 10
        anchors.verticalCenter: freqLabelLFO.verticalCenter

        onClicked: {
            // Request a current VCOs frequencies
            Mixer.requestVCOFrequency(singleUnitLFO.singleUnitLFOID);
        }

        contentItem: Text {
            text: freqRefreshButtonLFO.text
            font: freqRefreshButtonLFO.font
            color: freqRefreshButtonLFO.down ? "darkgoldenrod" : "black"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            color: "dimgray"
            border.color: "#33c2ff"
            border.width: 1
        }
    }

    FreqSelectorLFO {
        id: freqSelectorLFO
        anchors.left: parent.left
        anchors.leftMargin: 30
        y: 70
        freqSelectorLFOID: singleUnitLFO.singleUnitLFOID
    }

    Text {
        id: potFrequencyLFOLabel
        anchors.horizontalCenter: potFrequencyLFO.horizontalCenter
        anchors.top: potFrequencyLFO.top
        anchors.topMargin: -50
        color: "black"
        font.pixelSize: 13
        font.family: singleUnitLabelFont.font
        font.weight: Font.Normal
        text: qsTr("COARSE")
    }

    PotFrequencyLFO {
        id: potFrequencyLFO
        x: 200
        y: 100
        potFrequencyLFOID: singleUnitLFO.singleUnitLFOID
    }

    Text {
        id: potFreqFineLFOLabel
        anchors.horizontalCenter: potFreqFineLFO.horizontalCenter
        anchors.top: potFreqFineLFO.top
        anchors.topMargin: -50
        color: "black"
        font.pixelSize: 13
        font.family: singleUnitLabelFont.font
        font.weight: Font.Normal
        text: qsTr("FINE")
    }

    PotFreqFineLFO {
        id: potFreqFineLFO
        x: 185
        y: 290
        potFreqFineLFOID: singleUnitLFO.singleUnitLFOID
    }

    Text {
        id: potDutyCycleLFOLabel
        anchors.horizontalCenter: potDutyCycleLFO.horizontalCenter
        anchors.top: potDutyCycleLFO.top
        anchors.topMargin: -50
        color: "black"
        font.pixelSize: 13
        font.family: singleUnitLabelFont.font
        font.weight: Font.Normal
        text: qsTr("DUTY")
    }

    PotDutyCycleLFO {
        id: potDutyCycleLFO
        x: 320
        y: 280
        potDutyCycleLFOID: singleUnitLFO.singleUnitLFOID
    }

    HarmonicsSwitchesLFO {
        id: harmonicsSwitchesLFO
        anchors.left: parent.left
        anchors.leftMargin: 25
        y: 270
        harmonicsSwitchesLFOID: singleUnitLFO.singleUnitLFOID
    }
}

