#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QtSql>

struct DataRecord {
    int position;
    QString name;
    int numCols;
    int numRows;
    int numMines;
    int seconds;
    float factor;
};

class RecordsModel : public QAbstractListModel
{
    Q_OBJECT

    //////////////// Public methods ////////////////
public:
    RecordsModel(QObject *parent = 0);
    ~RecordsModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void initDb();
    int isRecord(float factor);
    void addNewRecord(DataRecord* record);

    //////////////// Private methods ////////////////
private:
    void trimTable();
    void refreshQuery();

    //////////////// Private members ////////////////
private:
    QSqlQuery* m_query;
    QSqlDatabase m_dbRecords;
    int m_size; //!< size of the table records

    const int MAX_SIZE = 10;

    //////////////// Private enumerations ////////////////
private:
    enum Roles {
        NumberRole = Qt::UserRole + 1,
        NameRole,
        CellsRole,
        MinesRole,
        TimeRole,
        FactorRole
    };
    enum Indices {
        Number = 0,
        Name = 1,
        Rows = 2,
        Cols = 3,
        Mines = 4,
        Seconds = 5,
        Factor = 6
    };
};

#endif // RECORDSMODEL_H
