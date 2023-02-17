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

#ifndef MIXER_H
#define MIXER_H

#include <QObject>
#include <QQmlEngine>
#include "singleUnitLFOModel.h"

class Mixer : public QObject
{
    Q_OBJECT

private:

    // Singleton static instance
    static Mixer *oMixer;

    // Main Mixer Data Model
    QHash<int, SingleUnitLFOModel*> *m_hsLFOMixerModel;

    // Constructor
    explicit Mixer(QObject *parent = nullptr);
    // Mixer Destructor
    ~Mixer();

    // Save data into the model
    void updateMixerModel(quint8 byID, quint8 byType, quint8 byValue);

public:

    // First initialize the instance. All classes will access via this instance
    static Mixer* getInstance();

    // Properties
    QHash<int, SingleUnitLFOModel*>* getLFOMixerModel();

    // QML singleton type provider function (callback).
    // Second, define the singleton type provider function (callback).
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

signals:

    // Signal for update botton panel info text
    void updateBottomInfoText(QString sInfoText);

public slots:

    // Store the status of the single control
    void setMixerValue(int iID, int iType, int iValue);

    // Send Request for Sync All command to serial port
    void sendRequestSyncAllVCO();


};

#endif // MIXER_H
