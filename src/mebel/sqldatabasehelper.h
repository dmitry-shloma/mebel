#ifndef SQLDATABASEHELPER_H
#define SQLDATABASEHELPER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class SqlDatabaseHelper : public QObject
{
    Q_OBJECT
public:
    static SqlDatabaseHelper &getInstance(
            const QString &type = QString(),
            const QString &hostName = QString(),
            const QString &databaseName = QString(),
            const QString &userName = QString(),
            const QString &password = QString(),
            QObject *parent = 0) {
        static SqlDatabaseHelper sqlDatabaseHelper(
                    type,
                    hostName,
                    databaseName,
                    userName,
                    password,
                    parent);
            return sqlDatabaseHelper;
    }

    QList<QStringList> select(
            const QString &tableName,
            const QStringList &columnList = QStringList("*"),
            const QString &filter = QString()) {

            if (!isOpen_) {
                return QList<QStringList>();
            }

            QString columnListWithCommas = columnList.join(",");
            // TODO: пробелы перед ";"
            QSqlQuery query(QString("SELECT %0 FROM %1 %2;")
                            .arg(columnListWithCommas)
                            .arg(tableName)
                            .arg(filter), db_);
            int columnCount = query.record().count();

            QList<QStringList> tableValues;
            QStringList rowValues;
            while (query.next()) {
                for (int i = 0; i < columnCount; ++i) {
                    rowValues << query.value(i).toString();
                }
                tableValues << rowValues;
                rowValues.clear();
            }
            return tableValues;
    }

    quint32 insert(
            const QString &tableName,
            const QStringList &columns,
            const QStringList &values) {
        if (!isOpen_) {
            return 0;
        }

        QString columnsWithCommas = columns.join(",");
        QString valuesWithCommas = values.join(",");
        QSqlQuery query(QString("INSERT INTO %0 (%1) VALUES (%2);")
                        .arg(tableName)
                        .arg(columnsWithCommas)
                        .arg(valuesWithCommas), db_);
        if (query.lastError().type() != QSqlError::NoError) {
            qDebug() << "text" << query.lastError().text();
            qDebug() << "databaseText" << query.lastError().databaseText();
            qDebug() << "driverText" << query.lastError().driverText();
            return 0;
        }

        return query.lastInsertId().toInt();
    }

    void update() {}
//    void delete() {}

    void close() {
        if (isOpen_) {
            QSqlDatabase::removeDatabase(db_.connectionName());
        }
    }

private:
    SqlDatabaseHelper(
                const QString &type,
                const QString &hostName,
                const QString &databaseName,
                const QString &userName,
                const QString &password,
                QObject *parent = 0)
        : QObject(parent),
          type_(type),
          hostName_(hostName),
          databaseName_(databaseName),
          userName_(userName),
          password_(password) {
        db_ = QSqlDatabase::addDatabase(type_);
        db_.setHostName(hostName_);
        db_.setDatabaseName(databaseName_);
        if (!(isOpen_ = db_.open(userName_, password_))) {
            qDebug() << "text" << db_.lastError().text();
            qDebug() << "databaseText" << db_.lastError().databaseText();
            qDebug() << "driverText" << db_.lastError().driverText();
        }
    }
    ~SqlDatabaseHelper() {}

    SqlDatabaseHelper(SqlDatabaseHelper const &);
    SqlDatabaseHelper &operator = (SqlDatabaseHelper const&);

    QString type_;
    QString hostName_;
    QString databaseName_;
    QString userName_;
    QString password_;

    QSqlDatabase db_;
    bool isOpen_;
};

#endif // SQLDATABASEHELPER_H
