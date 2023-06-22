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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QtCore>
#include <QQmlEngine>

class Protocol : public QObject
{
    Q_OBJECT

    /*****************************
     *
     * Constants JSON last configuration path file
     *
     ******************************/

    Q_PROPERTY(QString lastConfigJSONFile READ lastConfigJSONFile CONSTANT)

    /*************************************************
     *
     * A.L.F.O.N.S.oo
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
    Q_PROPERTY(int freqSelectorType READ freqSelectorType CONSTANT)
    Q_PROPERTY(int frequencyPotType READ frequencyPotType CONSTANT)
    Q_PROPERTY(int freqFinePotType READ freqFinePotType CONSTANT)
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

    // Constructor
    explicit Protocol(QObject *parent = nullptr);

    // QML singleton type provider function (callback).
    // Second, define the singleton type provider function (callback).
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    // Gets Properties
    QString lastConfigJSONFile();

    int tabButtonType();
    int freqSelectorType();
    int frequencyPotType();
    int freqFinePotType();
    int dutyCyclePotType();
    int toggleSwitchSineType();
    int toggleSwitchSquareType();
    int toggleSwitchTriangleType();

    int syncAllVCO();

    /*****************************
     *
     * JSON last configuration path file
     *
     ******************************/

    static const QString lastConfigJSONFileValue;

    /*****************************
     *
     * Microcode Components Types
     *
     ******************************/

    static const int tabButtonTypeValue = 1;                // Main Tab Enabler VCO/LFO
    static const int freqSelectorTypeValue = 2;             // Frequency Range selector VCO/LFO
    static const int frequencyPotTypeValue = 3;             // Frequency Coarse Potentiometer VCO/LFO
    static const int freqFinePotTypeValue = 4;              // Frequency Fine Potentiometer VCO/LFO
    static const int dutyCyclePotTypeValue = 5;             // Duty Cycle Potentiometer VCO/LFO
    static const int toggleSwitchSineTypeValue = 6;         // Switch Sine VCO/LFO Signal
    static const int toggleSwitchSquareTypeValue = 7;       // Switch Square VCO/LFO Signal
    static const int toggleSwitchTriangleTypeValue = 8;     // Switch Triangle VCO/LFO Signal

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

    // Resquest for set VCO 1 frequency Range
    static const quint16 VCO_1_REQ_FREQ_SELECTOR = 0x0010;
    // Resquest for set VCO 2 frequency Range
    static const quint16 VCO_2_REQ_FREQ_SELECTOR = 0x0011;
    // Resquest for set VCO 3 frequency Range
    static const quint16 VCO_3_REQ_FREQ_SELECTOR = 0x0012;
    // Resquest for set VCO 4 frequency Range
    static const quint16 VCO_4_REQ_FREQ_SELECTOR = 0x0013;

    // Resquest for set VCO 1 coarse frequency
    static const quint16 VCO_1_REQ_FREQCOARSE = 0x0020;
    // Resquest for set VCO 2 coarse frequency
    static const quint16 VCO_2_REQ_FREQCOARSE = 0x0021;
    // Resquest for set VCO 3 coarse frequency
    static const quint16 VCO_3_REQ_FREQCOARSE = 0x0022;
    // Resquest for set VCO 4 coarse frequency
    static const quint16 VCO_4_REQ_FREQCOARSE = 0x0023;

    // Resquest for set VCO 1 fine frequency
    static const quint16 VCO_1_REQ_FREQFINE = 0x0030;
    // Resquest for set VCO 2 fine frequency
    static const quint16 VCO_2_REQ_FREQFINE = 0x0031;
    // Resquest for set VCO 3 fine frequency
    static const quint16 VCO_3_REQ_FREQFINE = 0x0032;
    // Resquest for set VCO 4 fine frequency
    static const quint16 VCO_4_REQ_FREQFINE = 0x0033;

    // Resquest for set VCO 1 Duty cycle
    static const quint16 VCO_1_REQ_DUTY_CYCLE = 0x0040;
    // Resquest for set VCO 2 Duty cycle
    static const quint16 VCO_2_REQ_DUTY_CYCLE = 0x0041;
    // Resquest for set VCO 3 Duty cycle
    static const quint16 VCO_3_REQ_DUTY_CYCLE = 0x0042;
    // Resquest for set VCO 4 Duty cycle
    static const quint16 VCO_4_REQ_DUTY_CYCLE = 0x0043;

    // Resquest for enable VCO 1 Sine line
    static const quint16 VCO_1_REQ_ENABLE_SINE = 0x0050;
    // Resquest for enable VCO 2 Sine line
    static const quint16 VCO_2_REQ_ENABLE_SINE = 0x0051;
    // Resquest for enable VCO 3 Sine line
    static const quint16 VCO_3_REQ_ENABLE_SINE = 0x0052;
    // Resquest for enable VCO 4 Sine line
    static const quint16 VCO_4_REQ_ENABLE_SINE = 0x0053;

    // Resquest for enable VCO 1 Square line
    static const quint16 VCO_1_REQ_ENABLE_SQUARE = 0x0060;
    // Resquest for enable VCO 2 Square line
    static const quint16 VCO_2_REQ_ENABLE_SQUARE = 0x0061;
    // Resquest for enable VCO 3 Square line
    static const quint16 VCO_3_REQ_ENABLE_SQUARE = 0x0062;
    // Resquest for enable VCO 4 Square line
    static const quint16 VCO_4_REQ_ENABLE_SQUARE = 0x0063;

    // Resquest for enable VCO 1 Triangle line
    static const quint16 VCO_1_REQ_ENABLE_TRIANGLE = 0x0070;
    // Resquest for enable VCO 2 Triangle line
    static const quint16 VCO_2_REQ_ENABLE_TRIANGLE = 0x0071;
    // Resquest for enable VCO 3 Triangle line
    static const quint16 VCO_3_REQ_ENABLE_TRIANGLE = 0x0072;
    // Resquest for enable VCO 4 Triangle line
    static const quint16 VCO_4_REQ_ENABLE_TRIANGLE = 0x0073;

    /*****************************
     *
     * Commands for only get states of VCO/Mixers by client.
     *
     ******************************/

    // Request for get current frequency on VCO 1
    static const quint16 VCO_1_REQ_FREQUENCY = 0x0100;
    // Request for get current frequency on VCO 2
    static const quint16 VCO_2_REQ_FREQUENCY = 0x0101;
    // Request for get current frequency on VCO 3
    static const quint16 VCO_3_REQ_FREQUENCY = 0x0102;
    // Request for get current frequency on VCO 4
    static const quint16 VCO_4_REQ_FREQUENCY = 0x0103;

    /*****************************
     *
     * States Response to client.
     *
     ******************************/

    // Response for VCO 1 frequency
    static const quint16 VCO_1_RSP_FREQUENCY = 0x1000;
    // Response for VCO 2 frequency
    static const quint16 VCO_2_RSP_FREQUENCY = 0x1001;
    // Response for VCO 3 frequency
    static const quint16 VCO_3_RSP_FREQUENCY = 0x1002;
    // Response for VCO 4 frequency
    static const quint16 VCO_4_RSP_FREQUENCY = 0x1003;

    /*****************************
     *
     * Utilites functions
     *
     ******************************/

    // Append 2 bytes to QByteArray
    static void append2Bytes(QByteArray& byBuffer, quint16 iValue);

};

#endif // PROTOCOL_H
