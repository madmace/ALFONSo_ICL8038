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

#include "serialPort.h"
#include "serialPortController.h"

SerialPort::SerialPort(QObject *parent) : QObject{parent}
{
    // Serial Port Name empty
    m_sSerialPortName = "";
    // Serial Port not open
    m_bSerialPortOpen = false;

    // Creates timer for check if Serial Port present
    m_oCheckSerialTimer = new QTimer(this);
    // Connects timer to check function
    connect(m_oCheckSerialTimer, SIGNAL(timeout()), this, SLOT(handleIsAvailableALFONSoUSB()));
}

bool SerialPort::isSerialPortOpen()
{
    return m_bSerialPortOpen;
}

// Get All available Serial Ports
void SerialPort::handleAvailablePortsWorker() {
    emit availablePortsWorker(QSerialPortInfo::availablePorts());
}

// Return to the USB Serial ALFONSo if is present
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

// Check if the USB Serial ALFONSo if is available
void SerialPort::handleIsAvailableALFONSoUSB() {

    // Find ALFONSo USB Serial port
    QString sSerialPortName = getALFONSoUSB();
    // Control if found
    if (sSerialPortName.isEmpty()) {

        // Acts as under shutdown
        handleALFONSoUnderClosingWorker();

        emit isALFONSoUSBPresentWorker(false);
    }
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

            // Starts timer with 5s interval
            m_oCheckSerialTimer->start(5000);

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

        // Stop timer for check if Serial Port present
        m_oCheckSerialTimer->stop();

        qDebug() << "ALFONSo USB Serial Port closed.";
    }
}

// Send data to serial port
void SerialPort::handleSendBytesWorker(const QByteArray &data) {

    // Control if Serial Port open
    if (m_bSerialPortOpen && m_oSerial->isOpen()) {
        // Send to serial port
        m_oSerial->write(data);
        m_oSerial->flush();
    }
}

// Receive data from serial port
void SerialPort::handleReceiveBytesWorker() {

    QByteArray data;                    // Received buffer

    // Control if Serial Port open
    if (m_bSerialPortOpen && m_oSerial->isOpen()) {
        // Receive serial port
        data.append(m_oSerial->readAll());
        // Controls if not empty
        if (!data.isEmpty()) {
            emit receivedBytesWorker(data);
        }
    }
}
