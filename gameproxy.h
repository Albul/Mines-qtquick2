#ifndef GAMEPROXY_H
#define GAMEPROXY_H

#include <QObject>
#include "cellsmodel.h"
#include "time.h"
#include <QDebug>

class GameProxy : public QObject
{
    Q_OBJECT

    //////////////// Public methods ////////////////
public:
    explicit GameProxy(QObject *parent = 0);

    Q_INVOKABLE void createNewGame(int numCols, int numRows, int numMines);
    Q_INVOKABLE QString getColor(int index);
    Q_INVOKABLE void flip(int index);
    Q_INVOKABLE void flag(int index);
    CellsModel* getGameModel();

signals:

public slots:

    //////////////// Private methods ////////////////
private:
    int getRandom(int min, int max);
    void placeMines();
    int calcCell(int index);
    void calcCellsAll();
    void searchEmpry(int index);

    //////////////// Private members ////////////////
private:
    CellsModel* m_gameModel;
    QList <QString> m_colors;
};

#endif // GAMEPROXY_H
