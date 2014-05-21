#include "gameproxy.h"


//////////////// Public methods ////////////////

GameProxy::GameProxy(QObject *parent) :
    QObject(parent)
{
    m_gameModel = new CellsModel();
    m_colors << "#0000FF" << "#00A000" << "#0000FF" << "#00007F" <<
                "#A00000" << "#00CCFF" << "#A000A0" << "#000000";

    markedSound = new QSound(":/sounds/marked.wav");
    m_gameState = GameNotStarted;
    m_isPressed = false;
    setGameTime("00:00");
}

void GameProxy::createNewGame(int numCols, int numRows, int numMines) {
    m_gameModel->resetGame(numCols, numRows, numMines);
    placeMines();
    calcCellsAll();

    // Setting the time
    m_curTime = m_startTime = QTime::currentTime();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    m_timer->start(1000);

    setGameState(GameContinuing);
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

void GameProxy::flip(int index)
{
    Cell* tmpCell = m_gameModel->getCell(index);
    if (!tmpCell->hasFlag()) {
        if (tmpCell->minesBeside() == 0) {
            this->searchEmpry(index);
        } else
            m_gameModel->openCell(index);

        // Conditions of loss
        if (tmpCell->hasMine()) {
            finishGame(false);
        }

        // Conditions of win
        if (m_gameModel->getNumClosed() == m_gameModel->getNumMines()) {
            finishGame(true);
        }
    }
}

void GameProxy::flag(int index)
{
    Cell* tmpCell = m_gameModel->getCell(index);
    if (!tmpCell->isOpened()) {
        tmpCell->setHasFlag(!tmpCell->hasFlag());
        markedSound->play();
        setIsPressed(false);
    }
}

void GameProxy::finishGame(bool isWon)
{
    m_timer->stop();

    if (isWon)
        setGameState(GameWon);
    else
        setGameState(GameLost);
}


//////////////// getters & setters ////////////////

int GameProxy::getGameState()
{
    return m_gameState;
}

void GameProxy::setGameState(int value)
{
    if (m_gameState == value)
        return ;
    m_gameState = value;
    emit gameStateChanged();
}

bool GameProxy::isCompleted()
{
    if (m_gameState == GameWon || m_gameState == GameLost)
        return true;
    else
        return false;
}

bool GameProxy::isWon()
{
    if (m_gameState == GameWon)
        return true;
    else
        return false;
}

QString GameProxy::getGameTime()
{
    return m_strGameTime;
}

void GameProxy::setGameTime(QString value)
{
    if(m_strGameTime == value) {
        return ;
    }
    m_strGameTime = value;
    emit gameTimeChanged();
}

bool GameProxy::isPressed()
{
    return m_isPressed;
}

void GameProxy::setIsPressed(bool value)
{
    if(m_isPressed == value) {
        return ;
    }
    m_isPressed = value;
    emit isPressedChanged();
}

CellsModel* GameProxy::getGameModel()
{
    return m_gameModel;
}


//////////////// public slots ////////////////

void GameProxy::onTimer()
{
    m_curTime.restart();
    QTime tmpTime(0, 0, 0, 0);
    m_gameTime = tmpTime.addSecs(m_startTime.secsTo(m_curTime));
    setGameTime(m_gameTime.toString("mm:ss"));
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
