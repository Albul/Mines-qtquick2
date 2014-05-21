#include "cellsmodel.h"

CellsModel::CellsModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int CellsModel::getNumRows()
{
    return m_numRows;
}

int CellsModel::getNumCols()
{
    return m_numCols;
}

int CellsModel::getNumMines()
{
    return m_numMines;
}

int CellsModel::getNumCells()
{
    return m_listCells.count();
}

int CellsModel::getNumClosed()
{
    return m_numClosed;
}

Cell* CellsModel::getCell(int index)
{
    if (isValid(index)) {
        return m_listCells.at(index);
    }
}

Cell* CellsModel::getCell(int i, int j)
{
    if (i * m_numCols + j < m_listCells.count()) {
        return m_listCells.at(i * m_numCols + j);
    }
}


QList <int> CellsModel::getNeighbors(int i)
{
    int k;
    QList <int> neighbors;

    for (int n = 1; n <= 8; n++) {
        switch (n) {
        case 1:
            k = i - m_numCols - 1;
            if (i % m_numCols == 0)
                k = -1;
            break;
        case 2:
            k = i - m_numCols;
            break;
        case 3:
            k = i - m_numCols + 1;
            if (i % m_numCols == m_numCols - 1)
                k = -1;
            break;
        case 4:
            k = i - 1;
            if (i % m_numCols == 0)
                k = -1;
            break;
        case 5:
            k = i + 1;
            if (i % m_numCols == m_numCols - 1)
                k = -1;
            break;
        case 6:
            k = i + m_numCols - 1;
            if (i % m_numCols == 0)
                k = -1;
            break;
        case 7:
            k = i + m_numCols;
            break;
        case 8:
            k = i + m_numCols + 1;
            if (i % m_numCols == m_numCols - 1)
                k = -1;
            break;
        }
        if (isValid(k)) {
            neighbors.append(k);
        }
    }
    return neighbors;
}


void CellsModel::openCell(int index)
{
    this->getCell(index)->setIsOpened(true);
    m_numClosed--;
}

void CellsModel::resetGame(int numCols, int numRows, int numMines)
{
    beginResetModel();
    m_numCols = numCols;
    m_numRows = numRows;
    m_numMines = numMines;
    m_numClosed = numCols * numRows;
    initList();   
    endResetModel();
}

QHash<int, QByteArray> CellsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DataRole] = "modelData";
    return roles;
}


int CellsModel::rowCount(const QModelIndex &parent) const
{
    return m_listCells.count();
}

QVariant CellsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_listCells.count())
        return QVariant();

    if (!index.isValid())
        return QVariant();

    if (role == DataRole)
        return qVariantFromValue(m_listCells.at(index.row()));
}


//////////////// Private methods ////////////////

void CellsModel::initList()
{
    int count = m_numCols * m_numRows;
    m_listCells.clear();
    for (int i = 0; i < count; i++) {
        m_listCells.append(new Cell());
    }
}

bool CellsModel::isValid(int index)
{
    if (0 <= index && index < m_listCells.count())
        return true;
    else
        return false;
}
