import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.mixer 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: freqSelectorButtonLFO
    state: "state_normal"

    property int freqSelectorButtonIndex
    property alias freqSelectorButtonText: freqSelectorButtonLabel.text

    function toggle() {

        freqSelectorButtonLFO.state = "state_checked";

        //console.log("isSelected -> ", tabButtonObj.tabButtonSelected)
        console.log("isSelected")
    }

    Image {
        id: freqSelectorButton
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit

        Text {
            id: freqSelectorButtonLabel
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            width: 87
            height: 22
            color: "black"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
            font.family: "Abel"
            font.weight: Font.Normal
        }

        Image {
            id: freqSelectorButtonLED
            anchors.left: freqSelectorButton.right
            anchors.leftMargin: 7
            anchors.verticalCenter: freqSelectorButton.verticalCenter
            width: 15
            height: 15
            fillMode: Image.PreserveAspectFit
        }

        MouseArea {
            anchors.fill: parent

            onClicked: freqSelectorObj.setFreqSelectorSelectedIndex(freqSelectorButtonIndex);
        }
    }

    states: [
        State {
            name: "state_checked"

            PropertyChanges { target: freqSelectorButton; source: "qrc:/resources/FreqSelectorMetalSelected.svg" }
            PropertyChanges { target: freqSelectorButtonLED; source: "qrc:/resources/RedLight.svg" }
        },
        State {
            name: "state_normal"

            PropertyChanges { target: freqSelectorButton; source: "qrc:/resources/FreqSelectorMetalUnselected.svg" }
            PropertyChanges { target: freqSelectorButtonLED; source: "qrc:/resources/GrayLight.svg" }
        }
    ]

}
