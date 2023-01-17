#include "serialPortController.h"
#include "protocol.h"

// Initialize Singleton
SerialPortController *SerialPortController::oSerialPortController = 0;

// ALFONSo USB Serial type
const QString SerialPortController::usbALFONSoDesc = "Alfons CDC Proto 1";
const quint16 SerialPortController::usbALFONSoVendID = 1240;    // 0x04D8
const quint16 SerialPortController::usbALFONSoProdID = 10;      // 0x000A

//const QString SerialPortController::usbALFONSoDesc = "Silicon Labs CP210x USB to UART Bridge";
//const quint16 SerialPortController::usbALFONSoVendID = 4292;    // 0x10C4
//const quint16 SerialPortController::usbALFONSoProdID = 60000;   // 0xEA60

// ALFONSo USB Serial settings
const qint32 SerialPortController::usbALFONSoBaudRate = QSerialPort::Baud115200;
const QSerialPort::DataBits SerialPortController::usbALFONSoDataBits = QSerialPort::Data8;
const QSerialPort::Parity SerialPortController::usbALFONSoParity = QSerialPort::NoParity;
const QSerialPort::StopBits SerialPortController::usbALFONSoStopBits = QSerialPort::OneStop;
const QSerialPort::FlowControl SerialPortController::usbALFONSoFlowControl = QSerialPort::NoFlowControl;

// Controller Constructor
SerialPortController::SerialPortController(QObject *parent): QObject{parent}
{
    // Create worker Serial Port
    oSerialPort = new SerialPort();
    // Create Thread
    oWorkerThread = new QThread();
    // Move Thread to Worker
    oSerialPort->moveToThread(oWorkerThread);

    // Delete connection
    connect(oWorkerThread, &QThread::finished, oSerialPort, &QObject::deleteLater);
    // Inbound connections
    connect(this, SIGNAL(availablePortsController()), oSerialPort, SLOT(handleAvailablePortsWorker()));
    connect(this, SIGNAL(isALFONSoUSBPresentController()), oSerialPort, SLOT(handleIsALFONSoUSBPresentWorker()));
    connect(this, SIGNAL(ALFONSoUnderClosing()), oSerialPort, SLOT(handleALFONSoUnderClosingWorker()));
    connect(this, SIGNAL(sendBytes(QByteArray)), oSerialPort, SLOT(handleSendBytesWorker(QByteArray)));
    // Outbound connections
    connect(oSerialPort, SIGNAL(availablePortsWorker(QList<QSerialPortInfo>)), this, SLOT(handleAvailablePorts(QList<QSerialPortInfo>)));
    connect(oSerialPort, SIGNAL(isALFONSoUSBPresentWorker(bool)), this, SLOT(handleALFONSoUSBPresent(bool)));
    connect(oSerialPort, SIGNAL(receivedBytesWorker(QByteArray)), this, SLOT(receivedBytes(QByteArray)));

    // Signal for receive data from serial port
    //void ;

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

// Request for send bytes to serial port
void SerialPortController::requestSendBytes(quint8 byID, quint8 byType, quint8 byValue) {


    QByteArray byBuffer;

    switch (byType) {
        case Protocol::tabButtonTypeValue:

            switch (byID) {
                case 1:
                    append2Bytes(byBuffer, Protocol::VCO_1_ENABLE);
                    break;
                case 2:
                    append2Bytes(byBuffer, Protocol::VCO_2_ENABLE);
                    break;
                case 3:
                    append2Bytes(byBuffer, Protocol::VCO_3_ENABLE);
                    break;
                case 4:
                    append2Bytes(byBuffer, Protocol::VCO_4_ENABLE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::frequencyPotTypeValue:

            switch (byID) {
                case 1:
                    append2Bytes(byBuffer, Protocol::VCO_1_FREQUENCY);
                    break;
                case 2:
                    append2Bytes(byBuffer, Protocol::VCO_2_FREQUENCY);
                    break;
                case 3:
                    append2Bytes(byBuffer, Protocol::VCO_3_FREQUENCY);
                    break;
                case 4:
                    append2Bytes(byBuffer, Protocol::VCO_4_FREQUENCY);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::dutyCyclePotTypeValue:

            switch (byID) {
                case 1:
                    append2Bytes(byBuffer, Protocol::VCO_1_DUTY_CYCLE);
                    break;
                case 2:
                    append2Bytes(byBuffer, Protocol::VCO_2_DUTY_CYCLE);
                    break;
                case 3:
                    append2Bytes(byBuffer, Protocol::VCO_3_DUTY_CYCLE);
                    break;
                case 4:
                    append2Bytes(byBuffer, Protocol::VCO_4_DUTY_CYCLE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::toggleSwitchSineTypeValue:

            switch (byID) {
                case 1:
                    append2Bytes(byBuffer, Protocol::VCO_1_ENABLE_SINE);
                    break;
                case 2:
                    append2Bytes(byBuffer, Protocol::VCO_2_ENABLE_SINE);
                    break;
                case 3:
                    append2Bytes(byBuffer, Protocol::VCO_3_ENABLE_SINE);
                    break;
                case 4:
                    append2Bytes(byBuffer, Protocol::VCO_4_ENABLE_SINE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::toggleSwitchSquareTypeValue:

            switch (byID) {
                case 1:
                    append2Bytes(byBuffer, Protocol::VCO_1_ENABLE_SQUARE);
                    break;
                case 2:
                    append2Bytes(byBuffer, Protocol::VCO_2_ENABLE_SQUARE);
                    break;
                case 3:
                    append2Bytes(byBuffer, Protocol::VCO_3_ENABLE_SQUARE);
                    break;
                case 4:
                    append2Bytes(byBuffer, Protocol::VCO_4_ENABLE_SQUARE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

        case Protocol::toggleSwitchTriangleTypeValue:

            switch (byID) {
                case 1:
                    append2Bytes(byBuffer, Protocol::VCO_1_ENABLE_TRIANGLE);
                    break;
                case 2:
                    append2Bytes(byBuffer, Protocol::VCO_2_ENABLE_TRIANGLE);
                    break;
                case 3:
                    append2Bytes(byBuffer, Protocol::VCO_3_ENABLE_TRIANGLE);
                    break;
                case 4:
                    append2Bytes(byBuffer, Protocol::VCO_4_ENABLE_TRIANGLE);
                    break;
            }

            // Adds byte value
            byBuffer.append(byValue);

            break;

    }

    if (byBuffer.length() == Protocol::REQUEST_SIZE) {
        emit sendBytes(byBuffer);
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

// Signal for receive data from serial port
void SerialPortController::receivedBytes(const QByteArray &data) {

    qDebug() << "SerialPortController::receivedBytes() fired. Inbound data : " << data;
}

QObject* SerialPortController::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {

    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    // C++ and QML instance they are the same instance
    return SerialPortController::getInstance();
}

// Append 2 bytes to QByteArray
void SerialPortController::append2Bytes(QByteArray& byBuffer, quint16 iValue) {

    quint8 byLowByte = 0;
    quint8 byHighByte = 0;

    // Take low part
    byLowByte = iValue & 0x00FF;
    // Take high part
    byHighByte = iValue >> 8;

    // First Low byte
    byBuffer.append(byLowByte);
    // Second High byte
    byBuffer.append(byHighByte);

}
