#include "jsonmanager.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>

JsonManager::JsonManager()
{
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);
    if (!dir.exists()) dir.mkpath(".");
    m_filePath = dir.filePath("save.json");
}

void JsonManager::savePath(const QString& key, const QString& path)
{
    QFile file(m_filePath);
    QJsonObject data;

    if(file.open(QIODevice::ReadOnly))
    {
        data = QJsonDocument::fromJson(file.readAll()).object();
        file.close();
    }

    // Modify values
    data[key] = path;

    // Rewrite files
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(QJsonDocument(data).toJson());
        file.close();
    }
}

QString JsonManager::loadPath(const QString& key) const
{
    QFile file(m_filePath);
    if(!file.open(QIODevice::ReadOnly))
        return "";

    QJsonObject data = QJsonDocument::fromJson(file.readAll()).object();
    return data.value(key).toString("");
}
