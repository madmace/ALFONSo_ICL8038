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

#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QObject>

class ToggleSwitch : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int toggleSwitchID READ toggleSwitchID WRITE setToggleSwitchID NOTIFY toggleSwitchIDChanged)
    Q_PROPERTY(int toggleSwitchType READ toggleSwitchType WRITE setToggleSwitchType NOTIFY toggleSwitchTypeChanged)
    Q_PROPERTY(bool toggleSwitchSelected READ toggleSwitchSelected WRITE setToggleSwitchSelected NOTIFY toggleSwitchSelectedChanged)

public:

    // Default constants
    static const int defaultToggleSwitchID;
    static const int defaultToggleSwitchType;
    static const bool defaultToggleSwitchSelected;

    // Constructor
    explicit ToggleSwitch(QObject *parent = nullptr);

    // Gets Properties
    int toggleSwitchID();
    int toggleSwitchType();
    bool toggleSwitchSelected();

protected:

    // Initialization
    void init();

signals:
    // Properties signals
    void toggleSwitchIDChanged();
    void toggleSwitchTypeChanged();
    void toggleSwitchSelectedChanged(bool newSelection);

public slots:
    void setToggleSwitchID(int newValue);
    void setToggleSwitchType(int newValue);
    void setToggleSwitchSelected(bool newValue);

private:
    // Exposed properties
    int m_toggleSwitchID;
    int m_toggleSwitchType;
    bool m_toggleSwitchSelected;

};

#endif // TOGGLESWITCH_H
