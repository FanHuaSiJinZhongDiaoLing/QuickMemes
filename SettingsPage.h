#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QMessageBox>
#include <QScrollArea>
#include "SharedData.h"

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(SharedData* sharedData, QWidget* parent = nullptr);
    ~SettingsPage();

private slots:
    void applySettings();
    void cancelSettings();
    void toggleVisibility();

private:
    void setupUI();
    void initGalleryPage();
    void initExpandablePage();

    SharedData* m_sharedData;
    QLineEdit* m_searchStrEdit;
    QLineEdit* m_backgroundColorEdit;
    QSpinBox* m_picWidthSpin;
    QSpinBox* m_picHeightSpin;
    QSpinBox* m_picGapSpin;
    QSpinBox* m_numPerLineSpin;
    QSpinBox* m_maxPicNumSpin;

    QTabWidget* m_tabWidget;
    QWidget* m_galleryPage;
    QWidget* m_expandablePage;

    QPushButton* m_applyButton;
    QPushButton* m_cancelButton;
};

#endif // SETTINGSPAGE_H
