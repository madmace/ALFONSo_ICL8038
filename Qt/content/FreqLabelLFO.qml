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
    state: "state_normal"

    FontLoader { id: freqLabelLFOLabelFont; source: "qrc:/resources/arial.ttf" }

    Rectangle {
        id: freqLabelBackground
        x: 0
        y: 0
        width: 86
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
        width: 87
        height: 22
        color: "#dcdada"
        text: qsTr("----.-- Hz")
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: freqLabelLFOLabelFont.font
        font.weight: Font.Normal
    }
}
