/********************************************************************************
** Form generated from reading UI file 'Test.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TestClass)
    {
        if (TestClass->objectName().isEmpty())
            TestClass->setObjectName(QString::fromUtf8("TestClass"));
        TestClass->resize(600, 400);
        menuBar = new QMenuBar(TestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TestClass->setStatusBar(statusBar);

        retranslateUi(TestClass);

        QMetaObject::connectSlotsByName(TestClass);
    } // setupUi

    void retranslateUi(QMainWindow *TestClass)
    {
        TestClass->setWindowTitle(QCoreApplication::translate("TestClass", "Test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestClass: public Ui_TestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
