import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: singleUnitLFO
    color: "transparent"
    border.color: "#33c2ff"
    border.width: 1

    Image { source: "qrc:/resources/alum-texture-blue-900x900.jpg"; fillMode: Image.Tile; anchors.fill: parent;  opacity: 0.3 }

    property int singleUnitLFOID
    property alias singleUnitLFOText : tabButtonLFO.tabButtonLFOLabelText
    property alias singleUnitLFOLabelText: singleUnitLFOLabel.text

    TabButtonLFO {
        id: tabButtonLFO
        anchors.horizontalCenter: parent.horizontalCenter
        y: -35
        width: 86
        height: 22
        tabButtonLFOID : singleUnitLFO.singleUnitLFOID
    }

    Text {
        id: singleUnitLFOLabel
        x: 10
        y: 10
        color: "#ffffff"
        font.pixelSize: 14
        font.family: "Abel"
        font.weight: Font.Normal
    }

    PotFrequencyLFO {
        id: potFrequencyLFO
        x: 95
        y: 65
        potFrequencyLFOID: singleUnitLFO.singleUnitLFOID
    }

    HarmonicsSwitchesLFO {
        x: 20
        y: 210
        harmonicsSwitchesLFOID: singleUnitLFO.singleUnitLFOID
    }

    PotDutyCycleLFO {
        x: 170
        y: 220
        potDutyCycleLFOID: singleUnitLFO.singleUnitLFOID
    }
}

