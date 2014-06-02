#include "fieldmodel.h"

FieldModel::FieldModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

FieldModel::~FieldModel()
{
    qDeleteAll(m_listCells.begin(), m_listCells.end());
    m_listCells.clear();
}

int FieldModel::getNumRows()
{
    return m_numRows;
}

int FieldModel::getNumCols()
{
    return m_numCols;
}

int FieldModel::getNumMines()
{
    return m_numMines;
}

int FieldModel::getNumCells()
{
    return m_listCells.count();
}

int FieldModel::getNumClosed()
{
    return m_numClosed;
}

Cell* FieldModel::getCell(int index) const
{
    if (isValid(index)) {
        return m_listCells.at(index);
    }
    return NULL;
}

Cell* FieldModel::getCell(int i, int j) const
{
    int index = i * m_numCols + j;
    return getCell(index);
}

QList <int> FieldModel::getNeighbors(int i)
{
    int k;
    QList <int> neighbors;

    for (int n = 1; n <= 8; n++) {
        switch (n) {
        case 1:
            if (isLeftmost(i))
                k = -1;
            else
                k = i - m_numCols - 1;
            break;
        case 2:
            k = i - m_numCols;
            break;
        case 3:
            if (isRightmost(i))
                k = -1;
            else
                k = i - m_numCols + 1;
            break;
        case 4:
            if (isLeftmost(i))
                k = -1;
            else
                k = i - 1;
            break;
        case 5:
            if (isRightmost(i))
                k = -1;
            else
                k = i + 1;
            break;
        case 6:
            if (isLeftmost(i))
                k = -1;
            else
                k = i + m_numCols - 1;
            break;
        case 7:
            k = i + m_numCols;
            break;
        case 8:
            if (isRightmost(i))
                k = -1;
            else
                k = i + m_numCols + 1;
            break;
        }
        if (isValid(k)) {
            neighbors.append(k);
        }
    }
    return neighbors;
}

void FieldModel::openCell(int index)
{
    getCell(index)->setIsOpened(true);
    m_numClosed--;
}

void FieldModel::resetGame(int numCols, int numRows, int numMines)
{
    beginResetModel();
    m_numCols = numCols;
    m_numRows = numRows;
    m_numMines = numMines;
    m_numClosed = numCols * numRows;
    initList();
    endResetModel();
}

QHash<int, QByteArray> FieldModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DataRole] = "modelData";
    return roles;
}


int FieldModel::rowCount(const QModelIndex &parent) const
{
    return m_listCells.count();
}

QVariant FieldModel::data(const QModelIndex &index, int role) const
{
    int ind = index.row();
    if (!isValid(ind))
        return QVariant();

    if (role == DataRole)
        return qVariantFromValue(getCell(ind));
}


//////////////// Private methods ////////////////

void FieldModel::initList()
{
    int count = m_numCols * m_numRows;
    qDeleteAll(m_listCells.begin(), m_listCells.end());
    m_listCells.clear();
    for (int i = 0; i < count; i++) {
        m_listCells.append(new Cell());
    }
}

bool FieldModel::isValid(int index) const
{
    if (0 <= index && index < m_listCells.count())
        return true;
    else
        return false;
}

bool FieldModel::isLeftmost(int index) const
{
    if (index % m_numCols == 0)
        return true;
    else
        return false;
}

bool FieldModel::isRightmost(int index) const
{
    if (index % m_numCols == m_numCols - 1)
        return true;
    else
        return false;
}
