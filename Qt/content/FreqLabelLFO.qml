import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.mixer 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: freqLabelLFO
    width: 86
    height: 22
    state: "state_disabled"

    property alias freqLabelLFOID: freqLabelObj.freqLabelID
    property alias freqLabelLFOValue: freqLabelObj.freqLabelValue

    FontLoader { id: freqLabelLFOLabelFont; source: "qrc:/resources/arial.ttf" }

    Rectangle {
        id: freqLabelBackground
        x: 0
        y: 0
        width: 96
        height: 22
        //color: "#4d33c2ff"
        color: "#434343"
        border.color: "#33c2ff"
        border.width: 1
    }

    Text {
        id: freqLabelText
        x: 0
        y: 0
        width: 96
        height: 22
        font.pixelSize: 14
        anchors.horizontalCenter: freqLabelBackground.horizontalCenter
        anchors.verticalCenter: freqLabelBackground.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: freqLabelLFOLabelFont.font
        font.weight: Font.Normal
    }

    Connections {
        target: Mixer

        function onUpdateFrequencyText(byID, sFVCO) {
            // If update is for this VCO
            if (byID === freqLabelLFOID) {

                if (freqLabelLFO.state == "state_disabled") {
                    // Set state enabled
                    freqLabelLFO.state ="state_enabled";
                }

                freqLabelText.text = sFVCO + " Hz";
            }
        }

    }

    FreqLabel {
        id: freqLabelObj
    }

    states: [
        State {
            name: "state_enabled"

            PropertyChanges {
                target: freqLabelBackground
                color: "#e6b812"
            }

            PropertyChanges {
                target: freqLabelText
                color: "#111112"
            }
        },
        State {
            name: "state_disabled"

            PropertyChanges {
                target: freqLabelBackground
                color: "transparent"
            }

            PropertyChanges {
                target: freqLabelText
                color: "#dcdada"
                text: qsTr("----- Hz")
            }
        }
    ]
}
