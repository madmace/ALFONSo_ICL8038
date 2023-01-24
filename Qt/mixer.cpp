#include "mixer.h"
#include "serialPortController.h"

#include <QDebug>

Mixer::Mixer(QObject *parent) : QObject{parent}
{

}

// Send Request for Sync command to serial port
void Mixer::sendRequestSyncVCO(quint16 uiSyncRequest) {

    // Send to Serial Port
    SerialPortController::getInstance()->requestSendCommand(uiSyncRequest);
}
