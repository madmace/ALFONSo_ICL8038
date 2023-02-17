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

#include "singleUnitLFOModel.h"

// Constructor
SingleUnitLFOModel::SingleUnitLFOModel()
{
    // Create HarmonicsSwitchesLFO Model object
    m_oHarmonicsSwitchesLFO = new HarmonicsSwitchesLFO();

    //Clear Properties
    m_tabButtonLFOSelected = false;
    m_freqSelectorLFOValue = 0;
    m_potFrequencyLFOValue = 0;
    m_potDutyCycleLFOValue = 0;
}

// Properties

bool SingleUnitLFOModel::getTabButtonLFOSelected() {
    return m_tabButtonLFOSelected;
}

quint8 SingleUnitLFOModel::getFreqSelectorLFOValue() {
    return m_freqSelectorLFOValue;
}

quint8 SingleUnitLFOModel::getPotFrequencyLFOValue() {
    return m_potFrequencyLFOValue;
}

quint8 SingleUnitLFOModel::getPotDutyCycleLFOValue() {
    return m_potDutyCycleLFOValue;
}

HarmonicsSwitchesLFO* SingleUnitLFOModel::getHarmonicsSwitchesLFO() {
    return m_oHarmonicsSwitchesLFO;
}

void SingleUnitLFOModel::setTabButtonLFOSelected(bool newValue) {
    m_tabButtonLFOSelected = newValue;
}

void SingleUnitLFOModel::setFreqSelectorLFOValue(quint8 newValue) {
    m_freqSelectorLFOValue = newValue;
}

void SingleUnitLFOModel::setPotFrequencyLFOValue(quint8 newValue) {
    m_potFrequencyLFOValue = newValue;
}

void SingleUnitLFOModel::setPotDutyCycleLFOValue(quint8 newValue) {
    m_potDutyCycleLFOValue = newValue;
}

void SingleUnitLFOModel::setHarmonicsSwitchesLFO(HarmonicsSwitchesLFO *newObj) {
    m_oHarmonicsSwitchesLFO = newObj;
}
