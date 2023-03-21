/*******************************************************************************

 A.L.F.O.N.S
 Author : Emiliano Mazza
 Version : 1.0
 Created on Date : 15/18/2020
 Last update     : 31/01/2023

 CopyRight 2006-2015 all rights are reserved

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE AUTHOR SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

*******************************************************************************/

#include "mixer.h"
#include "protocol.h"
#include "serialPortController.h"

#include <QDebug>

// Initialize Singleton
Mixer *Mixer::oMixer = 0;

// Constructor
Mixer::Mixer(QObject *parent) : QObject{parent}
{
    // Create Main Mixer Data Model
    m_hsLFOMixerModel = new QHash<int, SingleUnitLFOModel*>;
}

// Mixer Destructor
Mixer::~Mixer() {

}

// First initialize the instance. All classes will access via this instance
Mixer* Mixer::getInstance() {
    // If already created
    if (!oMixer) {
        // Makes Singleton
        oMixer = new Mixer();
    }
    return oMixer;
}

// Properties
QHash<int, SingleUnitLFOModel*>* Mixer::getLFOMixerModel()
{
    return m_hsLFOMixerModel;
}

// Send Request for Sync All command to serial port
void Mixer::sendRequestSyncAllVCO() {

    QByteArray byBuffer;

    // Adds Sync All request command
    Protocol::append2Bytes(byBuffer, Protocol::SYNC_REQ_ALL);

    // VCOs model iterator
    QHashIterator<int, SingleUnitLFOModel*> i(*m_hsLFOMixerModel);
    while (i.hasNext()) {
        i.next();

        qDebug("Mixer::sendRequestSyncAllVCO Adds Mixer ID -> %d", i.key());

        // Adds VCO settings

        // VCO ID
        byBuffer.append((quint8)i.key());
        // VCO Enable
        byBuffer.append(i.value()->getTabButtonLFOSelected());
        // VCO Selector
        byBuffer.append(i.value()->getFreqSelectorLFOValue());
        // VCO Frequency Coarse
        byBuffer.append(i.value()->getPotFrequencyLFOValue());
        // VCO Frequency Fine
        byBuffer.append(i.value()->getPotFreqFineLFOValue());
        // VCO Duty Cycle
        byBuffer.append(i.value()->getPotDutyCycleLFOValue());
        // VCO Harmonic Sine output
        byBuffer.append(i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSineSelected());
        // VCO Harmonic Square output
        byBuffer.append(i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSquareSelected());
        // VCO Harmonic Triangle output
        byBuffer.append(i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOTriangleSelected());
    }

    // Send to Serial Port
    SerialPortController::getInstance()->requestSendRawData(byBuffer);

    // Update infomations
    emit updateBottomInfoText("VCOs Synchronized.");

}

// Store the status of the single control
void Mixer::setMixerValue(int iID, int iType, int iValue) {

   qDebug("Mixer ID -> %d Type -> %d Value() -> %d", iID, iType, iValue);

   // Control if single VCO model is already present
   if (!m_hsLFOMixerModel->contains(iID)) {
       // Not present

       // Create single VCO model
       SingleUnitLFOModel* p_oNewVCOModel = new SingleUnitLFOModel();
       // Adds to Hash
       m_hsLFOMixerModel->insert(iID, p_oNewVCOModel);
   }

   // Save data into the model
   updateMixerModel((quint8)iID, (quint8)iType, (quint8)iValue);

   // Send to Serial Port
   SerialPortController::getInstance()->requestSendWidgetCommand((quint8)iID, (quint8)iType, (quint8)iValue);

}

// Save data into the model
void Mixer::updateMixerModel(quint8 byID, quint8 byType, quint8 byValue) {

    SingleUnitLFOModel* pVCOModel = m_hsLFOMixerModel->value(byID);

    switch (byType) {
        case Protocol::tabButtonTypeValue:

            // TabButtonLFO
            pVCOModel->setTabButtonLFOSelected(byValue);

            break;

        case Protocol::freqSelectorTypeValue:

            // TabButtonLFO
            pVCOModel->setFreqSelectorLFOValue(byValue);

            break;

        case Protocol::frequencyPotTypeValue:

            // PotFrequencyLFO
            pVCOModel->setPotFrequencyLFOValue(byValue);

            break;

        case Protocol::freqFinePotTypeValue:

            // PotFreqFineLFO
            pVCOModel->setPotFreqFineLFOValue(byValue);

            break;

        case Protocol::dutyCyclePotTypeValue:

            // PotDutyCycleLF
            pVCOModel->setPotDutyCycleLFOValue(byValue);

            break;

        case Protocol::toggleSwitchSineTypeValue:

            // ToggleSwitchLFOSine
            pVCOModel->getHarmonicsSwitchesLFO()->setToggleSwitchLFOSineSelected(byValue);

            break;

        case Protocol::toggleSwitchSquareTypeValue:

            // ToggleSwitchLFOSquare
            pVCOModel->getHarmonicsSwitchesLFO()->setToggleSwitchLFOSquareSelected(byValue);

            break;

        case Protocol::toggleSwitchTriangleTypeValue:

            // ToggleSwitchLFOTriangle
            pVCOModel->getHarmonicsSwitchesLFO()->setToggleSwitchLFOTriangleSelected(byValue);

            break;
    }
}

// QML singleton type provider function (callback).
// Second, define the singleton type provider function (callback).
QObject* Mixer::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {

    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    // C++ and QML instance they are the same instance
    return Mixer::getInstance();
}
