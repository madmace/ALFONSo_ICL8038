QT += quick serialport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        freqSelector.cpp \
        harmonicsSwitchesLFOModel.cpp \
        main.cpp \
        mixer.cpp \
        potentiometer.cpp \
        protocol.cpp \
        serialPort.cpp \
        serialPortController.cpp \
        singleUnitLFOModel.cpp \
        tabButton.cpp \
        toggleSwitch.cpp

RESOURCES += resources \
             qml.qrc
			 
RC_FILE = Alfonso_ICL8038_resource.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = qml/content

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    freqSelector.h \
    harmonicsSwitchesLFOModel.h \
    main.h \
    mixer.h \
    potentiometer.h \
    protocol.h \
    serialPort.h \
    serialPortController.h \
    singleUnitLFOModel.h \
    tabButton.h \
    toggleSwitch.h

DISTFILES += \
    content/Constants.qml \
    content/FreqSelectorButtonLFO.qml \
    content/FreqSelectorLFO.qml \
    content/PotDutyCycleLFO.qml \
    content/PotFrequencyLFO.qml \
    content/FreqLabelLFO.qml \
    content/TabButtonLFO.qml \
    content/ToggleSwitchLFO.qml \
    content/ViewPanelLFO.qml \
    content/HarmonicsSwitchesLFO.qml \
    content/SingleUnitLFO.qml \
    content/LFOMixer.qml \
    content/Splash.qml \

    main.qml
