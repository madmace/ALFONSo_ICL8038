#include "potentiometer.h"
#include "serialPortController.h"
#include <QtMath>
#include <QLineF>

#include <QDebug>

// Default constants Values
const int Potentiometer::defaultPotID = 0;
const int Potentiometer::defaultPotType = 0;
const int Potentiometer::defaultPotWidth = 100;
const int Potentiometer::defaultPotHeight = 100;
const int Potentiometer::defaultPotValue = 0;
const int Potentiometer::defaultPotMinRange = 0;
const int Potentiometer::defaultPotMaxRange = 255;
const int Potentiometer::defaultPotSpreadAngle = 360;

Potentiometer::Potentiometer(QObject *parent) : QObject{parent}
{
    // Set dafault value
    m_potID = defaultPotID;
    m_potType = defaultPotType;
    m_potWidth = defaultPotWidth;
    m_potHeight = defaultPotHeight;
    m_potValue = defaultPotValue;
    m_potMinRange = defaultPotMinRange;
    m_potMaxRange = defaultPotMaxRange;
    m_potSpreadAngle = defaultPotSpreadAngle;

    // Initialization
    init();
}

int Potentiometer::potID()
{
    return m_potID;
}

int Potentiometer::potType()
{
    return m_potType;
}

int Potentiometer::potWidth()
{
    return m_potWidth;
}

int Potentiometer::potHeight()
{
    return m_potHeight;
}

int Potentiometer::potRange()
{
    return m_potRange;
}

int Potentiometer::potMinRange()
{
    return m_potMinRange;
}

int Potentiometer::potMaxRange()
{
    return m_potMaxRange;
}

int Potentiometer::potSpreadAngle()
{
    return m_potSpreadAngle;
}

int Potentiometer::potValue()
{
    return m_potValue;
}

void Potentiometer::setPotID(int newValue)
{
    m_potID = newValue;
}

void Potentiometer::setPotType(int newValue)
{
    m_potType = newValue;
}

void Potentiometer::setPotWidth(int newValue)
{
    m_potWidth = newValue;
}

void Potentiometer::setPotHeight(int newValue)
{
    m_potHeight = newValue;
}

void Potentiometer::setPotRange(int newValue)
{
    m_potRange = newValue;
}

void Potentiometer::setPotMinRange(int newValue)
{
    m_potMinRange = newValue;
    // Set Range
    setPotRange(potMaxRange() - m_potMinRange);
}

void Potentiometer::setPotMaxRange(int newValue)
{
    m_potMaxRange = newValue;
    // Set Range
    setPotRange(m_potMaxRange - potMinRange());
}

void Potentiometer::setPotSpreadAngle(int newValue)
{
    if (newValue >= 0 && newValue <= 360)
    {
        m_potSpreadAngle = newValue;
    }
}

void Potentiometer::setPotValue(int newValue)
{
    m_potValue = newValue;
}

void Potentiometer::init()
{
    // Initial Angles
    m_potAngle90 = 0;
    m_potAngle315 = 0;

    // Set Range
    setPotRange(m_potMaxRange - m_potMinRange);

    // Calcs pot value relative to new minimum
    setPotValue(potValue() - potMinRange());
}

void Potentiometer::toAngle(qreal x, qreal y)
{
    // Create a line from center to 90° degrees
    QLineF refLine90(potWidth() / 2, potHeight() / 2, potWidth() / 2, 0);
    // Create a line from center to 315° degrees
    QLineF refLine315(potWidth() / 2, potHeight() / 2, potWidth(), potHeight());

    // Create a line from center to the target point
    QLineF tagLine(potWidth() / 2, potHeight() / 2, x, y);

    // Calcs angle relative to 90° degrees
    qreal newAngle90 = tagLine.angleTo(refLine90);
    // Calcs angle relative to 315° degrees
    qreal newAngle315 = tagLine.angleTo(refLine315);

    // Calcs degrees for single step
    m_degreesSingleStep = qreal(potSpreadAngle()) / potRange();

    // Calcs values in range steps to 90°
    m_potStepTo90 = newAngle90 * (potRange() / qreal(potSpreadAngle()));

    // Direction Vector
    // 1 Clockwise
    // -1 CounterClockWise
    // 0 None
    int v = 0;

    // Control if in same position or initial position
    if (m_potAngle90 != newAngle90 && m_potAngle315 != newAngle315)
    {
        // Control if there is in lower half circle
        if (newAngle90 > 90.0 && newAngle90 < 270.0)
        {
            // If clockwise
            if (m_potAngle90 < newAngle90)
                v = 1;

            // If counterclockwise
            if (m_potAngle90 > newAngle90 )
                v = -1;
        }
        else
        {
            // Upper half circle

            // If clockwise
            if (m_potAngle315 < newAngle315)
                v = 1;

            // If counterclockwise
            if (m_potAngle315 > newAngle315)
                v = -1;
        }

        // Controls if there's in range
        if ((potValue() + v) <= potMaxRange() && (potValue() + v) >= potMinRange())
        {
            // Valid and add step
            setPotValue(potValue() + v);

            // CouterClockWise
            if (v == -1)
                emit potCouterClockWise(m_degreesSingleStep);
            // ClockWise
            if (v == 1)
                emit potClockWise(m_degreesSingleStep);

            // Send to Serial Port
            SerialPortController::getInstance()->requestSendBytes((quint8)potID(), (quint8)potType(), (quint8)potValue());

            qDebug("ID -> %d Type -> %d potValue() -> %d", potID(), potType(), potValue());
        }
    }

    // Save angles
    m_potAngle90 = newAngle90;
    m_potAngle315 = newAngle315;
}
