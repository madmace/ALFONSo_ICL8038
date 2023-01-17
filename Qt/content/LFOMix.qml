import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.qml.controls 1.0

Item {
    id: lFOMix
    rotation: 0

    ViewPanelLFO {
        id: viewPanelLFO
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        visible: true
        clip: false
        state: "state_state_normal"
    }

    SingleUnitLFO {
        id: singleUnitLFO1
        x: 10
        y: 40
        width: 300
        height: 350
        singleUnitLFOText: "VCO/LFO 1"
        singleUnitLFOLabelText: "MIX MODULE 1"
        singleUnitLFOID: 1
    }

    SingleUnitLFO {
        id: singleUnitLFO2
        x: 320
        y: 40
        width: 300
        height: 350
        singleUnitLFOText: "VCO/LFO 2"
        singleUnitLFOLabelText: "MIX MODULE 2"
        singleUnitLFOID: 2
    }

    SingleUnitLFO {
        id: singleUnitLFO3
        x: 630
        y: 40
        width: 300
        height: 350
        singleUnitLFOText: "VCO/LFO 3"
        singleUnitLFOLabelText: "MIX MODULE 3"
        singleUnitLFOID: 3
    }

    SingleUnitLFO {
        id: singleUnitLFO4
        x: 940
        y: 40
        width: 300
        height: 350
        singleUnitLFOText: "VCO/LFO 4"
        singleUnitLFOLabelText: "MIX MODULE 4"
        singleUnitLFOID: 4
    }
}
