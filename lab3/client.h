#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QList>
#include "employee.h"

class Client : public QObject {
    Q_OBJECT
private:
    static Client* instance;
    QNetworkAccessManager* network;
    QString rootUrl;

    explicit Client(const QString& rootUrl, QObject* parent = nullptr);

public:
    static Client* getInstance(const QString& url = "http://localhost:8080/api/");
    static void destroyInstance();

    Employee getEmployee(unsigned id) const;
    QList<Employee> getEmployees() const;
    bool createEmployee(const Employee& employee) const;
    bool updateEmployee(const Employee& employee, bool isPartial = false) const;
    bool deleteEmployee(unsigned id) const;

private:
    bool handleReply(QNetworkReply* reply) const;
};

#endif // CLIENT_H
