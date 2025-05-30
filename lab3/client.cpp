#include "client.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

Client* Client::instance = nullptr;

Client::Client(const QString& newRootUrl, QObject* parent)
    : QObject(parent), rootUrl(newRootUrl) {
    network = new QNetworkAccessManager(this);
}

Client* Client::getInstance(const QString& url) {
    if (!instance) {
        instance = new Client(url);
    }
    return instance;
}

void Client::destroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

QList<Employee> Client::getEmployees() const {
    QList<Employee> employees;
    QNetworkRequest request(QUrl(rootUrl + "employees/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = network->get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "[ERROR] Failed to fetch employees:" << reply->errorString();
        qDebug() << "Response:" << reply->readAll();
        reply->deleteLater();
        return employees;
    }

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    if (doc.isArray()) {
        for (const QJsonValue& value : doc.array()) {
            if (value.isObject()) {
                Employee employee;
                if (employee.fromJSON(value.toObject())) {
                    employees.append(employee);
                }
            }
        }
    }

    reply->deleteLater();
    return employees;
}

Employee Client::getEmployee(unsigned id) const {
    Employee employee;
    QNetworkRequest request(QUrl(rootUrl + "employees/" + QString::number(id) + "/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = network->get(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (doc.isObject()) {
            employee.fromJSON(doc.object());
        }
    } else {
        qDebug() << "[ERROR] Failed to get employee:" << reply->errorString();
        qDebug() << "Response:" << reply->readAll();
    }

    reply->deleteLater();
    return employee;
}

bool Client::createEmployee(const Employee& employee) const {
    QNetworkRequest request(QUrl(rootUrl + "employees/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json = employee.toJSON();
    json.remove("id");

    QByteArray jsonData = QJsonDocument(json).toJson();
    QNetworkReply* reply = network->post(request, jsonData);

    return handleReply(reply);
}

bool Client::updateEmployee(const Employee& employee, bool isPartial) const {
    QNetworkRequest request(QUrl(rootUrl + "employees/" + QString::number(employee.getId()) + "/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json = employee.toJSON();
    json.remove("id");

    QByteArray jsonData = QJsonDocument(json).toJson();
    QNetworkReply* reply;

    if (isPartial) {
        reply = network->sendCustomRequest(request, "PATCH", jsonData);
    } else {
        reply = network->put(request, jsonData);
    }

    return handleReply(reply);
}

bool Client::deleteEmployee(unsigned id) const {
    QNetworkRequest request(QUrl(rootUrl + "employees/" + QString::number(id) + "/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = network->deleteResource(request);
    return handleReply(reply);
}

bool Client::handleReply(QNetworkReply* reply) const {
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool success = (reply->error() == QNetworkReply::NoError);
    QByteArray response = reply->readAll();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "URL:" << reply->url().toString();
    qDebug() << "Status code:" << statusCode;
    qDebug() << "Response:" << response;

    if (!success) {
        qDebug() << "[ERROR] Request failed:" << reply->errorString();
    }

    reply->deleteLater();
    return success;
}
