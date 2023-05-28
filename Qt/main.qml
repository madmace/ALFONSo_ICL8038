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

import com.alfonso.qml.constants 1.0

import "./content"

ApplicationWindow {
    id: mainPanel
    objectName: "MainWindowObject"
    width: Constants.mainWidth
    height: Constants.mainHeight
    visible: true
    title: Constants.mainWindowTitle
    maximumWidth: mainPanel.width
    maximumHeight: mainPanel.height
    minimumWidth: mainPanel.width
    minimumHeight: mainPanel.height

    signal underClosingALFONSo()

    // Signal emitted at startup implementation
    //onAfterRendering: {
    //    splashWindow.isALFONSoUSBPresent();
    //}

    onClosing: {

        console.log("ALFONSo Closing...")
        mainPanel.underClosingALFONSo();
    }

    LFOMixer {
        id: panelLFOMixer
        enabled: false
        visible: false
        width: parent.width
        height: parent.height
    }

    Splash {
        objectName: "SplashWindowObject"
        id : splashWindow
        enabled: true
        visible: true
        width: parent.width
        height: parent.height
    }

//    Loader {
//        id: mainLoader
//        anchors {
//            left: parent.left
//            right: parent.right
//            top: parent.bottom
//            bottom: parent.bottom
//        }
//    }

}

