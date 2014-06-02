#include "recordsmodel.h"

RecordsModel::RecordsModel(QObject *parent):
    QAbstractListModel(parent)
{
}

RecordsModel::~RecordsModel()
{
}

/*!
 * \brief RecordsModel::initDb Setting the database
 */
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
    QString strQuery = "CREATE TABLE records ("
            "number integer PRIMARY KEY, "
            "name VARCHAR(255), "
            "rows integer, "
            "cols integer, "
            "mines integer, "
            "seconds integer, "
            "factor real"
            ");";
    bool b = m_query->exec(strQuery);
    if (!b) {
        qDebug() << "creating table: " << m_query->lastError().text();
    } else {
        strQuery = "INSERT INTO records (number, name, rows, cols, mines, seconds, factor) "
                "VALUES (?, ?, ?, ?, ?, ?, ?);";
        m_query->prepare(strQuery);
        m_query->bindValue(Number, 1);
        m_query->bindValue(Name, "Null");
        m_query->bindValue(Rows, 10);
        m_query->bindValue(Cols, 10);
        m_query->bindValue(Mines, 15);
        m_query->bindValue(Seconds, 83);
        m_query->bindValue(Factor, 0.1721);

        b = m_query->exec();
        if (!b) {
            qDebug() <<  "inserting initial records: " << m_query->lastError().text();
        }
        m_query->prepare(strQuery);
        m_query->bindValue(Number, 2);
        m_query->bindValue(Name, "Empty");
        m_query->bindValue(Rows, 8);
        m_query->bindValue(Cols, 8);
        m_query->bindValue(Mines, 10);
        m_query->bindValue(Seconds, 72);
        m_query->bindValue(Factor, 0.1295);
        b = m_query->exec();
        if (!b) {
            qDebug() <<  "inserting initial records: " << m_query->lastError().text();
        }
    }

    b = m_query->exec("SELECT * FROM records");
    if (!b) {
        qDebug() <<  "selecting: " << m_query->lastError().text();
    }
    refreshQuery();
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
        value = m_query->value(Number);
        break;
    case NameRole:
        value = m_query->value(Name);
        break;
    case CellsRole:
        value = qVariantFromValue(m_query->value(Rows).toString() + " / " + m_query->value(Cols).toString());
        break;
    case MinesRole:
        value = m_query->value(Mines);
        break;
    case TimeRole: {
        int refMinutes = m_query->value(Seconds).toInt() / 60;
        int refSeconds = m_query->value(Seconds).toInt() % 60;

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

/*!
 * \brief RecordsModel::isRecord
 * \param factor
 * \return
 */
int RecordsModel::isRecord(float factor)
{
    QSqlQuery query;
    query.exec("SELECT * FROM records");
    query.last();
    int i = m_size;
    while(i >= 1) {
        if (factor > query.value(Factor).toFloat()) {
            query.previous();
            i--;
        } else
            return i + 1;

    }
    return 1;
}

void RecordsModel::addNewRecord(DataRecord* record)
{
    beginResetModel();
    QSqlQuery query;
    QString strQuery;
    bool b;
    int i = m_size;
    qDebug() << record->factor;
    while (i >= record->position) {
        strQuery = "UPDATE records SET number = number + 1 WHERE number == " + QString::number(i);
        b = query.exec(strQuery);
        if (!b) {
            qDebug() << "updating: " << query.lastError().text();
        }
        i--;
    }

    strQuery = "INSERT INTO records (number, name, cols, rows, mines, seconds, factor) "
            "VALUES (?, ?, ?, ?, ?, ?, ?);";
    query.prepare(strQuery);
    query.bindValue(Number, record->position);
    query.bindValue(Name, record->name);
    query.bindValue(Rows, record->numCols);
    query.bindValue(Cols, record->numRows);
    query.bindValue(Mines, record->numMines);
    query.bindValue(Seconds, record->seconds);
    query.bindValue(Factor, record->factor);
    b = query.exec();
    if (!b) {
        qDebug() << "inserting: " << query.lastError().text();
    }

    refreshQuery();
    if (m_size > MAX_SIZE) {
        trimTable();
    }

    b = m_query->exec("SELECT * FROM records");
    if (!b) {
        qDebug() << "selecting: " << m_query->lastError().text();
    }
    refreshQuery();
    endResetModel();
}


//////////////// Private methods ////////////////

void RecordsModel::trimTable()
{
    QSqlQuery query;
    query.prepare("DELETE FROM records WHERE number > " + QString::number(MAX_SIZE));
    if(!query.exec())
        qDebug() << query.lastError().text();
}

void RecordsModel::refreshQuery()
{
    m_query->last();
    m_size = m_query->at() + 1;
    m_query->first();
}
