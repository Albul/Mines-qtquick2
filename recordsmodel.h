#ifndef RECORDSMODEL_H
#define RECORDSMODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QtSql>

class RecordsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NumberRole = Qt::UserRole + 1,
        NameRole,
        CellsRole,
        MinesRole,
        TimeRole,
        FactorRole
    };

    RecordsModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void initDb();
    int isRecord(float factor);
    void addNewRecord(int pos, QString name, int cols, int rows, int mines, int time, float factor);

private:
     QSqlQuery* m_query;
     QSqlDatabase m_dbRecords;
     int m_size;
};

#endif // RECORDSMODEL_H
