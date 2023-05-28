/*******************************************************************************

 A.L.F.O.N.S.o.o
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

#include "freqSelector.h"

// Default constants Values
const int FreqSelector::defaultFreqSelectorID = 0;
const int FreqSelector::defaultFreqSelectorType = 0;
const int FreqSelector::defaultFreqSelectorSelectedIndex = FreqSelector::VCO;

/*****************************
 * Frequency Ranages Properties
 ******************************/

int FreqSelector::rangeHVCO()
{
    return FreqSelector::HVCO;
}

int FreqSelector::rangeVCO()
{
    return FreqSelector::VCO;
}

int FreqSelector::rangeLFO()
{
    return FreqSelector::LFO;
}

int FreqSelector::rangeVLFO()
{
    return FreqSelector::VLFO;
}

FreqSelector::FreqSelector(QObject *parent) : QObject{parent}
{
    // Set dafault value
    m_freqSelectorID = defaultFreqSelectorID;
    m_freqSelectorType = defaultFreqSelectorType;
    m_freqSelectorSelectedIndex = defaultFreqSelectorSelectedIndex;

    // Initialization
    init();
}

int FreqSelector::freqSelectorID()
{
    return m_freqSelectorID;
}

int FreqSelector::freqSelectorType()
{
    return m_freqSelectorType;
}

int FreqSelector::freqSelectorSelectedIndex()
{
    return m_freqSelectorSelectedIndex;
}

void FreqSelector::setFreqSelectorID(int newValue)
{
    m_freqSelectorID = newValue;
}

void FreqSelector::setFreqSelectorType(int newValue)
{
    m_freqSelectorType = newValue;
}

void FreqSelector::setFreqSelectorSelectedIndex(int newValue)
{
    m_freqSelectorSelectedIndex = newValue;

    // Emit change value signal
    emit freqSelectorSelectedIndexChanged(newValue);
}

void FreqSelector::init()
{

}
