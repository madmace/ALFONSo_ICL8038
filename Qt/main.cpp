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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QTimer>
#include <QIcon>

#include "main.h"
#include "protocol.h"
#include "serialPortController.h"
#include "mixer.h"
#include "potentiometer.h"
#include "toggleSwitch.h"
#include "tabButton.h"
#include "freqLabel.h"
#include "freqSelector.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(PROJECT_NAME);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // Register singleton for Constants
    qmlRegisterSingletonType(QUrl("qrc:/content/Constants.qml"), "com.alfonso.qml.constants", 1, 0, "Constants");
    // Register singleton for Protocol
    qmlRegisterSingletonType<Protocol>("com.alfonso.protocol", 1, 0, "Protocol", Protocol::qmlInstance);
    // Register singleton for Mixer
    qmlRegisterSingletonType<Mixer>("com.alfonso.mixer", 1, 0, "Mixer", Mixer::qmlInstance);
    // Register controller singleton for the Serial Port
    qmlRegisterSingletonType<SerialPortController>("com.alfonso.serialportcontroller", 1, 0, "SerialPortController", SerialPortController::qmlInstance);

    // Register QML Controls
    qmlRegisterType<TabButton> ("com.alfonso.qml.controls", 1, 0, "TabButton");
    qmlRegisterType<FreqLabel> ("com.alfonso.qml.controls", 1, 0, "FreqLabel");
    qmlRegisterType<FreqSelector> ("com.alfonso.qml.controls", 1, 0, "FreqSelector");
    qmlRegisterType<Potentiometer> ("com.alfonso.qml.controls", 1, 0, "Potentiometer");
    qmlRegisterType<ToggleSwitch> ("com.alfonso.qml.controls", 1, 0, "ToggleSwitch");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);

    // Adds resource path
    engine.addImportPath(QCoreApplication::applicationDirPath() + "/content");
    engine.addImportPath(":/");

    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    // Get instance in C++ of SerialPortController
    SerialPortController* oSerialPortController = SerialPortController::getInstance();
    // Get instance in C++ of Mixer
    Mixer* oMixer = Mixer::getInstance();

    // Find MainWindow
    QObject* oMainWindowObj = engine.rootObjects().first();

    // Find SplashWindow
    QObject* oSplashWinObj = engine.rootObjects().first()->findChild<QObject*>("SplashWindowObject");

    // Connect main window catch the quit for USB Serial control
    QMetaObject::Connection oConnMainWindowSerCtrl = QObject::connect(oMainWindowObj, SIGNAL(underClosingALFONSo()), oSerialPortController, SLOT(requestALFONSoUnderClosing()));
    // Connect main window catch the quit for Mixer
    QMetaObject::Connection oConnMainWindowMixer = QObject::connect(oMainWindowObj, SIGNAL(underClosingALFONSo()), oMixer, SLOT(requestALFONSoUnderClosing()));
    // Connect ALFONSo USB Serial control for search ALFONSo HW
    QMetaObject::Connection oConnSplashWinObj = QObject::connect(oSplashWinObj, SIGNAL(isALFONSoUSBPresent()), oSerialPortController, SLOT(requestIsALFONSoUSBPresent()));

    // Signal emitted at startup implementation
    //QTimer::singleShot(2000, [=]() { QObject::disconnect(oConnection); } );

    return app.exec();
}
