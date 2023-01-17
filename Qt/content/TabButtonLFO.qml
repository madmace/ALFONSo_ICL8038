import QtQuick 2.8
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: tabButtonLFO
    width: 86
    height: 22
    state: "state_normal"
    property alias tabButtonLFOLabelText: tabButtonLabel.text
    property alias tabButtonLFOID: tabButtonObj.tabButtonID
    property alias tabButtonLFOType: tabButtonObj.tabButtonType

    function toggle() {
        if (tabButtonObj.tabButtonSelected) {
            tabButtonLFO.state = "state_normal";
            tabButtonObj.setTabButtonSelected(false);
        } else {
            tabButtonLFO.state = "state_checked";
            tabButtonObj.setTabButtonSelected(true);
        }

        //console.log("isSelected -> ", tabButtonObj.tabButtonSelected)
    }

    TabButton {
        id: tabButtonObj
        tabButtonType: Protocol.tabButtonType
    }

    Connections {
        target: tabButtonObj
    }

    Rectangle {
        id: tabButtonBackground
        x: 0
        y: 0
        width: 86
        height: 22
        color: "#4d33c2ff"
        border.color: "#33c2ff"
        border.width: 1

        MouseArea {
            anchors.fill: parent
            onPressed: tabButtonLFO.state = "state_pressed"
            onClicked: toggle()
        }
    }

    Text {
        id: tabButtonLabel
        x: 0
        y: 0
        width: 87
        height: 22
        color: "#dcdada"
        text: qsTr("Tab Header")
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: "Abel"
        font.weight: Font.Normal
    }
    states: [
        State {
            name: "state_pressed"
        },
        State {
            name: "state_checked"
            extend: "state_pressed"

            PropertyChanges {
                target: tabButtonBackground
                color: "#33c2ff"
            }

            PropertyChanges {
                target: tabButtonLabel
                color: "#111112"
            }
        },
        State {
            name: "state_normal"
            extend: "state_pressed"

            PropertyChanges {
                target: tabButtonBackground
                color: "transparent"
            }

            PropertyChanges {
                target: tabButtonLabel
                color: "#33c2ff"
            }
        }
    ]
}
