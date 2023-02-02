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

import com.alfonso.protocol 1.0

Item {
    id: harmonicsSwitchesLFO
    property int harmonicsSwitchesLFOID
    property alias toggleSwitchLFOSineSelected: toggleSwitchLFO1.toggleSwitchLFOSelected
    property alias toggleSwitchLFOSquareSelected: toggleSwitchLFO2.toggleSwitchLFOSelected
    property alias toggleSwitchLFOTriangleSelected: toggleSwitchLFO3.toggleSwitchLFOSelected

    Item {
        id: toggleSwitchLFOSine

        ToggleSwitchLFO {
            id: toggleSwitchLFO1
            width: 70
            height: 30
            toggleSwitchLFOID: harmonicsSwitchesLFO.harmonicsSwitchesLFOID
            toggleSwitchLFOType: Protocol.toggleSwitchSineType
        }

        Image {
            id: toggleSwitchLFOSineLabel
            anchors.left: toggleSwitchLFO1.right
            anchors.verticalCenter: toggleSwitchLFO1.verticalCenter
            anchors.leftMargin: 5
            width: 30
            height: 20
            source: "qrc:/resources/SineLabel.svg"
            fillMode: Image.PreserveAspectFit
        }
    }

    Item {
        id: toggleSwitchLFOSquare
        anchors.horizontalCenter: toggleSwitchLFOSine.horizontalCenter
        anchors.top: toggleSwitchLFOSine.bottom
        anchors.topMargin: 38

        ToggleSwitchLFO {
            id: toggleSwitchLFO2
            width: 70
            height: 30
            toggleSwitchLFOID: harmonicsSwitchesLFO.harmonicsSwitchesLFOID
            toggleSwitchLFOType: Protocol.toggleSwitchSquareType
        }

        Image {
            id: toggleSwitchLFOSquareLabel
            anchors.left: toggleSwitchLFO2.right
            anchors.verticalCenter: toggleSwitchLFO2.verticalCenter
            anchors.leftMargin: 5
            width: 30
            height: 20
            source: "qrc:/resources/SquareLabel.svg"
            fillMode: Image.PreserveAspectFit
        }
    }

    Item {
        id: toggleSwitchLFOTriangle
        anchors.horizontalCenter: toggleSwitchLFOSquare.horizontalCenter
        anchors.top: toggleSwitchLFOSquare.bottom
        anchors.topMargin: 38

        ToggleSwitchLFO {
            id: toggleSwitchLFO3
            width: 70
            height: 30
            toggleSwitchLFOID: harmonicsSwitchesLFO.harmonicsSwitchesLFOID
            toggleSwitchLFOType: Protocol.toggleSwitchTriangleType
        }

        Image {
            id: toggleSwitchLFOTriangleLabel
            anchors.left: toggleSwitchLFO3.right
            anchors.verticalCenter: toggleSwitchLFO3.verticalCenter
            anchors.leftMargin: 5
            width: 30
            height: 20
            source: "qrc:/resources/TriangleLabel.svg"
            fillMode: Image.PreserveAspectFit
        }
    }
}
