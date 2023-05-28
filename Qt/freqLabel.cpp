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

#include "freqLabel.h"

// Default constants Values
const int FreqLabel::defaultFreqLabelID = 0;
const int FreqLabel::defaultFreqLabelValue = 0;

FreqLabel::FreqLabel(QObject *parent) : QObject{parent}
{
    // Set dafault value
    m_freqLabelID = defaultFreqLabelID;
    m_freqLabelValue = defaultFreqLabelValue;

    // Initialization
    init();
}

int FreqLabel::freqLabelID()
{
    return m_freqLabelID;
}

int FreqLabel::freqLabelValue()
{
    return m_freqLabelValue;
}

void FreqLabel::setFreqLabelID(int newValue)
{
    m_freqLabelID = newValue;
}

void FreqLabel::setFreqLabelValue(int newValue)
{
    m_freqLabelValue = newValue;
}

void FreqLabel::init()
{

}
