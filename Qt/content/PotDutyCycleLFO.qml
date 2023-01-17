import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import com.alfonso.protocol 1.0
import com.alfonso.qml.controls 1.0

Item {
    id: potDutyCycleLFO
    width: 90
    height: 90
    property alias potDutyCycleLFOID: potDutyCycleObj.potID

    Image {
        id: potDutyCycleGauge
        x: -11
        y: -11
        width: parent.width + 20;
        height: parent.height + 10;
        source: "qrc:/resources/PotGauge.svg"
        fillMode: Image.PreserveAspectFit

        Text {
            id: labelMinDutyCycle
            x: 1
            y: 100
            color: "#ffffff"
            text: qsTr("1%")
            font.pixelSize: 12
            font.family: "Abel"
            font.weight: Font.Normal
        }

        Text {
            id: labelMaxDutyCycle
            x: 90
            y: 100
            color: "#ffffff"
            text: qsTr("99%")
            font.pixelSize: 12
            font.family: "Abel"
            font.weight: Font.Normal
        }

        Text {
            id: labelHalfDutyCycle
            x: 46
            y: -14
            color: "#ffffff"
            text: qsTr("50%")
            font.pixelSize: 12
            font.family: "Abel"
            font.weight: Font.Normal
        }
    }

    Potentiometer {
        id: potDutyCycleObj
        potType: Protocol.dutyCyclePotType
        potWidth: 90
        potHeight: 90
        potMinRange: 1
        potMaxRange: 255
        potSpreadAngle: 280
        potValue: 127
    }

    Connections {
        target: potDutyCycleObj
        function onPotClockWise(iDeg) {
            knobDutyCycleView.rotation += iDeg
        }
        function onPotCouterClockWise(iDeg) {
            knobDutyCycleView.rotation -= iDeg
        }
    }

    Image {
        id: knobDutyCycleView
        width: potDutyCycleObj.potWidth
        height: potDutyCycleObj.potHeight
        source: "qrc:/resources/PotDutyCycleMetal.svg"
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        anchors.fill: parent
        onClicked : (mouse)=> {
            if (mouse.button === Qt.LeftButton) {
                // Cals Angle and fire signals
                potDutyCycleObj.toAngle(mouse.x, mouse.y)
            }
        }

        onMouseXChanged: (mouse)=> {
            // Cals Angle and fire signals
            potDutyCycleObj.toAngle(mouse.x, mouse.y)
        }
        onMouseYChanged: (mouse)=> {
            // Cals Angle and fire signals
            potDutyCycleObj.toAngle(mouse.x, mouse.y)
        }
    }
}
