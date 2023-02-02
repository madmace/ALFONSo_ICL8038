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

#include "toggleSwitch.h"

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

    // Emit change value signal
    emit toggleSwitchSelectedChanged(newValue);
}

void ToggleSwitch::init()
{

}
