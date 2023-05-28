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
    id: tabButtonLFO
    width: 86
    height: 22
    state: "state_normal"
    property alias tabButtonLFOLabelText: tabButtonLabel.text
    property alias tabButtonLFOID: tabButtonObj.tabButtonID
    property alias tabButtonLFOType: tabButtonObj.tabButtonType
    property alias tabButtonLFOSelected: tabButtonObj.tabButtonSelected

    Component.onCompleted: {
        // Force first Potentiometer value
        Mixer.setMixerValue(tabButtonObj.tabButtonID, tabButtonObj.tabButtonType, tabButtonObj.tabButtonSelected);
    }

    Connections {
        target: Mixer

        function onUpdateVCOEnable(byID, isEnabled) {

            // If update is for this VCO
            if (byID === tabButtonLFOID) {
                // If enabled
                if (isEnabled) {
                    checked();
                } else {
                    normal();
                }

            }

        }
    }

    function normal() {
        tabButtonLFO.state = "state_normal";
        tabButtonObj.setTabButtonSelected(false);
    }

    function checked() {
        tabButtonLFO.state = "state_checked";
        tabButtonObj.setTabButtonSelected(true);
    }

    function toggle() {
        if (tabButtonObj.tabButtonSelected) {
            normal();
        } else {
            checked();
        }

        //console.log("isSelected -> ", tabButtonObj.tabButtonSelected)
    }

    TabButton {
        id: tabButtonObj
        tabButtonType: Protocol.tabButtonType

        onTabButtonSelectedChanged: (newSelection)=> {
            // Save TabButton value
            Mixer.setMixerValue(tabButtonObj.tabButtonID, tabButtonObj.tabButtonType, tabButtonObj.tabButtonSelected);
        }
    }

    Connections {
        target: tabButtonObj
    }

    Rectangle {
        id: tabButtonBackground
        x: 0
        y: 0
        width: 86
        height: 22
        color: "#4d33c2ff"
        border.color: "#33c2ff"
        border.width: 1

        MouseArea {
            anchors.fill: parent
            onPressed: tabButtonLFO.state = "state_pressed"
            onClicked: toggle()
        }
    }

    Text {
        id: tabButtonLabel
        x: 0
        y: 0
        width: 87
        height: 22
        color: "#dcdada"
        text: qsTr("Tab Header")
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: "Abel"
        font.weight: Font.Normal
    }

    states: [
        State {
            name: "state_pressed"
        },
        State {
            name: "state_checked"
            extend: "state_pressed"

            PropertyChanges {
                target: tabButtonBackground
                color: "#33c2ff"
            }

            PropertyChanges {
                target: tabButtonLabel
                color: "#111112"
            }
        },
        State {
            name: "state_normal"
            extend: "state_pressed"

            PropertyChanges {
                target: tabButtonBackground
                color: "transparent"
            }

            PropertyChanges {
                target: tabButtonLabel
                color: "#33c2ff"
            }
        }
    ]
}
