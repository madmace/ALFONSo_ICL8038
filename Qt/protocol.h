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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QtCore>
#include <QQmlEngine>

class Protocol : public QObject
{
    Q_OBJECT

    /*************************************************
    *
    * A.L.F.O.N.So
    *
    * Microcode constants type protocol
    * ID    -> VCO/LFO Channel
    * Type  -> Component type
    *
    *************************************************/

    /*****************************
     *
     * Microcode Components Types Properties
     *
     ******************************/

    Q_PROPERTY(int tabButtonType READ tabButtonType CONSTANT)
    Q_PROPERTY(int frequencyPotType READ frequencyPotType CONSTANT)
    Q_PROPERTY(int dutyCyclePotType READ dutyCyclePotType CONSTANT)
    Q_PROPERTY(int toggleSwitchSineType READ toggleSwitchSineType CONSTANT)
    Q_PROPERTY(int toggleSwitchSquareType READ toggleSwitchSquareType CONSTANT)
    Q_PROPERTY(int toggleSwitchTriangleType READ toggleSwitchTriangleType CONSTANT)

    /*****************************
     *
     * Microcode Absolute Command Properties
     *
     ******************************/

    Q_PROPERTY(int syncAllVCO READ syncAllVCO CONSTANT)

public:

    explicit Protocol(QObject *parent = nullptr);

    // QML singleton type provider function (callback).
    // Second, define the singleton type provider function (callback).
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    // Gets Properties
    int tabButtonType();
    int frequencyPotType();
    int dutyCyclePotType();
    int toggleSwitchSineType();
    int toggleSwitchSquareType();
    int toggleSwitchTriangleType();

    int syncAllVCO();

    /*****************************
     *
     * Microcode Components Types
     *
     ******************************/

    static const int tabButtonTypeValue = 1;                // Main Tab Enabler VCO/LFO
    static const int frequencyPotTypeValue = 2;             // Frequency Potentiometer VCO/LFO
    static const int dutyCyclePotTypeValue = 3;             // Duty Cycle Potentiometer VCO/LFO
    static const int toggleSwitchSineTypeValue = 4;         // Switch Sine VCO/LFO Signal
    static const int toggleSwitchSquareTypeValue = 5;       // Switch Square VCO/LFO Signal
    static const int toggleSwitchTriangleTypeValue = 6;     // Switch Triangle VCO/LFO Signal

    /*****************************
     *
     * Commands for request states of VCO/Mixers from client.
     *
     ******************************/

    // Fixed size for command
    static const quint16 REQUEST_SIZE = 3;

    // Resquest all ALFONSo State
    static const quint16 SYNC_REQ_ALL = 0xFFFF;

    // Resquest VCO 1 State
    static const quint16 SYNC_REQ_VCO_1 = 0xFFE0;
    // Resquest VCO 2 State
    static const quint16 SYNC_REQ_VCO_2 = 0xFFE1;
    // Resquest VCO 3 State
    static const quint16 SYNC_REQ_VCO_3 = 0xFFE2;
    // Resquest VCO 4 State
    static const quint16 SYNC_REQ_VCO_4 = 0xFFE3;

    /*****************************
     *
     * Commands for sets VCO/Mixers by client.
     *
     ******************************/

    // Resquest for enable/disable VCO 1
    static const quint16 VCO_1_REQ_ENABLE = 0x0001;
    // Resquest for enable/disable VCO 2
    static const quint16 VCO_2_REQ_ENABLE = 0x0002;
    // Resquest for enable/disable VCO 3
    static const quint16 VCO_3_REQ_ENABLE = 0x0003;
    // Resquest for enable/disable VCO 4
    static const quint16 VCO_4_REQ_ENABLE = 0x0004;

    // Resquest for set VCO 1 frequency
    static const quint16 VCO_1_REQ_FREQUENCY = 0x0010;
    // Resquest for set VCO 2 frequency
    static const quint16 VCO_2_REQ_FREQUENCY = 0x0011;
    // Resquest for set VCO 3 frequency
    static const quint16 VCO_3_REQ_FREQUENCY = 0x0012;
    // Resquest for set VCO 4 frequency
    static const quint16 VCO_4_REQ_FREQUENCY = 0x0013;

    // Resquest for set VCO 1 Duty cycle
    static const quint16 VCO_1_REQ_DUTY_CYCLE = 0x0020;
    // Resquest for set VCO 2 Duty cycle
    static const quint16 VCO_2_REQ_DUTY_CYCLE = 0x0021;
    // Resquest for set VCO 3 Duty cycle
    static const quint16 VCO_3_REQ_DUTY_CYCLE = 0x0022;
    // Resquest for set VCO 4 Duty cycle
    static const quint16 VCO_4_REQ_DUTY_CYCLE = 0x0023;

    // Resquest for enable VCO 1 Sine line
    static const quint16 VCO_1_REQ_ENABLE_SINE = 0x0030;
    // Resquest for enable VCO 2 Sine line
    static const quint16 VCO_2_REQ_ENABLE_SINE = 0x0031;
    // Resquest for enable VCO 3 Sine line
    static const quint16 VCO_3_REQ_ENABLE_SINE = 0x0032;
    // Resquest for enable VCO 4 Sine line
    static const quint16 VCO_4_REQ_ENABLE_SINE = 0x0033;

    // Resquest for enable VCO 1 Square line
    static const quint16 VCO_1_REQ_ENABLE_SQUARE = 0x0040;
    // Resquest for enable VCO 2 Square line
    static const quint16 VCO_2_REQ_ENABLE_SQUARE = 0x0041;
    // Resquest for enable VCO 3 Square line
    static const quint16 VCO_3_REQ_ENABLE_SQUARE = 0x0042;
    // Resquest for enable VCO 4 Square line
    static const quint16 VCO_4_REQ_ENABLE_SQUARE = 0x0043;

    // Resquest for enable VCO 1 Triangle line
    static const quint16 VCO_1_REQ_ENABLE_TRIANGLE = 0x0050;
    // Resquest for enable VCO 2 Triangle line
    static const quint16 VCO_2_REQ_ENABLE_TRIANGLE = 0x0051;
    // Resquest for enable VCO 3 Triangle line
    static const quint16 VCO_3_REQ_ENABLE_TRIANGLE = 0x0052;
    // Resquest for enable VCO 4 Triangle line
    static const quint16 VCO_4_REQ_ENABLE_TRIANGLE = 0x0053;

    /*****************************
     *
     * States Response to client.
     *
     ******************************/

    // Response for VCO 1 frequency
    static const quint16 VCO_1_RSP_FREQUENCY = 0x1001;
    // Response for VCO 2 frequency
    static const quint16 VCO_2_RSP_FREQUENCY = 0x1002;
    // Response for VCO 3 frequency
    static const quint16 VCO_3_RSP_FREQUENCY = 0x1003;
    // Response for VCO 4 frequency
    static const quint16 VCO_4_RSP_FREQUENCY = 0x1004;

    /*****************************
     *
     * Structure for Synchronize an Single VCO
     *
     ******************************/

    struct SyncVCOStruct
    {
        bool bTabButtonLFOSelected;
        quint8 uiPotFrequencyLFOValue;
        quint8 uiPotDutyCycleLFOValue;
        bool bToggleSwitchLFOSineSelected;
        bool bToggleSwitchLFOSquareSelected;
        bool bToggleSwitchLFOTriangleSelected;
    };

    /*****************************
     *
     * Utilites functions
     *
     ******************************/

    // Append 2 bytes to QByteArray
    static void append2Bytes(QByteArray& byBuffer, quint16 iValue);

};

#endif // PROTOCOL_H
