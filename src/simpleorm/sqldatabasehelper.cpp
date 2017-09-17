#include "simpleorm.h"

#include <QSqlQuery>

SimpleOrm::SimpleOrm(const QString &type, const QString &connectionName)
{
    db_ = QSqlDatabase::addDatabase(type, connectionName);
    isOpen_ = false;
}

bool SimpleOrm::open(const QString &hostName, const QString &userName, const QString &password)
{
    db_.setDatabaseName(db_.connectionName());
    db_.setHostName(hostName);
    db_.setUserName(userName);
    db_.setPassword(password);

    bool ok = db_.open();
    isOpen_ = ok;
    return ok;
}

void SimpleOrm::close()
{
    QSqlDatabase::removeDatabase(db_.connectionName());
}

bool SimpleOrm::insertIntoTable(QString tableName, QStringList columns, QStringList values,
                                quint64 &id)
{
    // sample
    //INSERT INTO NoiseMonitorSession (startDateTime, channel, antenna, stopDateTime) VALUES
    //  ('2015-12-01 10:00:00', 1, 2, '2015-12-01 10:00:01');
    //
    QString columnsStr = columns.join(", ");
    QString valuesStr = values.join(", ");
    QString queryStr = QString("INSERT INTO %1 (%2) VALUES (%3) RETURNING id").arg(tableName)
            .arg(columnsStr)
            .arg(valuesStr);
    qDebug("%s", queryStr.toStdString().c_str());
    QSqlQuery query(queryStr, db_);
    while (query.next()) {
        id = query.value(0).toInt();
    }
    return query.exec();
}

bool SimpleOrm::selectFromTable()
{
    // sample
    //SELECT * FROM NoiseMonitorSession, NoiseMonitorSessionResult WHERE
    //  NoiseMonitorSessionResult.id_NoiseMonitorSession = NoiseMonitorSession.id;
    //
    return true;
}

bool SimpleOrm::updateTable(QString tableName, QPair<QString, QString> pair, quint64 id)
{
    // sample
    // UPDATE NoiseMonitorSession SET StopDateTime='2015-03-11 09:00:00' WHERE id=117;
    //

    QString columnValue = QString("%1=%2").arg(pair.first).arg(pair.second);
//    QListIterator<QPair<QString, QString> > i(pair);
//    while (i.hasNext()) {
//        columnValue.append(QString("%1=%2").arg(i.next().first).arg(i.next().second));
//    }
    qDebug("%s", columnValue.toStdString().c_str());
//    return true;
    QString queryStr = QString("UPDATE %1 SET %2 WHERE id=%3").arg(tableName)
            .arg(columnValue)
            .arg(id);
    QSqlQuery query(queryStr, db_);
    while (query.next()) {
        id = query.value(0).toInt();
    }
    return query.exec();
}
