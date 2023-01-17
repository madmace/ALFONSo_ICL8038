#include "toggleSwitch.h"
#include "serialPortController.h"

// Default constants Values
const int ToggleSwitch::defaultToggleSwitchID = 0;
const int ToggleSwitch::defaultToggleSwitchType = 0;
const bool ToggleSwitch::defaultToggleSwitchSelected = false;

ToggleSwitch::ToggleSwitch(QObject *parent) : QObject{parent}
{
    // Set dafault value
    m_toggleSwitchID = defaultToggleSwitchID;
    m_toggleSwitchType = defaultToggleSwitchType;
    m_toggleSwitchSelected = defaultToggleSwitchSelected;

    // Initialization
    init();
}

int ToggleSwitch::toggleSwitchID()
{
    return m_toggleSwitchID;
}

int ToggleSwitch::toggleSwitchType()
{
    return m_toggleSwitchType;
}

bool ToggleSwitch::toggleSwitchSelected()
{
    return m_toggleSwitchSelected;
}

void ToggleSwitch::setToggleSwitchID(int newValue)
{
    m_toggleSwitchID = newValue;
}

void ToggleSwitch::setToggleSwitchType(int newValue)
{
    m_toggleSwitchType = newValue;
}

void ToggleSwitch::setToggleSwitchSelected(bool newValue)
{
    m_toggleSwitchSelected = newValue;

    // Send to Serial Port
    SerialPortController::getInstance()->requestSendBytes((quint8)toggleSwitchID(), (quint8)toggleSwitchType(), (quint8)toggleSwitchSelected());

    qDebug("ID -> %d Type -> %d toggleSwitchSelected() -> %d", toggleSwitchID(), toggleSwitchType(), toggleSwitchSelected());
}

void ToggleSwitch::init()
{

}
