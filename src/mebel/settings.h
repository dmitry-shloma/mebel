#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings &getInstance(
            const QString &projectName = QString(),
            const QString &hostName = QString(),
            const QString &databaseName = QString(),
            const QString &userName = QString(),
            const QString &password = QString(),
            QObject *parent = 0) {
        static Settings settings(
                    projectName,
                    hostName,
                    databaseName,
                    userName,
                    password,
                    parent);
        return settings;
    }

    QString getProjectName() { return projectName_; }
    QString getHostName() { return hostName_; }
    QString getDatabaseName() { return databaseName_; }
    QString getUserName() { return userName_; }
    QString getPassword() { return password_; }

private:
    Settings(
            const QString &projectName,
            const QString &hostName,
            const QString &databaseName,
            const QString &userName,
            const QString &password,
            QObject *parent = 0)
        : QObject(parent),
          projectName_(projectName),
          hostName_(hostName),
          databaseName_(databaseName),
          userName_(userName),
          password_(password) {
    }
    ~Settings() {}

    Settings(Settings const&);
    Settings &operator = (Settings const&);

    QString projectName_;
    QString hostName_;
    QString databaseName_;
    QString userName_;
    QString password_;
};

#endif // SETTINGS_H
