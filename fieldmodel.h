#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QAbstractListModel>
#include "cell.h"
#include <cstddef>

class FieldModel : public QAbstractListModel
{
    Q_OBJECT

    //////////////// Public methods ////////////////
public:

    enum Constants {
        Mine = -1
    };

    explicit FieldModel(QObject *parent = 0);
    ~FieldModel();

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
    Cell* getCell(int i, int j) const;
    Cell* getCell(int index) const;
    QList <int> getNeighbors(int index);

signals:

public slots:

    //////////////// Private methods ////////////////
private:
    void initList();
    bool isValid(int index) const;
    bool isLeftmost(int index) const;
    bool isRightmost(int index) const;

    //////////////// Private members ////////////////
private:
    int m_numCols;
    int m_numRows;
    int m_numMines;
    int m_numClosed;

    QList< Cell* > m_listCells;

    //////////////// Private enumerations ////////////////
private:
    enum FieldRoles {
        DataRole = Qt::UserRole + 1
    };
};

#endif // FIELDMODEL_H
