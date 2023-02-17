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

#ifndef FREQSELECTOR_H
#define FREQSELECTOR_H

#include <QObject>

class FreqSelector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int freqSelectorID READ freqSelectorID WRITE setFreqSelectorID NOTIFY freqSelectorIDChanged)
    Q_PROPERTY(int freqSelectorType READ freqSelectorType WRITE setFreqSelectorType NOTIFY freqSelectorTypeChanged)
    Q_PROPERTY(int freqSelectorSelectedIndex READ freqSelectorSelectedIndex WRITE setFreqSelectorSelectedIndex NOTIFY freqSelectorSelectedIndexChanged)

    /*****************************
     * Frequency Ranages Properties
     ******************************/

    Q_PROPERTY(int rangeHVCO READ rangeHVCO CONSTANT)
    Q_PROPERTY(int rangeVCO READ rangeVCO CONSTANT)
    Q_PROPERTY(int rangeLFO READ rangeLFO CONSTANT)
    Q_PROPERTY(int rangeVLFO READ rangeVLFO CONSTANT)

public:

    // Default constants
    static const int defaultFreqSelectorID;
    static const int defaultFreqSelectorType;
    static const int defaultFreqSelectorSelectedIndex;

    // Constructor
    explicit FreqSelector(QObject *parent = nullptr);

    /*****************************
     * Frequency Ranges Value
     ******************************/

    static const int HVCO = 1;          // High Frequencies range
    static const int VCO = 2;           // Normal audible Frequencies range
    static const int LFO = 3;           // Low audible Frequencies range
    static const int VLFO = 4;          // Lowest Frequencies range

    // Gets Properties Ranges
    int rangeHVCO();
    int rangeVCO();
    int rangeLFO();
    int rangeVLFO();

    // Gets Properties
    int freqSelectorID();
    int freqSelectorType();
    int freqSelectorSelectedIndex();

protected:

    // Initialization
    void init();

signals:
    // Properties signals
    void freqSelectorIDChanged();
    void freqSelectorTypeChanged();
    void freqSelectorSelectedIndexChanged(int newSelection);

public slots:
    void setFreqSelectorID(int newValue);
    void setFreqSelectorType(int newValue);
    void setFreqSelectorSelectedIndex(int newValue);

private:
    // Exposed properties
    int m_freqSelectorID;
    int m_freqSelectorType;
    int m_freqSelectorSelectedIndex;

};

#endif // FREQSELECTOR_H
