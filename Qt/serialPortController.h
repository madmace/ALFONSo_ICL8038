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

#ifndef SERIALPORTCONTROLLER_H
#define SERIALPORTCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QQmlEngine>
#include <QSerialPortInfo>

#include "serialPort.h"

class SerialPortController : public QObject
{
    Q_OBJECT

private:

    // Singleton static instance
    static SerialPortController *oSerialPortController;

    // Working Thread
    QThread *oWorkerThread = 0;

    // Worker Serial Port
    SerialPort *oSerialPort = 0;

    // Controller Constructor
    explicit SerialPortController(QObject *parent = nullptr);
    // Controller Destructor
    ~SerialPortController();

public:

    // ALFONSo USB Serial type
    static const QString usbALFONSoDesc;
    static const quint16 usbALFONSoVendID;
    static const quint16 usbALFONSoProdID;

    // ALFONSo USB Serial settings
    static const qint32 usbALFONSoBaudRate;
    static const QSerialPort::DataBits usbALFONSoDataBits;
    static const QSerialPort::Parity usbALFONSoParity;
    static const QSerialPort::StopBits usbALFONSoStopBits;
    static const QSerialPort::FlowControl usbALFONSoFlowControl;

    // First initialize the instance. All classes will access via this instance
    static SerialPortController* getInstance();

    // QML singleton type provider function (callback).
    // Second, define the singleton type provider function (callback).
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

signals:

    /*******************************
     *
     * Signal for external handler
     *
     ******************************/

    // Signal containing available serial ports
    void availablePorts(QList<QSerialPortInfo> lPorts);
    // Signal if ALFONSo device is present
    void isALFONSoUSBPresent(bool bResult);

    // Signal for update botton panel info text
    void updateBottomInfoText(QString sInfoText);
    // Signal for update VCOs frequencies
    void receivedVCOFrequency(quint8 byID, quint16 uiValue);

    /*******************************
     *
     * Signal for SerialPort Worker
     *
     ******************************/

    // Signal containing available serial ports
    void availablePortsController();
    // Signal if ALFONSo device is present
    void isALFONSoUSBPresentController();
    // Signal send when ALFONSo is under shutdown
    void ALFONSoUnderClosing();

    // Signal for send data to serial port
    void sendBytes(const QByteArray &data);

public slots:

    /*******************************
     *
     * Slots for external request
     *
     ******************************/

    // Get available serial ports
    void requestAvailablePorts();
    // Get state if ALFONSo device is present
    void requestIsALFONSoUSBPresent();
    // When requestd all ALFONSo application is under shutdown
    void requestALFONSoUnderClosing();

    // Request for send Raw Data to serial port
    void requestSendRawData(const QByteArray &data);

    // Request for send widget command to serial port
    void requestSendWidgetCommand(quint8 byID, quint8 byType, quint8 byValue);


    /*******************************
     *
     * Slots from SerialPort Worker
     *
     ******************************/

    // Get available serial ports
    void handleAvailablePorts(QList<QSerialPortInfo> lPorts);
    // Get state if ALFONSo device is present
    void handleALFONSoUSBPresent(bool bResult);
    // Signal for receive data from serial port
    void receivedBytes(const QByteArray &data);
};

#endif // SERIALPORTCONTROLLER_H
