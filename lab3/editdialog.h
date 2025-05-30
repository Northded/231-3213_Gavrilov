#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include "employee.h"

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditDialog(Employee employee, QWidget* parent = nullptr);
    ~EditDialog();
    Employee getEmployee() const;

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::EditDialog* ui;
    Employee employee;
};

#endif // EDITDIALOG_H
