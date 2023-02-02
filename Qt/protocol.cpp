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

#include "protocol.h"

Protocol::Protocol(QObject *parent): QObject{parent}
{
}

int Protocol::tabButtonType()
{
    return Protocol::tabButtonTypeValue;
}

int Protocol::frequencyPotType()
{
    return Protocol::frequencyPotTypeValue;
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
