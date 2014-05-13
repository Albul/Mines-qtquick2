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
        DataRole = Qt::UserRole + 1,
        StateRole
    };

    enum Constants {
        GameContinuing = 0,
        GameWon = 1,
        GameLost = -1,
        Mine = -1
    };

    explicit CellsModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void resetGame(int numCols, int numRows, int numMines);
    void openCell(int index);

    int getNumMines();
    int getNumCells();
    Cell* getCell(int i, int j);
    Cell* getCell(int index);
    QList <int> getNeighbors(int index);

    Q_PROPERTY(bool isCompleted READ isCompleted WRITE setGameState NOTIFY gameStateChanged)
    bool isCompleted();
    void setGameState(int value);

signals:
    void gameStateChanged();

public slots:

    //////////////// Private methods ////////////////
private:
    void initList();
    bool isValid(int index);

    //////////////// Private members ////////////////
private:
    int _gameState;
    int m_numCols;
    int m_numRows;
    int m_numMines;

    QList< Cell* > m_listCells;

};

#endif // CELLSMODEL_H
