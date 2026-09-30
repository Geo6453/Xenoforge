#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QString>
#include <QMap>

class JsonManager : public QObject
{
public:
    JsonManager();
    void savePath(const QString& key, const QString& path);
    QString loadPath(const QString& key) const;

private:
    QString m_filePath;
};

#endif
