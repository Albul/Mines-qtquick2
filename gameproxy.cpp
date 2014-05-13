#include "gameproxy.h"


//////////////// Public methods ////////////////

GameProxy::GameProxy(QObject *parent) :
    QObject(parent)
{
    m_gameModel = new CellsModel();
    m_colors << "#0000FF" << "#00A000" << "#0000FF" << "#00007F" <<
                "#A00000" << "#00CCFF" << "#A000A0" << "#000000";
}

void GameProxy::createNewGame(int numCols, int numRows, int numMines) {
    m_gameModel->resetGame(numCols, numRows, numMines);
    placeMines();
    calcCellsAll();
}

QString GameProxy::getColor(int index)
{
    if (index < 0) { // Mine
        return m_colors.at(0);
    } else if (index > m_colors.count()) {
        index = index % m_colors.count();
    }
    return m_colors.at(index);
}

CellsModel* GameProxy::getGameModel()
{
    return m_gameModel;
}

void GameProxy::flip(int index)
{
    Cell* tmpCell = m_gameModel->getCell(index);
    if (!tmpCell->hasFlag()) {
        m_gameModel->openCell(index);
        if (tmpCell->minesBeside() == 0) {
            this->searchEmpry(index);
        }
        if (tmpCell->hasMine()) {
            m_gameModel->setGameState(m_gameModel->GameLost);
        }
    }
}

void GameProxy::flag(int index)
{
    Cell* tmpCell = m_gameModel->getCell(index);
    if (!tmpCell->isOpened()) {
        tmpCell->setHasFlag(!tmpCell->hasFlag());
    }
}


//////////////// Private methods ////////////////

int GameProxy::getRandom(int min, int max)
{
    static bool first = true;
    if (first) {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % (max - min);
}

void GameProxy::placeMines()
{
    int mines = m_gameModel->getNumMines();
    int randIndex;
    Cell* randCell;
    while (mines) {
        randIndex = getRandom(0, m_gameModel->getNumCells());
        randCell = m_gameModel->getCell(randIndex);
        if (!randCell->hasMine()) {
            randCell->setHasMine(true);
            mines--;
        }
    }
}

int GameProxy::calcCell(int index)
{
    int count = 0;
    QList <int> neighbors = m_gameModel->getNeighbors(index);
    for (int i = 0, length = neighbors.length(); i < length; i++) {
        if (m_gameModel->getCell(neighbors.at(i))->hasMine())
            count++;
    }
    return count;
}

void GameProxy::calcCellsAll()
{
    Cell* tmpCell;
    for (int i = 0, length = m_gameModel->getNumCells(); i < length; i++) {
        tmpCell = m_gameModel->getCell(i);
        if (tmpCell->hasMine())
            tmpCell->setMinesBeside(m_gameModel->Mine);
        else
            tmpCell->setMinesBeside(calcCell(i));
    }
}

void GameProxy::searchEmpry(int index)
{
    Cell* tmpCell;
    m_gameModel->openCell(index);
    tmpCell = m_gameModel->getCell(index);
    if (tmpCell->minesBeside() > 0) return;

    QList <int> neighbors = m_gameModel->getNeighbors(index);
    int tmpIndex;

    for (int i = 0, length = neighbors.length(); i < length; i++) {
        tmpIndex = neighbors.at(i);
        tmpCell =  m_gameModel->getCell(tmpIndex);
        if (!tmpCell->hasMine() && !tmpCell->isOpened()) {
           searchEmpry(tmpIndex);
        }
    }
}
