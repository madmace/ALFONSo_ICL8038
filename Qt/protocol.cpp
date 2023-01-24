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
