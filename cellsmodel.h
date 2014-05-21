#ifndef CELLSMODEL_H
#define CELLSMODEL_H

#include <QAbstractListModel>
#include "cell.h"

class CellsModel : public QAbstractListModel
{
    Q_OBJECT

    //////////////// Public methods ////////////////
public:
    enum CellRoles {
        DataRole = Qt::UserRole + 1
    };

    enum Constants {
        Mine = -1
    };

    explicit CellsModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void resetGame(int numCols, int numRows, int numMines);
    void openCell(int index);

    Q_INVOKABLE int getNumRows();
    Q_INVOKABLE int getNumCols();
    Q_INVOKABLE int getNumMines();
    int getNumCells();
    int getNumClosed();
    Cell* getCell(int i, int j);
    Cell* getCell(int index);
    QList <int> getNeighbors(int index);

signals:

public slots:

    //////////////// Private methods ////////////////
private:
    void initList();
    bool isValid(int index);

    //////////////// Private members ////////////////
private:
    int m_numCols;
    int m_numRows;
    int m_numMines;
    int m_numClosed;

    QList< Cell* > m_listCells;
};

#endif // CELLSMODEL_H
