#include "SettingsPage.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QTabWidget>
#include <QScrollArea>
#include <QPalette>
#include <QColor>

SettingsPage::SettingsPage(SharedData* sharedData, QWidget* parent)
    : QWidget(parent), m_sharedData(sharedData)
{
    setupUI();
}

SettingsPage::~SettingsPage() {}

void SettingsPage::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // TabWidget for pages
    m_tabWidget = new QTabWidget(this);

    initGalleryPage();
    initExpandablePage();

    m_tabWidget->addTab(m_galleryPage, "图片画廊");
    m_tabWidget->addTab(m_expandablePage, "待拓展");

    mainLayout->addWidget(m_tabWidget);

    // Apply and Cancel buttons
    m_applyButton = new QPushButton("应用", this);
    m_cancelButton = new QPushButton("取消", this);

    connect(m_applyButton, &QPushButton::clicked, this, &SettingsPage::applySettings);
    connect(m_cancelButton, &QPushButton::clicked, this, &SettingsPage::cancelSettings);

    mainLayout->addWidget(m_applyButton);
    mainLayout->addWidget(m_cancelButton);
}

void SettingsPage::initGalleryPage()
{
    m_galleryPage = new QWidget(this);
    QFormLayout* formLayout = new QFormLayout(m_galleryPage);

    m_searchStrEdit = new QLineEdit(m_sharedData->searchStr().c_str(), this);
    m_backgroundColorEdit = new QLineEdit(m_sharedData->backgroundColor().c_str(), this);

    m_picWidthSpin = new QSpinBox(this);
    m_picWidthSpin->setValue(m_sharedData->picWidth());

    m_picHeightSpin = new QSpinBox(this);
    m_picHeightSpin->setValue(m_sharedData->picHeight());

    m_picGapSpin = new QSpinBox(this);
    m_picGapSpin->setValue(m_sharedData->picGap());

    m_numPerLineSpin = new QSpinBox(this);
    m_numPerLineSpin->setValue(m_sharedData->numPerLine());

    m_maxPicNumSpin = new QSpinBox(this);
    m_maxPicNumSpin->setValue(m_sharedData->maxPicNum());

    formLayout->addRow("搜索字符串", m_searchStrEdit);
    formLayout->addRow("背景颜色", m_backgroundColorEdit);
    formLayout->addRow("图片宽度", m_picWidthSpin);
    formLayout->addRow("图片高度", m_picHeightSpin);
    formLayout->addRow("图片间距", m_picGapSpin);
    formLayout->addRow("每行图片数", m_numPerLineSpin);
    formLayout->addRow("最大图片数量", m_maxPicNumSpin);

    m_galleryPage->setLayout(formLayout);
}

void SettingsPage::initExpandablePage()
{
    m_expandablePage = new QWidget(this);
    // 目前没有内容，待拓展
}

void SettingsPage::applySettings()
{
    bool settingsChanged = false;

    // Check for changes in each setting
    if (m_sharedData->searchStr() != m_searchStrEdit->text().toStdString()) {
        m_sharedData->setSearchStr(m_searchStrEdit->text().toStdString());
        settingsChanged = true;
    }
    if (m_sharedData->backgroundColor() != m_backgroundColorEdit->text().toStdString()) {
        m_sharedData->setBackgroundColor(m_backgroundColorEdit->text().toStdString());
        settingsChanged = true;
    }
    if (m_sharedData->picWidth() != m_picWidthSpin->value()) {
        m_sharedData->setPicWidth(m_picWidthSpin->value());
        settingsChanged = true;
    }
    if (m_sharedData->picHeight() != m_picHeightSpin->value()) {
        m_sharedData->setPicHeight(m_picHeightSpin->value());
        settingsChanged = true;
    }
    if (m_sharedData->picGap() != m_picGapSpin->value()) {
        m_sharedData->setPicGap(m_picGapSpin->value());
        settingsChanged = true;
    }
    if (m_sharedData->numPerLine() != m_numPerLineSpin->value()) {
        m_sharedData->setNumPerLine(m_numPerLineSpin->value());
        settingsChanged = true;
    }
    if (m_sharedData->maxPicNum() != m_maxPicNumSpin->value()) {
        m_sharedData->setMaxPicNum(m_maxPicNumSpin->value());
        settingsChanged = true;
    }

    if (settingsChanged) {
        QMessageBox::information(this, "设置已应用", "设置已成功应用！");
    }
}

void SettingsPage::cancelSettings()
{
    // Confirm cancellation if settings have been changed
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "取消", "设置已更改，确定取消吗？",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Reset to original settings or close the window
        this->close();
    }
}

void SettingsPage::toggleVisibility()
{
    if (isHidden()) {
        showNormal();
        activateWindow();
    }
    else {
        hide();
    }
}
