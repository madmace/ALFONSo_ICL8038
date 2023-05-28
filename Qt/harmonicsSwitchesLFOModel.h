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

#ifndef HARMONICSSWITCHESLFOMODEL_H
#define HARMONICSSWITCHESLFOMODEL_H

class HarmonicsSwitchesLFO
{

public:

    // Constructor
    HarmonicsSwitchesLFO();

    // Copy Constructor
    HarmonicsSwitchesLFO(const HarmonicsSwitchesLFO &newObj);

    // Properties
    bool getToggleSwitchLFOSineSelected();
    bool getToggleSwitchLFOSquareSelected();
    bool getToggleSwitchLFOTriangleSelected();

    void setToggleSwitchLFOSineSelected(bool newValue);
    void setToggleSwitchLFOSquareSelected(bool newValue);
    void setToggleSwitchLFOTriangleSelected(bool newValue);

private:
    bool m_toggleSwitchLFOSineSelected;
    bool m_toggleSwitchLFOSquareSelected;
    bool m_toggleSwitchLFOTriangleSelected;

};

#endif // HARMONICSSWITCHESLFOMODEL_H
