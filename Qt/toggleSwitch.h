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
    void toggleSwitchSelectedChanged();

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
