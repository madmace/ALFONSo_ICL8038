#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);

private:

    // ALFONSo Serial Port Name in use
    QString m_sSerialPortName;
    // True if is port open
    bool m_bSerialPortOpen;
    // ALFONSo Serial Port
    QSerialPort* m_oSerial = nullptr;

    // Return to the USB Serial ALFONSo if is present
    QString getALFONSoUSB();

signals:

    // Signal containing available serial ports
    void availablePortsWorker(QList<QSerialPortInfo> lPorts);
    // Signal if ALFONSo device is present
    void isALFONSoUSBPresentWorker(bool bResult);
    // Signal for receive data from serial port
    void receivedBytesWorker(const QByteArray &data);

private slots:

    // Receive data from serial port
    void handleReceiveBytesWorker();

public slots:

    // Get All available Serial Ports
    void handleAvailablePortsWorker();
    // Return true if USB Serial ALFONSo is present, otherwise false
    void handleIsALFONSoUSBPresentWorker();
    // Perform all Serial Port operation for close ALFONSo
    void handleALFONSoUnderClosingWorker();

    // Send data to serial port
    void handleSendBytesWorker(const QByteArray &data);

};

#endif // SERIALPORT_H
