import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.qml.controls 1.0

Item {
    id: toggleSwitchLFO
    state: "state_normal"
    property alias toggleSwitchLFOID: toggleSwitchObj.toggleSwitchID
    property alias toggleSwitchLFOType: toggleSwitchObj.toggleSwitchType

    function toggle() {
        if (toggleSwitchObj.toggleSwitchSelected) {
            toggleSwitchLFO.state = "state_normal";
            toggleSwitchObj.setToggleSwitchSelected(false);
        } else {
            toggleSwitchLFO.state = "state_checked";
            toggleSwitchObj.setToggleSwitchSelected(true);
        }

        //console.log("isSelected -> ", toggleSwitchObj.toggleSwitchSelected)
    }

    ToggleSwitch {
        id: toggleSwitchObj
    }

    Connections {
        target: toggleSwitchObj
    }

    Image {
        id: background
        width: toggleSwitchLFO.width
        height: toggleSwitchLFO.height
        source: "qrc:/resources/ToggleSwitch.svg"

        MouseArea {
            anchors.fill: parent;
            onClicked: toggle()
        }

        Text {
            id: label
            x: toggleSwitchLFO.width - knob.width - (knob.width * 2)
            y: 8

            color: "#ffffff"
            text: qsTr("OFF")
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
            font.family: "Abel"
            font.weight: Font.Normal
        }
    }

    Image {
        id: knob
        x: 2
        y: 3
        width: toggleSwitchLFO.width / 2.5
        height: toggleSwitchLFO.height - 4
        source: "qrc:/resources/ToggleSwitchKnob.svg"

        MouseArea {
            anchors.fill: parent
            drag.target: knob; drag.axis: Drag.XAxis; drag.minimumX: 2; drag.maximumX: toggleSwitchLFO.width - knob.width
            onClicked: toggle()
        }
    }

    states: [
        State {
            name: "state_checked"

            PropertyChanges { target: knob; x: toggleSwitchLFO.width - knob.width }
            PropertyChanges { target: background; source: "qrc:/resources/ToggleSwitchSelected.svg" }
            PropertyChanges { target: label; text: qsTr("ON") }
            PropertyChanges { target: label; x: label.width - 8 }
        },
        State {
            name: "state_normal"

            PropertyChanges { target: knob; x: 2 }
            PropertyChanges { target: background; source: "qrc:/resources/ToggleSwitch.svg" }
            PropertyChanges { target: label; text: qsTr("OFF") }
            PropertyChanges { target: label; x: toggleSwitchLFO.width - knob.width - 8}
        }
    ]

    transitions: Transition {
        NumberAnimation { target: knob; properties: "x"; easing.type: Easing.InOutQuad; duration: 200 }
        NumberAnimation { target: label; properties: "x"; easing.type: Easing.InOutQuad; duration: 200 }
    }
}

