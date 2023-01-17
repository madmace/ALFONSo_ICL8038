#include "serialPort.h"
#include "serialPortController.h"

SerialPort::SerialPort(QObject *parent) : QObject{parent}
{
    // Serial Port Name empty
    m_sSerialPortName = "";
    // Serial Port not open
    m_bSerialPortOpen = false;
}

// Get All available Serial Ports
void SerialPort::handleAvailablePortsWorker() {
    emit availablePortsWorker(QSerialPortInfo::availablePorts());
}

// Return to the USB Serial ALFONSo if is presen
QString SerialPort::getALFONSoUSB() {

    QString sSerialPortName = "";

    // Get All available Serial Ports
    const QList<QSerialPortInfo> lSerialPortsInfo = QSerialPortInfo::availablePorts();
    // Cycles list
    for (const QSerialPortInfo &info : lSerialPortsInfo) {

        // Check if same description
        //if (info.description() == SerialPortController::usbALFONSoDesc) {
            // Check if VendorIdentifier and ProductIdentifier
            if (info.hasVendorIdentifier() && info.hasProductIdentifier()) {
                // Check if same IDs
                if ((info.vendorIdentifier() == SerialPortController::usbALFONSoVendID) && (info.productIdentifier() == SerialPortController::usbALFONSoProdID)) {
                    // Found
                    sSerialPortName = info.portName();
                }
            }
        //}
    }

    return sSerialPortName;
}

// Return to the USB Serial ALFONSo if is present
void SerialPort::handleIsALFONSoUSBPresentWorker() {

    bool bFound = false;

    // Find ALFONSo USB Serial port
    QString sSerialPortName = getALFONSoUSB();
    // Control if found
    if (!sSerialPortName.isEmpty()) {

        // Create Serial Port object
        if (m_oSerial == nullptr) m_oSerial = new QSerialPort();
        // Set ALFONSo Serial Port found
        m_oSerial->setPortName(sSerialPortName);

        // Set Serial Settings
        m_oSerial->setBaudRate(SerialPortController::usbALFONSoBaudRate);
        m_oSerial->setDataBits(SerialPortController::usbALFONSoDataBits);
        m_oSerial->setParity(SerialPortController::usbALFONSoParity);
        m_oSerial->setStopBits(SerialPortController::usbALFONSoStopBits);
        m_oSerial->setFlowControl(SerialPortController::usbALFONSoFlowControl);
        // Private connections
        connect(m_oSerial, SIGNAL(readyRead()), this, SLOT(handleReceiveBytesWorker()));

        // Try to open
        if (m_oSerial->open(QIODevice::ReadWrite)) {

            // Save Serial Port Name
            m_sSerialPortName = sSerialPortName;
            // Serial Port open
            m_bSerialPortOpen = true;
            // Found
            bFound = true;

            qDebug() << "ALFONSo USB Serial Port " << m_oSerial->portName() << " open.";

        } else {

            // Open failed
            qDebug() << "Can't open port " << m_oSerial->portName() << ", Error Code " << m_oSerial->error();

        }
    }

    emit isALFONSoUSBPresentWorker(bFound);
}

// Perform all Serial Port operation for close ALFONSo
void SerialPort::handleALFONSoUnderClosingWorker() {

    // Control if Serial Port open
    if (m_bSerialPortOpen && m_oSerial->isOpen()) {
        // Close port
        m_oSerial->close();
        // Reset flag
        m_bSerialPortOpen = false;
        // Serial Port Name empty
        m_sSerialPortName = "";

        qDebug() << "ALFONSo USB Serial Port closed.";
    }
}

// Send data to serial port
void SerialPort::handleSendBytesWorker(const QByteArray &data) {

    // Control if Serial Port open
    if (m_bSerialPortOpen && m_oSerial->isOpen()) {
        // Send to serial port
        m_oSerial->write(data);
    }
}

// Receive data from serial port
void SerialPort::handleReceiveBytesWorker() {

    QByteArray data;                    // Received buffer

    // Control if Serial Port open
    if (m_bSerialPortOpen && m_oSerial->isOpen()) {
        // Receive serial port
        data.append(m_oSerial->readAll());

        emit receivedBytesWorker(data);
    }
}
