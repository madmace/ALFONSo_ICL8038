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

#include "serialPortController.h"
#include "protocol.h"

// Initialize Singleton
SerialPortController *SerialPortController::oSerialPortController = 0;

// Default constants Values
const int SerialPortController::defaultEnabled = true;

// Fake serial dongle
#ifndef __FAKE_DONGLE_USB_SERIAL__
// ALFONSo USB Serial type
const QString SerialPortController::usbALFONSoDesc = "Alfons CDC Proto 1";
const quint16 SerialPortController::usbALFONSoVendID = 1240;    // 0x04D8
const quint16 SerialPortController::usbALFONSoProdID = 10;      // 0x000A
#else
const QString SerialPortController::usbALFONSoDesc = "Silicon Labs CP210x USB to UART Bridge";
const quint16 SerialPortController::usbALFONSoVendID = 4292;    // 0x10C4
const quint16 SerialPortController::usbALFONSoProdID = 60000;   // 0xEA60
#endif

// ALFONSo USB Serial settings
const qint32 SerialPortController::usbALFONSoBaudRate = QSerialPort::Baud115200;
const QSerialPort::DataBits SerialPortController::usbALFONSoDataBits = QSerialPort::Data8;
const QSerialPort::Parity SerialPortController::usbALFONSoParity = QSerialPort::NoParity;
const QSerialPort::StopBits SerialPortController::usbALFONSoStopBits = QSerialPort::OneStop;
const QSerialPort::FlowControl SerialPortController::usbALFONSoFlowControl = QSerialPort::NoFlowControl;

// Controller Constructor
SerialPortController::SerialPortController(QObject *parent): QObject{parent}
{
    // Set dafault value
    m_enabled = defaultEnabled;

    // Create worker Serial Port
    oSerialPort = new SerialPort();
    // Create Thread
    oWorkerThread = new QThread();
    // Move Thread to Worker
    oSerialPort->moveToThread(oWorkerThread);

    // Delete connection
    connect(oWorkerThread, &QThread::finished, oSerialPort, &QObject::deleteLater);
    // Outbound connections
    connect(this, SIGNAL(availablePortsController()), oSerialPort, SLOT(handleAvailablePortsWorker()), Qt::QueuedConnection);
    connect(this, SIGNAL(isALFONSoUSBPresentController()), oSerialPort, SLOT(handleIsALFONSoUSBPresentWorker()), Qt::QueuedConnection);
    connect(this, SIGNAL(ALFONSoUnderClosing()), oSerialPort, SLOT(handleALFONSoUnderClosingWorker()), Qt::QueuedConnection);
    connect(this, SIGNAL(sendBytes(QByteArray)), oSerialPort, SLOT(handleSendBytesWorker(QByteArray)), Qt::BlockingQueuedConnection);
    // Inbound connections
    connect(oSerialPort, SIGNAL(availablePortsWorker(QList<QSerialPortInfo>)), this, SLOT(handleAvailablePorts(QList<QSerialPortInfo>)), Qt::QueuedConnection);
    connect(oSerialPort, SIGNAL(isALFONSoUSBPresentWorker(bool)), this, SLOT(handleALFONSoUSBPresent(bool)), Qt::QueuedConnection);
    connect(oSerialPort, SIGNAL(receivedBytesWorker(QByteArray)), this, SLOT(receivedBytes(QByteArray)), Qt::QueuedConnection);

    // Start Worker
    oWorkerThread->start();
}

// Controller Destructor
SerialPortController::~SerialPortController() {

    // Stop Thread
    oWorkerThread->quit();
    oWorkerThread->wait();
}

// First initialize the instance. All classes will access via this instance
SerialPortController* SerialPortController::getInstance() {
    // If already created
    if (!oSerialPortController) {
        // Makes Singleton
        oSerialPortController = new SerialPortController();
    }
    return oSerialPortController;
}

// Sets/Gets Properties
bool SerialPortController::enabled()
{
    return m_enabled;
}

