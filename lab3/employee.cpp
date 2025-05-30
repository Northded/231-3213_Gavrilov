#include "employee.h"
#include <QDebug>

Employee::Employee() : id(0), isOnLeave(false) {}

int Employee::getId() const { return id; }
QDate Employee::getHireDate() const { return hireDate; }
QString Employee::getPosition() const { return position; }
QString Employee::getDepartment() const { return department; }
QString Employee::getEmployeeId() const { return employeeId; }
bool Employee::getIsOnLeave() const { return isOnLeave; }

void Employee::setId(int newId) { id = newId; }
void Employee::setHireDate(const QDate& newHireDate) { hireDate = newHireDate; }
void Employee::setPosition(const QString& newPosition) { position = newPosition; }
void Employee::setDepartment(const QString& newDepartment) { department = newDepartment; }
void Employee::setEmployeeId(const QString& newEmployeeId) { employeeId = newEmployeeId; }
void Employee::setIsOnLeave(bool newIsOnLeave) { isOnLeave = newIsOnLeave; }

bool Employee::fromJSON(const QJsonObject& json) {
    if (json.contains("id") && json["id"].isDouble()) {
        id = json["id"].toInt();
    }

    if (json.contains("hire_date") && json["hire_date"].isString()) {
        hireDate = QDate::fromString(json["hire_date"].toString(), Qt::ISODate);
    }

    if (json.contains("position") && json["position"].isString()) {
        position = json["position"].toString();
    }

    if (json.contains("department") && json["department"].isString()) {
        department = json["department"].toString();
    }

    if (json.contains("employee_id") && json["employee_id"].isString()) {
        employeeId = json["employee_id"].toString();
    }

    if (json.contains("is_on_leave") && json["is_on_leave"].isBool()) {
        isOnLeave = json["is_on_leave"].toBool();
    }

    return true;
}

QJsonObject Employee::toJSON() const {
    QJsonObject json;
    if (id != 0) json["id"] = id;

    if (hireDate.isValid()) {
        json["hire_date"] = hireDate.toString(Qt::ISODate);
    }

    json["position"] = position;
    json["department"] = department;
    json["employee_id"] = employeeId;
    json["is_on_leave"] = isOnLeave;

    return json;
}
