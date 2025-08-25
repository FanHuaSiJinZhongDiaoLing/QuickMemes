/********************************************************************************
** Form generated from reading UI file 'QuickMemeTest001.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUICKMEMETEST001_H
#define UI_QUICKMEMETEST001_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuickMemeTest001Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QuickMemeTest001Class)
    {
        if (QuickMemeTest001Class->objectName().isEmpty())
            QuickMemeTest001Class->setObjectName("QuickMemeTest001Class");
        QuickMemeTest001Class->resize(600, 400);
        menuBar = new QMenuBar(QuickMemeTest001Class);
        menuBar->setObjectName("menuBar");
        QuickMemeTest001Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QuickMemeTest001Class);
        mainToolBar->setObjectName("mainToolBar");
        QuickMemeTest001Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QuickMemeTest001Class);
        centralWidget->setObjectName("centralWidget");
        QuickMemeTest001Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QuickMemeTest001Class);
        statusBar->setObjectName("statusBar");
        QuickMemeTest001Class->setStatusBar(statusBar);

        retranslateUi(QuickMemeTest001Class);

        QMetaObject::connectSlotsByName(QuickMemeTest001Class);
    } // setupUi

    void retranslateUi(QMainWindow *QuickMemeTest001Class)
    {
        QuickMemeTest001Class->setWindowTitle(QCoreApplication::translate("QuickMemeTest001Class", "QuickMemeTest001", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuickMemeTest001Class: public Ui_QuickMemeTest001Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUICKMEMETEST001_H
