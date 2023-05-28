import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.mixer 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: freqSelectorLFO
    property alias freqSelectorLFOID: freqSelectorObj.freqSelectorID
    property alias freqSelectorLFOType: freqSelectorObj.freqSelectorType
    property alias freqSelectorLFOSelectedIndex: freqSelectorObj.freqSelectorSelectedIndex

    Component.onCompleted: {
        // Display current state
        toggle();
        // Force first freqSelector value
        Mixer.setMixerValue(freqSelectorObj.freqSelectorID, freqSelectorObj.freqSelectorType, freqSelectorObj.freqSelectorSelectedIndex);
    }

    Connections {
        target: Mixer

        function onUpdateFreqSelector(byID, newValue)
        {
            // If update is for this VCO
            if (byID === freqSelectorLFOID) {
                // Set range
                freqSelectorObj.freqSelectorSelectedIndex = newValue;
                // Display current state
                toggle();
            }
        }
    }

    // Renders current selected selector
    function toggle() {

        // Reset all selector to normal state
        unToggleAll();

        switch (freqSelectorObj.freqSelectorSelectedIndex) {
            case freqSelectorObj.rangeHVCO:

                freqSelectorButtonHVCO.state = "state_checked";
                break;
            case freqSelectorObj.rangeVCO:

                freqSelectorButtonVCO.state = "state_checked";
                break;
            case freqSelectorObj.rangeLFO:

                freqSelectorButtonLFO.state = "state_checked";
                break;
            case freqSelectorObj.rangeVLFO:

                freqSelectorButtonVLFO.state = "state_checked";
                break;
        }

    }

    // Reset all selector to normal state
    function unToggleAll() {
        freqSelectorButtonHVCO.state = "state_normal";
        freqSelectorButtonVCO.state = "state_normal";
        freqSelectorButtonLFO.state = "state_normal";
        freqSelectorButtonVLFO.state = "state_normal";
    }

    FreqSelector {
        id: freqSelectorObj
        freqSelectorType: Protocol.freqSelectorType
        freqSelectorSelectedIndex: freqSelectorObj.rangeVCO

        onFreqSelectorSelectedIndexChanged: (indexValue)=> {
            // Save Selector value
            Mixer.setMixerValue(freqSelectorObj.freqSelectorID, freqSelectorObj.freqSelectorType, freqSelectorObj.freqSelectorSelectedIndex);
            // Display current state
            toggle();
        }
    }

    FreqSelectorButtonLFO {
        id: freqSelectorButtonHVCO
        x: 0
        y: 0
        width: 50
        height: 30
        freqSelectorButtonText: qsTr("HVCO")
        freqSelectorButtonIndex: freqSelectorObj.rangeHVCO
    }

    FreqSelectorButtonLFO {
        id: freqSelectorButtonVCO
        anchors.horizontalCenter: freqSelectorButtonHVCO.horizontalCenter
        anchors.top: freqSelectorButtonHVCO.bottom
        anchors.topMargin: 5
        width: 50
        height: 30
        freqSelectorButtonText: qsTr("VCO")
        freqSelectorButtonIndex: freqSelectorObj.rangeVCO
    }

    FreqSelectorButtonLFO {
        id: freqSelectorButtonLFO
        anchors.horizontalCenter: freqSelectorButtonVCO.horizontalCenter
        anchors.top: freqSelectorButtonVCO.bottom
        anchors.topMargin: 5
        width: 50
        height: 30
        freqSelectorButtonText: qsTr("LFO")
        freqSelectorButtonIndex: freqSelectorObj.rangeLFO
    }

    FreqSelectorButtonLFO {
        id: freqSelectorButtonVLFO
        anchors.horizontalCenter: freqSelectorButtonLFO.horizontalCenter
        anchors.top: freqSelectorButtonLFO.bottom
        anchors.topMargin: 5
        width: 50
        height: 30
        freqSelectorButtonText: qsTr("VLFO")
        freqSelectorButtonIndex: freqSelectorObj.rangeVLFO
    }
}