void SerialPortController::setEnabled(bool newValue)
{
    m_enabled = newValue;
}

// Get available serial ports
void SerialPortController::requestAvailablePorts() {

    qDebug() << "SerialPortController::requestAvailablePorts() fired.";

    // Post message to perform slot on worker
    emit availablePortsController();

}
// Get state if ALFONSo device is present
void SerialPortController::requestIsALFONSoUSBPresent() {

    qDebug() << "SerialPortController::requestIsALFONSoUSBPresent() fired.";

    // Post message to perform slot on worker
    emit isALFONSoUSBPresentController();

}

// Request for send Raw Data to serial port
void SerialPortController::requestSendRawData(const QByteArray &data) {

    qDebug() << "SerialPortController::requestSendRawData() fired.";

    // If serial port controller is enable
    if (this->enabled()) {
        // If serial port is open
        if (oSerialPort->isSerialPortOpen()) {
            // Send bytes to worker
            emit sendBytes(data);
        }
    }
}

// Request for send Widget command to serial port
void SerialPortController::requestSendWidgetCommand(quint8 byID, quint8 byType, quint8 byValue) {

    QByteArray byBuffer;

    switch (byType) {
        case Protocol::tabButtonTypeValue:

            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_ENABLE);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_ENABLE);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_ENABLE);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_ENABLE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::freqSelectorTypeValue:
            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_FREQ_SELECTOR);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_FREQ_SELECTOR);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_FREQ_SELECTOR);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_FREQ_SELECTOR);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::frequencyPotTypeValue:

            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_FREQCOARSE);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_FREQCOARSE);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_FREQCOARSE);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_FREQCOARSE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::freqFinePotTypeValue:

            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_FREQFINE);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_FREQFINE);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_FREQFINE);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_FREQFINE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::dutyCyclePotTypeValue:

            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_DUTY_CYCLE);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_DUTY_CYCLE);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_DUTY_CYCLE);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_DUTY_CYCLE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::toggleSwitchSineTypeValue:

            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_ENABLE_SINE);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_ENABLE_SINE);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_ENABLE_SINE);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_ENABLE_SINE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::toggleSwitchSquareTypeValue:

            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_ENABLE_SQUARE);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_ENABLE_SQUARE);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_ENABLE_SQUARE);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_ENABLE_SQUARE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::toggleSwitchTriangleTypeValue:

            switch (byID) {
                case 1:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_ENABLE_TRIANGLE);
                    break;
                case 2:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_ENABLE_TRIANGLE);
                    break;
                case 3:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_ENABLE_TRIANGLE);
                    break;
                case 4:
                    Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_ENABLE_TRIANGLE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

    }

    // Controls correct bytes size
    if (byBuffer.length() == Protocol::REQUEST_SIZE) {

        qDebug("SerialPortController::requestSendWidgetCommand ID -> %d Type -> %d Value() -> %d", byID, byType, byValue);

        // Send Raw Data to serial port
        requestSendRawData(byBuffer);
    }
}

// Request for send command request VCOs frequencies to serial port
void SerialPortController::requestSendVCOFrequencyCommand(quint8 byID) {

    QByteArray byBuffer;

    switch (byID) {
        case 1:
            Protocol::append2Bytes(byBuffer, Protocol::VCO_1_REQ_FREQUENCY);
            break;
        case 2:
            Protocol::append2Bytes(byBuffer, Protocol::VCO_2_REQ_FREQUENCY);
            break;
        case 3:
            Protocol::append2Bytes(byBuffer, Protocol::VCO_3_REQ_FREQUENCY);
            break;
        case 4:
            Protocol::append2Bytes(byBuffer, Protocol::VCO_4_REQ_FREQUENCY);
            break;
    }

    // Adds byte value
    byBuffer.append(byID);

    // Controls correct bytes size
    if (byBuffer.length() == Protocol::REQUEST_SIZE) {

        qDebug("SerialPortController::requestSendVCOFrequencyCommand ID -> %d", byID);

        // Send Raw Data to serial port
        requestSendRawData(byBuffer);
    }
}


