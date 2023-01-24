#ifndef MIXER_H
#define MIXER_H

#include <QObject>

class Mixer : public QObject
{
    Q_OBJECT

public:

    // Constructor
    explicit Mixer(QObject *parent = nullptr);

signals:

public slots:

    // Send Request for Sync command to serial port
    void sendRequestSyncVCO(quint16 uiSyncRequest);

};

#endif // MIXER_H
