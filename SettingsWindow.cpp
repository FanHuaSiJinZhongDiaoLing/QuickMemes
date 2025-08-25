#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(SharedData* sharedData, QWidget* parent)
    : QMainWindow(parent)
{
    // Create SettingsPage and set it as central widget
    m_settingsPage = new SettingsPage(sharedData, this);
    setCentralWidget(m_settingsPage);

    // Set window title
    setWindowTitle("设置");

    // Optionally: Adjust window size, min/max, etc.
    setFixedSize(800, 600);  // Example size
}

SettingsWindow::~SettingsWindow() {}
