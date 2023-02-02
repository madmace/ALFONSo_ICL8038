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

import com.alfonso.mixer 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: toggleSwitchLFO
    state: "state_normal"
    property alias toggleSwitchLFOID: toggleSwitchObj.toggleSwitchID
    property alias toggleSwitchLFOType: toggleSwitchObj.toggleSwitchType
    property alias toggleSwitchLFOSelected: toggleSwitchObj.toggleSwitchSelected

    Component.onCompleted: {
        // Force first toggleSwitch value
        Mixer.setMixerValue(toggleSwitchObj.toggleSwitchID, toggleSwitchObj.toggleSwitchType, toggleSwitchObj.toggleSwitchSelected);
    }

    function toggle() {
        if (toggleSwitchObj.toggleSwitchSelected) {
            toggleSwitchLFO.state = "state_normal";
            toggleSwitchObj.setToggleSwitchSelected(false);
        } else {
            toggleSwitchLFO.state = "state_checked";
            toggleSwitchObj.setToggleSwitchSelected(true);
        }

        //console.log("isSelected -> ", toggleSwitchObj.toggleSwitchSelected)
    }

    ToggleSwitch {
        id: toggleSwitchObj

        onToggleSwitchSelectedChanged: (newSelection)=> {
            // Save ToggleSwitch value
            Mixer.setMixerValue(toggleSwitchObj.toggleSwitchID, toggleSwitchObj.toggleSwitchType, toggleSwitchObj.toggleSwitchSelected);
        }
    }

    Connections {
        target: toggleSwitchObj
    }

    Image {
        id: background
        width: toggleSwitchLFO.width
        height: toggleSwitchLFO.height
        source: "qrc:/resources/ToggleSwitch.svg"

        MouseArea {
            anchors.fill: parent;
            onClicked: toggle()
        }

        Text {
            id: label
            x: toggleSwitchLFO.width - knob.width - (knob.width * 2)
            y: 8

            color: "#ffffff"
            text: qsTr("OFF")
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
            font.family: "Abel"
            font.weight: Font.Normal
        }
    }

    Image {
        id: knob
        x: 2
        y: 3
        width: toggleSwitchLFO.width / 2.5
        height: toggleSwitchLFO.height - 4
        source: "qrc:/resources/ToggleSwitchKnob.svg"

        MouseArea {
            anchors.fill: parent
            drag.target: knob; drag.axis: Drag.XAxis; drag.minimumX: 2; drag.maximumX: toggleSwitchLFO.width - knob.width
            onClicked: toggle()
        }
    }

    states: [
        State {
            name: "state_checked"

            PropertyChanges { target: knob; x: toggleSwitchLFO.width - knob.width }
            PropertyChanges { target: background; source: "qrc:/resources/ToggleSwitchSelected.svg" }
            PropertyChanges { target: label; text: qsTr("ON") }
            PropertyChanges { target: label; x: label.width - 8 }
        },
        State {
            name: "state_normal"

            PropertyChanges { target: knob; x: 2 }
            PropertyChanges { target: background; source: "qrc:/resources/ToggleSwitch.svg" }
            PropertyChanges { target: label; text: qsTr("OFF") }
            PropertyChanges { target: label; x: toggleSwitchLFO.width - knob.width - 8}
        }
    ]

    transitions: Transition {
        NumberAnimation { target: knob; properties: "x"; easing.type: Easing.InOutQuad; duration: 200 }
        NumberAnimation { target: label; properties: "x"; easing.type: Easing.InOutQuad; duration: 200 }
    }
}

