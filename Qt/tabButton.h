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
    void tabButtonSelectedChanged();

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
