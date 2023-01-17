import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.qml.constants 1.0

import "./content"

ApplicationWindow {
    id: lFOMix
    objectName: "MainWindowObject"
    width: Constants.mainWidth
    height: Constants.mainHeight
    visible: true
    title: qsTr("A.L.F.O.N.So Project")
    maximumWidth: lFOMix.width
    maximumHeight: lFOMix.height
    minimumWidth: lFOMix.width
    minimumHeight: lFOMix.height

    signal underClosingALFONSo()

    // Signal emitted at startup implementation
    //onAfterRendering: {
    //    splashWindow.isALFONSoUSBPresent();
    //}

    onClosing: {

        console.log("ALFONSo Closing...")
        lFOMix.underClosingALFONSo();
    }

    LFOMix {
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
        width: lFOMix.width
        height: lFOMix.height
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

