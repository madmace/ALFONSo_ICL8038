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

import QtQuick 2.8

Item {
    id: viewPanelLFO
    state: "state_state_active"

    Rectangle {
        id: panelBackground
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        color: "#2e2e2e"
        border.color: "#33c2ff"
        border.width: 1
    }

    Rectangle {
        id: panelBottomBar
        x: 0
        y: 404
        width: parent.width
        height: 46
        color: "#38383f"
        border.color: "#33c2ff"
        border.width: 1
    }

    Rectangle {
        id: panelTopBar
        x: 0
        y: 0
        width: parent.width
        height: 32
        color: "#111112"
        border.color: "#33c2ff"
        border.width: 1
    }
    states: [
        State {
            name: "state_state_active"
        },
        State {
            name: "state_state_normal"
            extend: "state_state_active"

            PropertyChanges {
                target: panelBackground
                border.color: "#767676"
            }

            PropertyChanges {
                target: panelTopBar
                border.color: "#767676"
            }

            PropertyChanges {
                target: panelBottomBar
                border.color: "#767676"
            }
        }
    ]
}
