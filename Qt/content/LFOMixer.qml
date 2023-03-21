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
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.qml.controls 1.0

Item {
    id: lFOMixer
    rotation: 0

    readonly property int lFOMixerWidth: 450
    readonly property int lFOMixerHeight: 405

    property alias singleUnitLFO: singleUnitLFO1

    ViewPanelLFO {
        id: viewPanelLFO
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        visible: true
        clip: false
        state: "state_state_normal"
    }

    SingleUnitLFO {
        id: singleUnitLFO1
        anchors.left: parent.left
        anchors.leftMargin: 10
        y: 40
        width: lFOMixerWidth
        height: lFOMixerHeight
        singleUnitLFOText: "VCO/LFO 1"
        singleUnitLFOLabelText: "MIX MODULE 1"
        singleUnitLFOID: 1
    }

    SingleUnitLFO {
        id: singleUnitLFO2
        anchors.left: singleUnitLFO1.right
        anchors.leftMargin: 10
        y: 40
        width: lFOMixerWidth
        height: lFOMixerHeight
        singleUnitLFOText: "VCO/LFO 2"
        singleUnitLFOLabelText: "MIX MODULE 2"
        singleUnitLFOID: 2
    }

    SingleUnitLFO {
        id: singleUnitLFO3
        anchors.left: singleUnitLFO2.right
        anchors.leftMargin: 10
        y: 40
        width: lFOMixerWidth
        height: lFOMixerHeight
        singleUnitLFOText: "VCO/LFO 3"
        singleUnitLFOLabelText: "MIX MODULE 3"
        singleUnitLFOID: 3
    }

    SingleUnitLFO {
        id: singleUnitLFO4
        anchors.left: singleUnitLFO3.right
        anchors.leftMargin: 10
        y: 40
        width: lFOMixerWidth
        height: lFOMixerHeight
        singleUnitLFOText: "VCO/LFO 4"
        singleUnitLFOLabelText: "MIX MODULE 4"
        singleUnitLFOID: 4
    }
}
