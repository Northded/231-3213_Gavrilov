#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(Employee employee, QWidget* parent)
    : QDialog(parent), ui(new Ui::EditDialog), employee(employee) {
    ui->setupUi(this);

    ui->positionEdit->setText(employee.getPosition());
    ui->departmentEdit->setText(employee.getDepartment());
    ui->employeeIdEdit->setText(employee.getEmployeeId());
    ui->hireDateEdit->setDate(employee.getHireDate());
    ui->isOnLeaveCheckBox->setChecked(employee.getIsOnLeave());

    connect(ui->saveButton, &QPushButton::clicked, this, &EditDialog::on_saveButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &EditDialog::on_cancelButton_clicked);
}

EditDialog::~EditDialog() {
    delete ui;
}

Employee EditDialog::getEmployee() const {
    Employee updated = employee;
    updated.setPosition(ui->positionEdit->text());
    updated.setDepartment(ui->departmentEdit->text());
    updated.setEmployeeId(ui->employeeIdEdit->text());
    updated.setHireDate(ui->hireDateEdit->date());
    updated.setIsOnLeave(ui->isOnLeaveCheckBox->isChecked());
    return updated;
}

void EditDialog::on_saveButton_clicked() {
    accept();
}

void EditDialog::on_cancelButton_clicked() {
    reject();
}
