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

    readonly property string swVersion: "0.0.1"
    readonly property int splashHeight: 450

    readonly property int mainWidth: 1250
    readonly property int mainHeight: 450


    //readonly property color backgroundColor: "#443224"
    //readonly property int defaultMargin: 8

    /*
    * Constant GUI Messages
    */

    readonly property string splashSeachingUSBDevice: "Searching ALFONSo USB device..."
    readonly property string splashUSBDeviceNotConnected: "ALFONSo USB device not connected."
    readonly property string splashUSBDeviceNotFound: "ALFONSo USB device not found."
    readonly property string splashUSBDeviceFound: "ALFONSo USB device found."
    readonly property string splashUSBPowerButton: "CONNECT"

}
