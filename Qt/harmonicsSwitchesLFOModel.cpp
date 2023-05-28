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

#include "harmonicsSwitchesLFOModel.h"

// Constructor
HarmonicsSwitchesLFO::HarmonicsSwitchesLFO()
{
    //Clear Properties

    setToggleSwitchLFOSineSelected(false);
    setToggleSwitchLFOSquareSelected(false);
    setToggleSwitchLFOTriangleSelected(false);
}

// Copy Constructor
HarmonicsSwitchesLFO::HarmonicsSwitchesLFO(const HarmonicsSwitchesLFO &newObj) {
    setToggleSwitchLFOSineSelected(newObj.m_toggleSwitchLFOSineSelected);
    setToggleSwitchLFOSquareSelected(newObj.m_toggleSwitchLFOSquareSelected);
    setToggleSwitchLFOTriangleSelected(newObj.m_toggleSwitchLFOTriangleSelected);
}

// Properties

bool HarmonicsSwitchesLFO::getToggleSwitchLFOSineSelected() {
    return m_toggleSwitchLFOSineSelected;
}

bool HarmonicsSwitchesLFO::getToggleSwitchLFOSquareSelected() {
    return m_toggleSwitchLFOSquareSelected;
}
bool HarmonicsSwitchesLFO::getToggleSwitchLFOTriangleSelected() {
    return m_toggleSwitchLFOTriangleSelected;
}

void HarmonicsSwitchesLFO::setToggleSwitchLFOSineSelected(bool newValue) {
    m_toggleSwitchLFOSineSelected = newValue;
}
void HarmonicsSwitchesLFO::setToggleSwitchLFOSquareSelected(bool newValue) {
    m_toggleSwitchLFOSquareSelected = newValue;
}
void HarmonicsSwitchesLFO::setToggleSwitchLFOTriangleSelected(bool newValue) {
    m_toggleSwitchLFOTriangleSelected = newValue;
}
