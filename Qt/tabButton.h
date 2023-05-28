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

#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QObject>

class TabButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int tabButtonID READ tabButtonID WRITE setTabButtonID NOTIFY tabButtonIDChanged)
    Q_PROPERTY(int tabButtonType READ tabButtonType WRITE setTabButtonType NOTIFY tabButtonTypeChanged)
    Q_PROPERTY(bool tabButtonSelected READ tabButtonSelected WRITE setTabButtonSelected NOTIFY tabButtonSelectedChanged)

public:

    // Default constants
    static const int defaultTabButtonID;
    static const int defaultTabButtonType;
    static const bool defaultTabButtonSelected;

    // Constructor
    explicit TabButton(QObject *parent = nullptr);

    // Gets Properties
    int tabButtonID();
    int tabButtonType();
    bool tabButtonSelected();

protected:

    // Initialization
    void init();

signals:
    // Properties signals
    void tabButtonIDChanged();
    void tabButtonTypeChanged();
    void tabButtonSelectedChanged(bool newSelection);

public slots:
    void setTabButtonID(int newValue);
    void setTabButtonType(int newValue);
    void setTabButtonSelected(bool newValue);

private:
    // Exposed properties
    int m_tabButtonID;
    int m_tabButtonType;
    bool m_tabButtonSelected;

};

#endif // TABBUTTON_H
