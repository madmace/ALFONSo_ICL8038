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

#ifndef FREQLABEL_H
#define FREQLABEL_H

#include <QObject>

class FreqLabel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int freqLabelID READ freqLabelID WRITE setFreqLabelID NOTIFY freqLabelIDChanged)
    Q_PROPERTY(int freqLabelValue READ freqLabelValue WRITE setFreqLabelValue NOTIFY freqLabelValueChanged)

public:

    // Default constants
    static const int defaultFreqLabelID;
    static const int defaultFreqLabelValue;

    // Constructor
    explicit FreqLabel(QObject *parent = nullptr);

    // Gets Properties
    int freqLabelID();
    int freqLabelValue();

protected:

    // Initialization
    void init();

signals:
    // Properties signals
    void freqLabelIDChanged();
    void freqLabelValueChanged();

public slots:
    void setFreqLabelID(int newValue);
    void setFreqLabelValue(int newValue);

private:
    // Exposed properties
    int m_freqLabelID;
    int m_freqLabelValue;

};

#endif // FREQLABEL_H
