#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editdialog.h"
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client(Client::getInstance()) {
    ui->setupUi(this);

    employeesLayout = ui->employeesLayout;

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::on_editButton_clicked);
    connect(ui->getByIdButton, &QPushButton::clicked, this, &MainWindow::on_getByIdButton_clicked);
    connect(ui->getAllButton, &QPushButton::clicked, this, &MainWindow::on_getAllButton_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_deleteButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addButton_clicked() {
    Employee newEmployee;
    EditDialog dialog(newEmployee, this);

    if (dialog.exec() == QDialog::Accepted) {
        if (client->createEmployee(dialog.getEmployee())) {
            QMessageBox::information(this, "Успех", "Сотрудник успешно создан");
            refreshEmployeeList();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось создать сотрудника");
        }
    }
}

void MainWindow::on_editButton_clicked() {
    QString idText = ui->idInput->text();
    bool ok;
    unsigned id = idText.toUInt(&ok);

    if (ok) {
        Employee employee = client->getEmployee(id);
        if (employee.getId() != 0) {
            EditDialog dialog(employee, this);
            if (dialog.exec() == QDialog::Accepted) {
                if (client->updateEmployee(dialog.getEmployee())) {
                    QMessageBox::information(this, "Успех", "Данные сотрудника обновлены");
                    refreshEmployeeList();
                } else {
                    QMessageBox::warning(this, "Ошибка", "Не удалось обновить данные");
                }
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Сотрудник не найден");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Некорректный ID");
    }
}

void MainWindow::on_getByIdButton_clicked() {
    QString idText = ui->idInput->text();
    bool ok;
    unsigned id = idText.toUInt(&ok);

    if (ok) {
        clearEmployees();
        Employee employee = client->getEmployee(id);
        if (employee.getId() != 0) {
            displayEmployee(employee);
        } else {
            QMessageBox::warning(this, "Ошибка", "Сотрудник не найден");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Некорректный ID");
    }
}

void MainWindow::on_getAllButton_clicked() {
    refreshEmployeeList();
}

void MainWindow::on_deleteButton_clicked() {
    QString idText = ui->idInput->text();
    bool ok;
    unsigned id = idText.toUInt(&ok);

    if (ok) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Подтверждение",
            "Вы уверены, что хотите удалить сотрудника?",
            QMessageBox::Yes | QMessageBox::No
            );

        if (reply == QMessageBox::Yes) {
            if (client->deleteEmployee(id)) {
                QMessageBox::information(this, "Успех", "Сотрудник успешно удален");
                refreshEmployeeList();
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить сотрудника");
            }
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Некорректный ID");
    }
}

void MainWindow::clearEmployees() {
    QLayoutItem *item;
    while ((item = employeesLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::displayEmployee(const Employee &employee) {
    QWidget *widget = new QWidget();
    widget->setStyleSheet("border: none; margin: 10px;");

    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);

    auto createLabel = [](const QString &text) {
        QLabel *label = new QLabel(text);
        label->setWordWrap(true);
        label->setStyleSheet("font-family: monospace; font-size: 14px;");
        return label;
    };

    QString hireDate = employee.getHireDate().toString("yyyy-MM-dd");

    layout->addWidget(createLabel(QString("id: %1").arg(employee.getId())));
    layout->addWidget(createLabel(QString("hire_date: \"%1\"").arg(hireDate)));
    layout->addWidget(createLabel(QString("position: \"%1\"").arg(employee.getPosition())));
    layout->addWidget(createLabel(QString("department: \"%1\"").arg(employee.getDepartment())));
    layout->addWidget(createLabel(QString("employee_id: \"%1\"").arg(employee.getEmployeeId())));
    layout->addWidget(createLabel(QString("is_on_leave: %1").arg(employee.getIsOnLeave() ? "true" : "false")));

    employeesLayout->addWidget(widget);
}

void MainWindow::refreshEmployeeList() {
    clearEmployees();
    QList<Employee> employees = client->getEmployees();
    for (const Employee &employee : employees) {
        displayEmployee(employee);
    }
    ui->scrollArea->widget()->adjustSize();
}
