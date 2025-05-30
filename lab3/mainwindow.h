#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "client.h"
#include "employee.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_getByIdButton_clicked();
    void on_getAllButton_clicked();
    void on_deleteButton_clicked();
    void refreshEmployeeList();

private:
    Ui::MainWindow *ui;
    Client *client;
    QVBoxLayout *employeesLayout;

    void clearEmployees();
    void displayEmployee(const Employee &employee);
};

#endif // MAINWINDOW_H
