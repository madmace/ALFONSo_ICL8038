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

#include "protocol.h"

// JSON last configuration path file
const QString Protocol::lastConfigJSONFileValue = "./ALFONSo.json";

Protocol::Protocol(QObject *parent): QObject{parent}
{
}

QString Protocol::lastConfigJSONFile()
{
    return Protocol::lastConfigJSONFileValue;
}

/*****************************
 *
 * Microcode Components Types
 *
 *****************************/

int Protocol::tabButtonType()
{
    return Protocol::tabButtonTypeValue;
}

int Protocol::freqSelectorType()
{
    return Protocol::freqSelectorTypeValue;
}

int Protocol::frequencyPotType()
{
    return Protocol::frequencyPotTypeValue;
}

int Protocol::freqFinePotType()
{
    return Protocol::freqFinePotTypeValue;
}

int Protocol::dutyCyclePotType()
{
    return Protocol::dutyCyclePotTypeValue;
}

int Protocol::toggleSwitchSineType()
{
    return Protocol::toggleSwitchSineTypeValue;
}

int Protocol::toggleSwitchSquareType()
{
    return Protocol::toggleSwitchSquareTypeValue;
}

int Protocol::toggleSwitchTriangleType()
{
    return Protocol::toggleSwitchTriangleTypeValue;
}

int Protocol::syncAllVCO()
{
    return Protocol::SYNC_REQ_ALL;
}

QObject* Protocol::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine) {

    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    // C++ and QML instance they are the same instance
    return new Protocol();
}

/*****************************
 *
 * Utilites functions
 *
 ******************************/

// Append 2 bytes to QByteArray
void Protocol::append2Bytes(QByteArray& byBuffer, quint16 iValue) {

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
