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

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <QObject>

class Potentiometer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int potID READ potID WRITE setPotID NOTIFY potIDChanged)
    Q_PROPERTY(int potType READ potType WRITE setPotType NOTIFY potTypeChanged)
    Q_PROPERTY(int potWidth READ potWidth WRITE setPotWidth NOTIFY potWidthChanged)
    Q_PROPERTY(int potHeight READ potHeight WRITE setPotHeight NOTIFY potHeightChanged)
    Q_PROPERTY(int potMinRange READ potMinRange WRITE setPotMinRange NOTIFY potMinRangeChanged)
    Q_PROPERTY(int potMaxRange READ potMaxRange WRITE setPotMaxRange NOTIFY potMaxRangeChanged)
    Q_PROPERTY(int potSpreadAngle READ potSpreadAngle WRITE setPotSpreadAngle NOTIFY potSpreadAngleChanged)
    Q_PROPERTY(int potValue READ potValue WRITE setPotValue NOTIFY potValueChanged)

public:

    // Default constants
    static const int defaultPotID;
    static const int defaultPotType;
    static const int defaultPotWidth;
    static const int defaultPotHeight;
    static const int defaultPotValue;
    static const int defaultPotMinRange;
    static const int defaultPotMaxRange;
    static const int defaultPotSpreadAngle;

    // Constructor
    explicit Potentiometer(QObject *parent = nullptr);

    // Gets Properties
    int potID();
    int potType();
    int potWidth();
    int potHeight();
    int potMinRange();
    int potMaxRange();
    int potSpreadAngle();
    int potValue();

protected:

    // Initialization
    void init();

signals:
    // Properties signals
    void potIDChanged();
    void potTypeChanged();
    void potWidthChanged();
    void potHeightChanged();
    void potMinRangeChanged();
    void potMaxRangeChanged();
    void potSpreadAngleChanged();
    void potValueChanged(int newValue);

    // Pot movie signals
    void potClockWise(qreal iDeg);
    void potCouterClockWise(qreal iDeg);


public slots:

    // Sets Properties
    void setPotID(int newValue);
    void setPotType(int newValue);
    void setPotWidth(int newValue);
    void setPotHeight(int newValue);
    void setPotMinRange(int newValue);
    void setPotMaxRange(int newValue);
    void setPotSpreadAngle(int newValue);
    void setPotValue(int newValue);

    void toAngle(qreal x, qreal y);
    void fromValue(int newValue);

private:
    // Exposed properties
    int m_potID;
    int m_potType;
    int m_potWidth;
    int m_potHeight;
    int m_potMinRange;
    int m_potMaxRange;
    int m_potSpreadAngle;
    int m_potValue;

    // Internal properties
    int m_potRange;
    int potRange();
    void setPotRange(int newValue);

    // Currents Angles
    qreal m_potAngle90;
    qreal m_potAngle315;

    // Steps value to 90° angle
    qreal m_potStepTo90;
    // Degrees for single step
    qreal m_degreesSingleStep;

};

#endif // POTENTIOMETER_H
