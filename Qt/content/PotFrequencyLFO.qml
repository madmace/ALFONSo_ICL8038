import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: potFrequencyLFO
    width: potFrequencyObj.potWidth
    height: potFrequencyObj.potHeight
    property alias potFrequencyLFOID: potFrequencyObj.potID

    Image {
        id: potFrequencyGauge
        x: -10
        y: -11
        width: parent.width + 20;
        height: parent.height + 10;
        source: "qrc:/resources/PotGauge.svg"
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: label10Hz
        x: -26
        y: 95
        color: "#ffffff"
        text: qsTr("10Hz")
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    Text {
        id: label4KHz
        x: -48
        y: 43
        color: "#ffffff"
        text: qsTr("4KHz")
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    Text {
        id: label8KHz
        x: -32
        y: -4
        color: "#ffffff"
        text: qsTr("8KHz")
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    Text {
        id: label12KHz
        x: 28
        y: -28
        color: "#ffffff"
        text: qsTr("12KHz")
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    Text {
        id: label16KHz
        x: 95
        y: -4
        color: "#ffffff"
        text: qsTr("16KHz")
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    Text {
        id: label18KHz
        x: 112
        y: 43
        color: "#ffffff"
        text: qsTr("18KHz")
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    Text {
        id: label20KHz
        x: 93
        y: 95
        color: "#ffffff"
        text: qsTr("20KHz")
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    Potentiometer {
        id: potFrequencyObj
        potType: Protocol.frequencyPotType
        potWidth: 100
        potHeight: 100
        potMinRange: 1
        potMaxRange: 255
        potSpreadAngle: 280
        potValue: 127
    }

    Connections {
        target: potFrequencyObj
        function onPotClockWise(iDeg) {
            knobFrequencyView.rotation += iDeg
        }
        function onPotCouterClockWise(iDeg) {
            knobFrequencyView.rotation -= iDeg
        }
    }

    Image {
        id: knobFrequencyView
        width: potFrequencyObj.potWidth
        height: potFrequencyObj.potHeight
        source: "qrc:/resources/PotFrequencyMetal.svg"
        fillMode: Image.PreserveAspectFit

//            Behavior on rotation {
//                NumberAnimation {
//                    duration: 1
//                }
//            }
    }

    MouseArea {
        //hoverEnabled: true
        anchors.fill: parent
        onClicked : (mouse)=> {
            if (mouse.button === Qt.LeftButton) {
                // Cals Angle and fire signals
                potFrequencyObj.toAngle(mouse.x, mouse.y)

                //console.log("mouse.x ", mouse.x)
                //console.log("mouse.y ", mouse.y)
            }
        }

        onMouseXChanged: (mouse)=> {
            // Cals Angle and fire signals
            potFrequencyObj.toAngle(mouse.x, mouse.y)
        }
        onMouseYChanged: (mouse)=> {
            // Cals Angle and fire signals
            potFrequencyObj.toAngle(mouse.x, mouse.y)
        }
    }
}
