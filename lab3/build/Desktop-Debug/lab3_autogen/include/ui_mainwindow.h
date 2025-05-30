/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *controlsLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QLineEdit *idInput;
    QPushButton *getByIdButton;
    QPushButton *getAllButton;
    QPushButton *deleteButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *employeesLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        controlsLayout = new QHBoxLayout();
        controlsLayout->setObjectName("controlsLayout");
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");

        controlsLayout->addWidget(addButton);

        editButton = new QPushButton(centralwidget);
        editButton->setObjectName("editButton");

        controlsLayout->addWidget(editButton);

        idInput = new QLineEdit(centralwidget);
        idInput->setObjectName("idInput");

        controlsLayout->addWidget(idInput);

        getByIdButton = new QPushButton(centralwidget);
        getByIdButton->setObjectName("getByIdButton");

        controlsLayout->addWidget(getByIdButton);

        getAllButton = new QPushButton(centralwidget);
        getAllButton->setObjectName("getAllButton");

        controlsLayout->addWidget(getAllButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");

        controlsLayout->addWidget(deleteButton);


        verticalLayout->addLayout(controlsLayout);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 774, 531));
        employeesLayout = new QVBoxLayout(scrollAreaWidgetContents);
        employeesLayout->setObjectName("employeesLayout");
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        addButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        idInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 ID", nullptr));
        getByIdButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \320\277\320\276 ID", nullptr));
        getAllButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\262\321\201\320\265\321\205", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
