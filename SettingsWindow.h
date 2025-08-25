#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include "SettingsPage.h"

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindow(SharedData* sharedData, QWidget* parent = nullptr);
    ~SettingsWindow();

private:
    SettingsPage* m_settingsPage;
};

#endif // SETTINGSWINDOW_H
