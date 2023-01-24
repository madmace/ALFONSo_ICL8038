#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QTimer>
#include <QIcon>

#include "protocol.h"
#include "serialPortController.h"
#include "mixer.h"
#include "potentiometer.h"
#include "toggleSwitch.h"
#include "tabButton.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("A.L.F.O.N.So Project");

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // Register singleton for constants
    qmlRegisterSingletonType(QUrl("qrc:/content/Constants.qml"), "com.alfonso.qml.constants", 1, 0, "Constants");
    // Register singleton for protocol
    qmlRegisterSingletonType<Protocol>("com.alfonso.protocol", 1, 0, "Protocol", &Protocol::qmlInstance);
    // Register controller singleton for the Serial Port
    qmlRegisterSingletonType<SerialPortController>("com.alfonso.serialportcontroller", 1, 0, "SerialPortController", &SerialPortController::qmlInstance);

    // Register QML Controls
    qmlRegisterType<Mixer> ("com.alfonso.qml.controls", 1, 0, "Mixer");
    qmlRegisterType<TabButton> ("com.alfonso.qml.controls", 1, 0, "TabButton");
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
    SerialPortController *oSerialPortController = SerialPortController::getInstance();

    // Set icon
    app.setWindowIcon(QIcon("qrc:/resources/favicon.png"));

    // Find MainWindow
    QObject* oMainWindowObj = engine.rootObjects().first();
    // Find SplashWindow
    QObject* oSplashWinObj = engine.rootObjects().first()->findChild<QObject*>("SplashWindowObject");

    QMetaObject::Connection oConnMainWindowOb = QObject::connect(oMainWindowObj, SIGNAL(underClosingALFONSo()), oSerialPortController, SLOT(requestALFONSoUnderClosing()));
    // Connect ALFONSo USB Serial control
    QMetaObject::Connection oConnSplashWinObj = QObject::connect(oSplashWinObj, SIGNAL(isALFONSoUSBPresent()), oSerialPortController, SLOT(requestIsALFONSoUSBPresent()));

    // Signal emitted at startup implementation
    //QTimer::singleShot(2000, [=]() { QObject::disconnect(oConnection); } );

    return app.exec();
}
