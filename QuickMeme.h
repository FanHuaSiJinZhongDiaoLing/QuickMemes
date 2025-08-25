#ifndef QUICKMEME_H
#define QUICKMEME_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QApplication>
#include <QCloseEvent>
#include <QIcon>

#include "ImageGallery.h"

class SettingsWindow; // 前向声明

class QuickMeme : public QMainWindow
{
    Q_OBJECT

public:
    QuickMeme(QWidget* parent = nullptr);
    ~QuickMeme();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void SetUI(); // 新增 UI 设置函数
    void createActions();
    void createTrayIcon();

    QWidget* topWidget;
    QScrollArea* scrollArea;
    ImageGallery* imageGallery;
    QSystemTrayIcon* trayIcon;
    QMenu* trayMenu;
    QAction* showAction;
    QAction* quitAction;
    QAction* settingAction;
    SettingsWindow* settingsWindow;

private slots:
    void toggleVisibility();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // QUICKMEME_H