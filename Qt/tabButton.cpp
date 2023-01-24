#include "tabButton.h"
#include "serialPortController.h"

// Default constants Values
const int TabButton::defaultTabButtonID = 0;
const int TabButton::defaultTabButtonType = 0;
const bool TabButton::defaultTabButtonSelected = false;

TabButton::TabButton(QObject *parent) : QObject{parent}
{
    // Set dafault value
    m_tabButtonID = defaultTabButtonID;
    m_tabButtonType = defaultTabButtonType;
    m_tabButtonSelected = defaultTabButtonSelected;

    // Initialization
    init();
}

int TabButton::tabButtonID()
{
    return m_tabButtonID;
}

int TabButton::tabButtonType()
{
    return m_tabButtonType;
}

bool TabButton::tabButtonSelected()
{
    return m_tabButtonSelected;
}

void TabButton::setTabButtonID(int newValue)
{
    m_tabButtonID = newValue;
}

void TabButton::setTabButtonType(int newValue)
{
    m_tabButtonType = newValue;
}

void TabButton::setTabButtonSelected(bool newValue)
{
    m_tabButtonSelected = newValue;

    // Send to Serial Port
    SerialPortController::getInstance()->requestSendWidgetCommand((quint8)tabButtonID(), (quint8)tabButtonType(), (quint8)tabButtonSelected());

    qDebug("ID -> %d Type -> %d tabButtonSelected() -> %d", tabButtonID(), tabButtonType(), tabButtonSelected());
}

void TabButton::init()
{

}
