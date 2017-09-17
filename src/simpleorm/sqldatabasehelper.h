#ifndef SIMPLEORM_H
#define SIMPLEORM_H

#include <QObject>
#include <QStringList>
#include <QVariant>
#include <QSqlDatabase>

class SimpleOrm
{
public:
    SimpleOrm(const QString &type, const QString &connectionName);

    bool open(const QString &hostName, const QString &userName, const QString &password);
    void close();
    bool insertIntoTable(QString tableName, QStringList columns, QStringList values, quint64 &id);
    // TODO: Разобраться с итераторами и исправить
    //    bool updateTable(QString tableName, QList<QPair<QString, QString> > list, quint64 id);
    bool updateTable(QString tableName, QPair<QString, QString> pair, quint64 id);
    bool selectFromTable();

private:
    QSqlDatabase db_;
    bool isOpen_;
};

#endif // SIMPLEORM_H
