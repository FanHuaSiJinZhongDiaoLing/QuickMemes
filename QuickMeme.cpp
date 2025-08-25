#include "QuickMeme.h"
#include "SharedData.h"
#include "SettingsWindow.h"

QuickMeme::QuickMeme(QWidget* parent)
    : QMainWindow(parent)
{
    // 使用 SharedData 单例
    SharedData* sharedData = SharedData::getInstance();
    settingsWindow = new SettingsWindow(sharedData, this); // 设置窗口，使用单例指针

    // 主窗口基本设置
    setWindowTitle("Quick Memes");
    resize(800, 600);
    hide();  // 默认隐藏主窗口
    setAttribute(Qt::WA_Hover, true);  // 使控件接收鼠标悬浮事件

    // 设置 UI
    SetUI();

    // 加载示例图片
    imageGallery->reloadImages("D:\\2025");

    // 创建系统托盘组件
    createActions();
    createTrayIcon();

    // 连接 SettingsWindow 的显示动作
    connect(settingAction, &QAction::triggered, settingsWindow, &SettingsWindow::show);
}

QuickMeme::~QuickMeme()
{
    delete trayIcon;
    delete trayMenu;
}

void QuickMeme::SetUI()
{
    // 创建主布局
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 上部25%紫色区域
    topWidget = new QWidget(this);
    topWidget->setFixedHeight(height() * 0.25);  // 初始设置为25%
    topWidget->setStyleSheet("background-color: purple;");
    mainLayout->addWidget(topWidget, 0);  // stretch factor设为0

    // 下部75%图片区域
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 设置滚动条样式（使其悬浮）
    scrollArea->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: rgba(0, 0, 0, 50);"
        "    width: 10px;"
        "    margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgba(255, 255, 255, 150);"
        "    min-height: 20px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}"
    );


    // 创建并设置 ImageGallery
    imageGallery = new ImageGallery(this);
    scrollArea->setWidget(imageGallery);
    mainLayout->addWidget(scrollArea, 75);  // stretch factor设为75

    // 设置中心部件
    setCentralWidget(centralWidget);
}

void QuickMeme::createActions()
{
    showAction = new QAction("显示主界面", this);
    quitAction = new QAction("退出程序", this);
    settingAction = new QAction("设置结果", this);

    connect(showAction, &QAction::triggered, this, &QuickMeme::toggleVisibility);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
}

void QuickMeme::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayMenu = new QMenu(this);

    // 设置托盘图标（确保有图标资源）
    trayIcon->setIcon(QIcon(":/QuickMemeTest001/static/icon/user.jpg"));
    trayIcon->setToolTip("Quick Memes");

    // 构建菜单
    trayMenu->addAction(showAction);
    trayMenu->addAction(settingAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    // 设置上下文菜单
    trayIcon->setContextMenu(trayMenu);

    // 连接托盘图标激活信号
    connect(trayIcon, &QSystemTrayIcon::activated,
        this, &QuickMeme::onTrayIconActivated);

    trayIcon->show();
}

void QuickMeme::closeEvent(QCloseEvent* event)
{
    hide();         // 隐藏窗口
    event->ignore(); // 阻止真正关闭
}

void QuickMeme::toggleVisibility()
{
    if (isHidden()) {
        showNormal();
        activateWindow();
    }
    else {
        hide();
    }
}

void QuickMeme::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger) {
        toggleVisibility();
    }
}