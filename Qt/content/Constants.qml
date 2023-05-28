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

pragma Singleton
import QtQuick 2.12

QtObject {

    /*
    property FontLoader fontLoader: FontLoader {
        id: fontLoader
        source: "TitilliumWeb-Regular.ttf"
    }
    readonly property alias fontFamily: fontLoader.name
    */

    /*
    * Constants GUI Titles
    */

    readonly property string mainWindowTitle: "A.L.F.O.N.S.o Basic Mixer for ICL8038"

    readonly property int mainWidth: 1850
    readonly property int mainHeight: 500

    readonly property string swVersion: "0.0.1"
    readonly property int splashHeight: mainHeight
    readonly property string splashMainName: "Alfonso"
    readonly property string splashMainSlogan: "Analog Low Frequency Oscillator No linear Sequencer"

    /*
    * Constants GUI Messages
    */

    readonly property string splashSeachingUSBDevice: "Searching ALFONSo USB device..."
    readonly property string splashUSBDeviceNotConnected: "ALFONSo USB device not connected."
    readonly property string splashUSBDeviceNotFound: "ALFONSo USB device not found."
    readonly property string splashUSBDeviceFound: "ALFONSo USB device found."
    readonly property string splashUSBPowerButton: "CONNECT"

}
