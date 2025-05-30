#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDate>
#include <QString>
#include <QJsonObject>

class Employee {
private:
    int id;
    QDate hireDate;
    QString position;
    QString department;
    QString employeeId;
    bool isOnLeave;

public:
    Employee();

    // Геттеры
    int getId() const;
    QDate getHireDate() const;
    QString getPosition() const;
    QString getDepartment() const;
    QString getEmployeeId() const;
    bool getIsOnLeave() const;

    // Сеттеры
    void setId(int newId);
    void setHireDate(const QDate& newHireDate);
    void setPosition(const QString& newPosition);
    void setDepartment(const QString& newDepartment);
    void setEmployeeId(const QString& newEmployeeId);
    void setIsOnLeave(bool newIsOnLeave);

    // JSON
    bool fromJSON(const QJsonObject& json);
    QJsonObject toJSON() const;
};

#endif // EMPLOYEE_H
