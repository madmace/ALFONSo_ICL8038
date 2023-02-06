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

#ifndef SINGLEUNITLFOMODEL_H
#define SINGLEUNITLFOMODEL_H

#include "harmonicsSwitchesLFOModel.h"
#include "qglobal.h"

class SingleUnitLFOModel
{
public:

    // Constructor
    SingleUnitLFOModel();

    // Properties

    bool getTabButtonLFOSelected();
    quint8 getPotFrequencyLFOValue();
    quint8 getPotDutyCycleLFOValue();
    HarmonicsSwitchesLFO* getHarmonicsSwitchesLFO();

    void setTabButtonLFOSelected(bool newValue);
    void setPotFrequencyLFOValue(quint8 newValue);
    void setPotDutyCycleLFOValue(quint8 newValue);
    void setHarmonicsSwitchesLFO(HarmonicsSwitchesLFO *newObj);

private:

    bool m_tabButtonLFOSelected;
    quint8 m_potFrequencyLFOValue;
    quint8 m_potDutyCycleLFOValue;
    HarmonicsSwitchesLFO* m_oHarmonicsSwitchesLFO;

};

#endif // SINGLEUNITLFOMODEL_H
