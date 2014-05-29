#include "recordsmodel.h"

RecordsModel::RecordsModel()
{
}

/// Setting the database
/// \brief RecordsModel::initDb
///
void RecordsModel::initDb()
{
    beginResetModel();
    m_dbRecords = QSqlDatabase::addDatabase("QSQLITE");
    m_dbRecords.setHostName("localhost");
    m_dbRecords.setDatabaseName("db_records.sqlite");
    if (!m_dbRecords.open()) {
        qDebug() << "creating db: " << m_dbRecords.lastError().text();
    }

    m_query = new QSqlQuery(m_dbRecords);
    QString strQuery = "CREATE TABLE records_table ("
            "number integer PRIMARY KEY, "
            "name VARCHAR(255), "
            "rows integer, "
            "cols integer, "
            "mines integer, "
            "time integer, "
            "factor real"
            ");";
    bool b = m_query->exec(strQuery);
    if (!b) {
        qDebug() << "creating table: " << m_query->lastError().text();
    } else {
        strQuery = "INSERT INTO records_table (number, name, rows, cols, mines, time, factor) "
                "VALUES (1, 'empty', 8, 8, 10, 250, 0.000625);";
        b = m_query->prepare(strQuery);
        b = m_query->exec();
        strQuery = "INSERT INTO records_table (number, name, rows, cols, mines, time, factor) "
                "VALUES (2, 'atari', 10, 10, 15, 200, 0.00075);";
        b = m_query->prepare(strQuery);
        b = m_query->exec();
        if (!b) {
            qDebug() <<  "inserting init records: " << m_query->lastError().text();
        }
    }

    b = m_query->exec("SELECT * FROM records_table");
    if (!b) {
        qDebug() <<  "selecting: " << m_query->lastError().text();
    }
    m_query->last();
    m_size = m_query->at() + 1;
    m_query->first();
    endResetModel();
}

int RecordsModel::rowCount(const QModelIndex &parent) const
{
    return m_size;
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{

    if (m_query->at() != index.row())
        m_query->seek(index.row(), false);

    QVariant value;
    switch (role) {
    case NumberRole:
        value = m_query->value(0);
        break;
    case NameRole:
        value = m_query->value(1);
        break;
    case CellsRole:
        value = qVariantFromValue(m_query->value(2).toString() + " / " + m_query->value(3).toString());
        break;
    case MinesRole:
        value = m_query->value(4);
        break;
    case TimeRole: {
        int refMinutes = m_query->value(5).toInt() / 60;
        int refSeconds = m_query->value(5).toInt() % 60;

        QString strTime = refMinutes >= 10?  QString::number(refMinutes) : "0" + QString::number(refMinutes);
        strTime += ":";
        strTime += refSeconds >= 10?  QString::number(refSeconds) : "0" + QString::number(refSeconds);
        value = qVariantFromValue(strTime);
        break;
    }
    default:
        break;
    }
    return value;
}

QHash<int, QByteArray> RecordsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NumberRole] = "number";
    roles[NameRole] = "name";
    roles[CellsRole] = "cells";
    roles[MinesRole] = "mines";
    roles[TimeRole] = "time";
    roles[FactorRole] = "factor";
    return roles;
}

int RecordsModel::isRecord(float factor)
{
    QSqlQuery query;
    query.exec("SELECT * FROM records_table");
    query.first();
    int i = 1;
    while(i <= m_size) {
        if (factor > query.value(6).toFloat()) {
            return i;
        }
        query.next();
        i++;
    }
    return -1;
}

void RecordsModel::addNewRecord(int pos, QString name, int cols, int rows, int mines, int time, float factor)
{
    beginResetModel();
    QSqlQuery query;
    QString strQuery;
    bool b;
    int i = m_size;
    qDebug() << m_size;
    while (i >= pos) {
        strQuery = "UPDATE records_table SET number = number + 1 WHERE number == " + QString::number(i);
        b = query.exec(strQuery);
        if (!b) {
            qDebug() << "updating: " << query.lastError().text();
        }
        i--;
    }

    strQuery = "INSERT INTO records_table (number, name, cols, rows, mines, time, factor) "
            "VALUES (:number, :name, :cols, :rows, :mines, :time, :factor);";
    query.prepare(strQuery);
    query.addBindValue(pos);
    query.addBindValue(name);
    query.addBindValue(cols);
    query.addBindValue(rows);
    query.addBindValue(mines);
    query.addBindValue(time);
    query.addBindValue(factor);
    b = query.exec();
    if (!b) {
        qDebug() << "inserting: " << query.lastError().text();
    }

    b = m_query->exec("SELECT * FROM records_table");
    if (!b) {
        qDebug() << "selecting: " << m_query->lastError().text();
    }
    m_query->last();
    m_size = m_query->at() + 1;
    m_query->first();
    endResetModel();
}
