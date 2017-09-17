#ifndef SQLDATABASEHELPER_H
#define SQLDATABASEHELPER_H

#include <QObject>
#include <QStringList>
#include <QSqlDatabase>

class SqlDatabaseHelper : public QObject
{
    Q_OBJECT
public:
    explicit SqlDatabaseHelper();

    void open(const QString &type, const QString &hostName,
              const QString &databaseName, const QString &userName,
              const QString &password);
    void close();

    QStringList select(const QString &tableName,
                       const QString &filter = QString());
    void insert(const QString &tableName, const QStringList &columns,
                         const QStringList &values);

private:
    QSqlDatabase db_;
    bool isOpen_;
};

#endif // SQLDATABASEHELPER_H