// When requestd all ALFONSo application is under shutdown
void SerialPortController::requestALFONSoUnderClosing() {

    qDebug() << "SerialPortController::requestALFONSoUnderClosing fired.";

    // Post message to perform slot on worker
    emit ALFONSoUnderClosing();
}

// Get available serial ports
void SerialPortController::handleAvailablePorts(QList<QSerialPortInfo> lPorts) {

}

// Get state if ALFONSo device is present
void SerialPortController::handleALFONSoUSBPresent(bool bResult) {

    qDebug() << "SerialPortController::handleALFONSoUSBPresent() fired. Found : " << bResult;

    // Post message to external
    emit isALFONSoUSBPresent(bResult);
}

void SerialPortController::UnpackFrequency16(const QByteArray &data, quint16 &uiIDCommand, quint16 &uiValue) {

    // Reading 2 byte command
    uiIDCommand = (quint8)data[1] << 8;
    uiIDCommand += (quint8)data[0];
    // Reading 2 byte value
    uiValue = (quint8)data[3] << 8;
    uiValue += (quint8)data[2];
}

void SerialPortController::UnpackFrequency32(const QByteArray &data, quint16 &uiIDCommand, quint32 &ulValue) {

    quint16 uiLowValue = 0;             // Response value low 16bit part
    quint16 uiHighValue = 0;            // Response value high 16bit part

    // Reading 2 byte command
    uiIDCommand = (quint8)data[1] << 8;
    uiIDCommand += (quint8)data[0];
    // Reading 2 byte value low part
    uiLowValue = (quint8)data[3] << 8;
    uiLowValue += (quint8)data[2];
    // Reading 2 byte value High part
    uiHighValue = (quint8)data[5] << 8;
    uiHighValue += (quint8)data[4];
    // Adds to 4 bytes word
    ulValue = (quint16)uiHighValue << 16;
    ulValue += (quint16)uiLowValue;
}

// Signal for receive data from serial port
void SerialPortController::receivedBytes(const QByteArray &data) {

    quint16 uiIDCommand = 0;            // Response command
    quint16 uiValue = 0;                // Response value 16bit

    // Unpack command and data
    UnpackFrequency16(data, uiIDCommand, uiValue);

    // By command received
    switch (uiIDCommand) {
        case  Protocol::VCO_1_RSP_FREQUENCY:
        {
            qDebug() << "SerialPortController::receivedBytes() fired. VCO_1_RSP_FREQUENCY : " << uiValue;

            // Post signal for update VCOs frequencies to external
            emit receivedVCOFrequency(1, uiValue);

            break;
        }
        case Protocol::VCO_2_RSP_FREQUENCY:

            qDebug() << "SerialPortController::receivedBytes() fired. VCO_2_RSP_FREQUENCY : " << uiValue;

            // Post signal for update VCOs frequencies to external
            emit receivedVCOFrequency(2, uiValue);

            break;

        case Protocol::VCO_3_RSP_FREQUENCY:

            qDebug() << "SerialPortController::receivedBytes() fired. VCO_3_RSP_FREQUENCY : " << uiValue;

            // Post signal for update VCOs frequencies to external
            emit receivedVCOFrequency(3, uiValue);

            break;

        case Protocol::VCO_4_RSP_FREQUENCY:

            qDebug() << "SerialPortController::receivedBytes() fired. VCO_4_RSP_FREQUENCY : " << uiValue;

            // Post signal for update VCOs frequencies to external
            emit receivedVCOFrequency(4, uiValue);

            break;
    }
}

// QML singleton type provider function (callback).
// Second, define the singleton type provider function (callback).
QObject* SerialPortController::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {

    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    // C++ and QML instance they are the same instance
    return SerialPortController::getInstance();
}

