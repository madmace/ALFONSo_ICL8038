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

#include "tabButton.h"

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

    // Emit change value signal
    emit tabButtonSelectedChanged(newValue);
}

void TabButton::init()
{

}
