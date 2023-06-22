/*******************************************************************************

 A.L.F.O.N.S.o
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
#include "freqSelector.h"
#include "serialPortController.h"

#include <QDebug>

// Initialize Singleton
Mixer *Mixer::oMixer = 0;

// Constructor
Mixer::Mixer(QObject *parent) : QObject{parent}
{
    // Create Main Mixer Data Model
    m_mapLFOMixerModel = new QMap<int, SingleUnitLFOModel*>;

    // Inbound connections
    connect(SerialPortController::getInstance(), SIGNAL(receivedVCOFrequency(quint8,quint16)), this, SLOT(handleVCOFrequency(quint8,quint16)));
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
QMap<int, SingleUnitLFOModel*>* Mixer::getLFOMixerModel()
{
    return m_mapLFOMixerModel;
}

// Send Request for Sync All command to serial port
void Mixer::sendRequestSyncAllVCO() {

    QByteArray byBuffer;

    // Adds Sync All request command
    Protocol::append2Bytes(byBuffer, Protocol::SYNC_REQ_ALL);

    // VCOs model iterator
    QMapIterator<int, SingleUnitLFOModel*> i(*m_mapLFOMixerModel);
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

        qDebug("Mixer::sendRequestSyncAllVCO Adds TabButton value %d", i.value()->getTabButtonLFOSelected());
        qDebug("Mixer::sendRequestSyncAllVCO Adds FreqSelector value %d", i.value()->getFreqSelectorLFOValue());
        qDebug("Mixer::sendRequestSyncAllVCO Adds PotFrequency value %d", i.value()->getPotFrequencyLFOValue());
        qDebug("Mixer::sendRequestSyncAllVCO Adds PotFreqFine value %d", i.value()->getPotFreqFineLFOValue());
        qDebug("Mixer::sendRequestSyncAllVCO Adds PotDutyCycle value %d", i.value()->getPotDutyCycleLFOValue());
        qDebug("Mixer::sendRequestSyncAllVCO Adds ToggleSwitchLFOSine value %d", i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSineSelected());
        qDebug("Mixer::sendRequestSyncAllVCO Adds ToggleSwitchLFOSquare value %d", i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSquareSelected());
        qDebug("Mixer::sendRequestSyncAllVCO Adds ToggleSwitchLFOTriangle value %d", i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOTriangleSelected());
    }

    // Send to Serial Port
    SerialPortController::getInstance()->requestSendRawData(byBuffer);

    // Update infomations
    emit updateBottomInfoText("VCOs Synchronized.");

}

// Store the status of the single control
void Mixer::setMixerValue(int iID, int iType, int iValue) {

   qDebug("Mixer::setMixerValue() Mixer ID -> %d Type -> %d Value() -> %d", iID, iType, iValue);

   // Control if single VCO model is already present
   if (!m_mapLFOMixerModel->contains(iID)) {
       // Not present

       // Create single VCO model
       SingleUnitLFOModel* p_oNewVCOModel = new SingleUnitLFOModel();
       // Adds to Map
       m_mapLFOMixerModel->insert(iID, p_oNewVCOModel);
   }

   // Save data into the model
   updateMixerModel((quint8)iID, (quint8)iType, (quint8)iValue);

   // Send to Serial Port
   SerialPortController::getInstance()->requestSendWidgetCommand((quint8)iID, (quint8)iType, (quint8)iValue);

}

// Save data into the model
void Mixer::updateMixerModel(quint8 byID, quint8 byType, quint8 byValue) {

    SingleUnitLFOModel* pVCOModel = m_mapLFOMixerModel->value(byID);

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

// Load last configuration from JSON
void Mixer::loadJSONConfig(QString sConfigJSONFile) {

    QFile fConfigJSON;                  // JSON Configuration File
    QJsonParseError ojsParserError;     // JSON Engine parser error object

    QJsonDocument ojsConfDoc;       // JSON Document

    // Set configuration file name
    fConfigJSON.setFileName(sConfigJSONFile);

    // Test if exists
    if (!fConfigJSON.open(QIODevice::ReadOnly)) {
        // Doesn't exist

        // Warnings
        qWarning() << "Mixer::loadJSONConfig() Couldn't open last save configuration file " << sConfigJSONFile;

        // Create default JSON config file from model
        writeJSONConfig(sConfigJSONFile);

    } else {
        // Configuration file exist

        // Reads all bytes from JSON file
        QByteArray byarLastSaveConfig = fConfigJSON.readAll();
        ojsConfDoc = QJsonDocument::fromJson(byarLastSaveConfig, &ojsParserError);

        // Fail if JSON is invalid
        if (ojsParserError.error != QJsonParseError::NoError) {
            qCritical() << "Failed to parse assets index file : " << ojsParserError.errorString()
                        << "at offest " << QString::number(ojsParserError.offset);
        } else {

            // Make sure the root is object
            if (!ojsConfDoc.isObject()) {
                qCritical() << "Invalid assets index JSON : Root should be an array.";
            } else {

                // Reads Configuration JSON file and loads model
                readJSONConfig(ojsConfDoc.object());
            }
        }

    }

}

// Make config JSON File from model
void Mixer::writeJSONConfig(QString sConfigJSONFile) {

    QFile fConfigJSON;              // JSON Configuration File

    QJsonDocument ojsConfDoc;       // JSON Document
    QJsonObject ojsRootObject;      // JSON Root object
    QJsonArray ojsVCOsObject;       // All VCO JSON object

    // Set configuration file name
    fConfigJSON.setFileName(sConfigJSONFile);
    // Open JSON Config file
    if (!fConfigJSON.open(QIODevice::WriteOnly)) {
        // Doesn't exist

        // Warnings
        qWarning() << "Mixer::writeJSONConfig() Couldn't write last save configuration file " << sConfigJSONFile;

    } else {

        // VCOs model iterator
        QMapIterator<int, SingleUnitLFOModel*> i(*m_mapLFOMixerModel);
        while (i.hasNext()) {
            i.next();

            // Info debug
            qDebug("Mixer::writeJSONConfig Adds Mixer ID -> %d", i.key());

            // Single VCO JSON object properties
            QJsonObject ojsVCOProps;

            // VCO Enable
            ojsVCOProps.insert("Enabled", i.value()->getTabButtonLFOSelected());
            // VCO Selector
            ojsVCOProps.insert("FreqSelector", i.value()->getFreqSelectorLFOValue());
            // VCO Frequency Coarse
            ojsVCOProps.insert("Frequency", i.value()->getPotFrequencyLFOValue());
            // VCO Frequency Fine
            ojsVCOProps.insert("FreqFine", i.value()->getPotFreqFineLFOValue());
            // VCO Duty Cycle
            ojsVCOProps.insert("DutyCycle", i.value()->getPotDutyCycleLFOValue());

            // Sub Harmonics JSON object properties
            QJsonObject ojsVCOHarmonicsProps;

            // VCO Harmonic Sine output
            ojsVCOHarmonicsProps.insert("SwitchLFOSine", i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSineSelected());
            // VCO Harmonic Square output
            ojsVCOHarmonicsProps.insert("SwitchLFOSquare", i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSquareSelected());
            // VCO Harmonic Triangle output
            ojsVCOHarmonicsProps.insert("SwitchLFOTriangle", i.value()->getHarmonicsSwitchesLFO()->getToggleSwitchLFOTriangleSelected());

            // VCO Harmonics
            ojsVCOProps.insert("HarmonicsSwitches", ojsVCOHarmonicsProps);

            // Single VCO JSON object
            QJsonObject ojsVCOObject;

            // VCO ID
            ojsVCOObject.insert("ID", (quint8)i.key());
            ojsVCOObject.insert("Values", ojsVCOProps);

            // Add to VCOs
            ojsVCOsObject.append(ojsVCOObject);
        }

        // Add to Root object
        ojsRootObject.insert("VCOs", ojsVCOsObject);
        // Add root object to JSON document
        ojsConfDoc.setObject(ojsRootObject);
        // Write to file with indentation
        fConfigJSON.write(ojsConfDoc.toJson(QJsonDocument::Indented));
        // Close file
        fConfigJSON.close();
    }
}

// Read config JSON File to model
void Mixer::readJSONConfig(const QJsonObject ojsConfRoot) {

    QJsonArray ojsVCOsObject;       // All VCO JSON object

    // If there's VCOs array
    if (ojsConfRoot.contains("VCOs") && ojsConfRoot["VCOs"].isArray()) {
        // Gets VCOs array
        ojsVCOsObject =  ojsConfRoot["VCOs"].toArray();

        // Disabled Serial Port Controller
        SerialPortController::getInstance()->setEnabled(false);

        // Cycles for VCOs array
        for (const QJsonValue &ojsVCOValue : qAsConst(ojsVCOsObject)) {

            // Single VCO JSON object
            QJsonObject ojsVCOObject = ojsVCOValue.toObject();

            // Get VCO ID
            int iVCOID = ojsVCOObject["ID"].toInt();
            // Get VCO model
            SingleUnitLFOModel* pVCOModel = m_mapLFOMixerModel->value(iVCOID);

            // Single VCO JSON object properties
            QJsonObject ojsVCOProps = ojsVCOObject["Values"].toObject();

            // VCO Enable
            pVCOModel->setTabButtonLFOSelected(ojsVCOProps["Enabled"].toBool());
            // Send signal
            emit updateVCOEnable(iVCOID, pVCOModel->getTabButtonLFOSelected());

            // VCO Selector
            pVCOModel->setFreqSelectorLFOValue(ojsVCOProps["FreqSelector"].toInt());
            // Send signal
            emit updateFreqSelector(iVCOID, pVCOModel->getFreqSelectorLFOValue());

            // VCO Frequency Coarse
            pVCOModel->setPotFrequencyLFOValue(ojsVCOProps["Frequency"].toInt());
            // Send signal
            emit updateFreqCoarse(iVCOID, pVCOModel->getPotFrequencyLFOValue());

            // VCO Frequency Fine
            pVCOModel->setPotFreqFineLFOValue(ojsVCOProps["FreqFine"].toInt());
            // Send signal
            emit updateFreqFine(iVCOID, pVCOModel->getPotFreqFineLFOValue());

            // VCO Duty Cycle
            pVCOModel->setPotDutyCycleLFOValue(ojsVCOProps["DutyCycle"].toInt());
            // Send signal
            emit updateDutyCycle(iVCOID, pVCOModel->getPotDutyCycleLFOValue());

            // Sub Harmonics JSON object properties
            QJsonObject ojsVCOHarmonicsProps = ojsVCOProps["HarmonicsSwitches"].toObject();

            // VCO Harmonic Sine output
            pVCOModel->getHarmonicsSwitchesLFO()->setToggleSwitchLFOSineSelected(ojsVCOHarmonicsProps["SwitchLFOSine"].toBool());
            // Send signal
            emit updateHarmonicsSwitches(iVCOID, Protocol::toggleSwitchSineTypeValue, pVCOModel->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSineSelected());
            // VCO Harmonic Square output
            pVCOModel->getHarmonicsSwitchesLFO()->setToggleSwitchLFOSquareSelected(ojsVCOHarmonicsProps["SwitchLFOSquare"].toBool());
            // Send signal
            emit updateHarmonicsSwitches(iVCOID, Protocol::toggleSwitchSquareTypeValue, pVCOModel->getHarmonicsSwitchesLFO()->getToggleSwitchLFOSquareSelected());
            // VCO Harmonic Triangle output
            pVCOModel->getHarmonicsSwitchesLFO()->setToggleSwitchLFOTriangleSelected(ojsVCOHarmonicsProps["SwitchLFOTriangle"].toBool());
            // Send signal
            emit updateHarmonicsSwitches(iVCOID, Protocol::toggleSwitchTriangleTypeValue, pVCOModel->getHarmonicsSwitchesLFO()->getToggleSwitchLFOTriangleSelected());

            qDebug("Mixer::readJSONConfig read Mixer ID -> %d", iVCOID);
        }

        // Enable Serial Port Controller
        SerialPortController::getInstance()->setEnabled(true);
    }
}

// Calcs and update VCOs frequencies
void Mixer::handleVCOFrequency(quint8 byID, quint16 uiValue) {

    /*
    double dTosc = (double)1 / 12000000;

    double dTcap = 0;
    double dTVCO = 0;
    double dFVCO = 0;

    SingleUnitLFOModel* pVCOModel = m_mapLFOMixerModel->value(byID);

    switch (pVCOModel->getFreqSelectorLFOValue()) {
        case FreqSelector::HVCO:

            dTcap = (double)ulValue / 16;

            break;

        case FreqSelector::VCO:

            dTcap = (double)ulValue / 4;

            break;

        case FreqSelector::LFO:

            dTcap = (double)ulValue;

            break;

        case FreqSelector::VLFO:

            dTcap = (double)ulValue;

            break;

    }

    dTVCO = dTcap * dTosc;
    dFVCO = (double)1 / dTVCO;
*/
    // Convert to string
    QString sFVCO = QString::number(uiValue, 10);

    qDebug() << "Mixer::handleVCOFrequency() VCO Freq : " << sFVCO << " Hz";

    // Post signal for update VCOs frequencies to external
    emit updateFrequencyText(byID, sFVCO);
}

// Request a current VCOs frequencies
void Mixer::requestVCOFrequency(quint8 byID) {

    qDebug("Mixer::requestVCOFrequency() VCO ID -> %d", byID);

    // Send to Serial Port the request for frequency VCO value
    SerialPortController::getInstance()->requestSendVCOFrequencyCommand(byID);

}

// When requestd all ALFONSo application is under shutdown
void Mixer::requestALFONSoUnderClosing() {

    qDebug() << "Mixer::requestALFONSoUnderClosing fired.";

    // Save model to config JSON
    writeJSONConfig(Protocol::lastConfigJSONFileValue);
}

// QML singleton type provider function (callback).
// Second, define the singleton type provider function (callback).
QObject* Mixer::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {

    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    // C++ and QML instance they are the same instance
    return Mixer::getInstance();
}
