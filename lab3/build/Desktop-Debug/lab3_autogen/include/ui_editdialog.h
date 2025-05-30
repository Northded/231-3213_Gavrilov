/********************************************************************************
** Form generated from reading UI file 'editdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDIALOG_H
#define UI_EDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *positionLabel;
    QLineEdit *positionEdit;
    QLabel *departmentLabel;
    QLineEdit *departmentEdit;
    QLabel *employeeIdLabel;
    QLineEdit *employeeIdEdit;
    QLabel *hireDateLabel;
    QDateEdit *hireDateEdit;
    QLabel *isOnLeaveLabel;
    QCheckBox *isOnLeaveCheckBox;
    QHBoxLayout *buttonLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *EditDialog)
    {
        if (EditDialog->objectName().isEmpty())
            EditDialog->setObjectName("EditDialog");
        EditDialog->resize(400, 350);
        verticalLayout = new QVBoxLayout(EditDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        positionLabel = new QLabel(EditDialog);
        positionLabel->setObjectName("positionLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, positionLabel);

        positionEdit = new QLineEdit(EditDialog);
        positionEdit->setObjectName("positionEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, positionEdit);

        departmentLabel = new QLabel(EditDialog);
        departmentLabel->setObjectName("departmentLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, departmentLabel);

        departmentEdit = new QLineEdit(EditDialog);
        departmentEdit->setObjectName("departmentEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, departmentEdit);

        employeeIdLabel = new QLabel(EditDialog);
        employeeIdLabel->setObjectName("employeeIdLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, employeeIdLabel);

        employeeIdEdit = new QLineEdit(EditDialog);
        employeeIdEdit->setObjectName("employeeIdEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, employeeIdEdit);

        hireDateLabel = new QLabel(EditDialog);
        hireDateLabel->setObjectName("hireDateLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, hireDateLabel);

        hireDateEdit = new QDateEdit(EditDialog);
        hireDateEdit->setObjectName("hireDateEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, hireDateEdit);

        isOnLeaveLabel = new QLabel(EditDialog);
        isOnLeaveLabel->setObjectName("isOnLeaveLabel");

        formLayout->setWidget(4, QFormLayout::LabelRole, isOnLeaveLabel);

        isOnLeaveCheckBox = new QCheckBox(EditDialog);
        isOnLeaveCheckBox->setObjectName("isOnLeaveCheckBox");

        formLayout->setWidget(4, QFormLayout::FieldRole, isOnLeaveCheckBox);


        verticalLayout->addLayout(formLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        saveButton = new QPushButton(EditDialog);
        saveButton->setObjectName("saveButton");

        buttonLayout->addWidget(saveButton);

        cancelButton = new QPushButton(EditDialog);
        cancelButton->setObjectName("cancelButton");

        buttonLayout->addWidget(cancelButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(EditDialog);

        QMetaObject::connectSlotsByName(EditDialog);
    } // setupUi

    void retranslateUi(QDialog *EditDialog)
    {
        positionLabel->setText(QCoreApplication::translate("EditDialog", "\320\224\320\276\320\273\320\266\320\275\320\276\321\201\321\202\321\214:", nullptr));
        departmentLabel->setText(QCoreApplication::translate("EditDialog", "\320\236\321\202\320\264\320\265\320\273:", nullptr));
        employeeIdLabel->setText(QCoreApplication::translate("EditDialog", "ID \321\201\320\276\321\202\321\200\321\203\320\264\320\275\320\270\320\272\320\260:", nullptr));
        hireDateLabel->setText(QCoreApplication::translate("EditDialog", "\320\224\320\260\321\202\320\260 \320\277\321\200\320\270\320\265\320\274\320\260:", nullptr));
        isOnLeaveLabel->setText(QCoreApplication::translate("EditDialog", "\320\222 \320\276\321\202\320\277\321\203\321\201\320\272\320\265:", nullptr));
        saveButton->setText(QCoreApplication::translate("EditDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        cancelButton->setText(QCoreApplication::translate("EditDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        (void)EditDialog;
    } // retranslateUi

};

namespace Ui {
    class EditDialog: public Ui_EditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDIALOG_H
