#include "gameproxy.h"


//////////////// Public methods ////////////////

GameProxy::GameProxy(QObject *parent) :
    QObject(parent)
{
    m_fieldModel = new FieldModel();
    m_colors << "#0000FF" << "#00A000" << "#0000FF" << "#00007F" <<
                "#A00000" << "#00CCFF" << "#A000A0" << "#000000";

    markedSound = new QSound(":/sounds/marked.wav");
    m_gameState = GameNotStarted;
    m_isPressed = false;
    m_isRecord = false;
    setGameTime("00:00");

    // Setting the database
    m_recordsModel = new RecordsModel();
    m_recordsModel->initDb();
}

void GameProxy::createNewGame(int numCols, int numRows, int numMines) {
    m_fieldModel->resetGame(numCols, numRows, numMines);
    placeMines();
    calcCellsAll();

    // Setting the time
    m_curTime = m_startTime = QTime::currentTime();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    m_timer->start(1000);
    setGameTime("00:00");
    setIsRecord(false);

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
    Cell* tmpCell = m_fieldModel->getCell(index);
    if (!tmpCell->hasFlag()) {
        if (tmpCell->minesBeside() == 0) {
            this->searchEmpry(index);
        } else
            m_fieldModel->openCell(index);

        // Conditions of loss and win
        if (tmpCell->hasMine()) {
            finishGame(false);
        } else if (m_fieldModel->getNumClosed() == m_fieldModel->getNumMines()) {
            finishGame(true);
        }
    }
}

void GameProxy::flag(int index)
{
    Cell* tmpCell = m_fieldModel->getCell(index);
    if (!tmpCell->isOpened()) {
        tmpCell->setHasFlag(!tmpCell->hasFlag());
        markedSound->play();
        setIsPressed(false);
    }
}

void GameProxy::finishGame(bool isWon)
{
    m_timer->stop();

    if (isWon) {
        float mines = static_cast< float >(m_fieldModel->getNumMines());
        float cells = static_cast< float >(m_fieldModel->getNumCells());
        float time = static_cast< float >(m_gameTime.minute() * 60 + m_gameTime.second());
        float factor = 1 / time + mines * 0.022 + 1 / cells;
        int pos = m_recordsModel->isRecord(factor);
        if (pos > 0) {
            m_lastRecord.position = pos;
            m_lastRecord.numCols = m_fieldModel->getNumCols();
            m_lastRecord.numRows = m_fieldModel->getNumRows();
            m_lastRecord.numMines = m_fieldModel->getNumMines();
            m_lastRecord.seconds = m_gameTime.minute() * 60 + m_gameTime.second();
            m_lastRecord.factor = factor;
            setIsRecord(true);
        }
        setGameState(GameWon);
    }
    else
        setGameState(GameLost);
}


//////////////// Getters & setters ////////////////

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

bool GameProxy::isRecord()
{
    return m_isRecord;
}

void GameProxy::setIsRecord(bool value)
{
    if(m_isRecord == value) {
        return ;
    }
    m_isRecord = value;
    emit isRecordChanged();
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

FieldModel* GameProxy::getFieldModel()
{
    return m_fieldModel;
}

RecordsModel* GameProxy::getRecordsModel()
{
    return m_recordsModel;
}


//////////////// Public slots ////////////////

void GameProxy::onTimer()
{
    m_curTime.restart();
    QTime tmpTime(0, 0, 0, 0);
    m_gameTime = tmpTime.addSecs(m_startTime.secsTo(m_curTime));
    setGameTime(m_gameTime.toString("mm:ss"));
}

void GameProxy::onUsernameInputed(const QString &name)
{
    m_lastRecord.name = name;
    m_recordsModel->addNewRecord(&m_lastRecord);
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
    int mines = m_fieldModel->getNumMines();
    int randIndex;
    Cell* randCell;
    while (mines) {
        randIndex = getRandom(0, m_fieldModel->getNumCells());
        randCell = m_fieldModel->getCell(randIndex);
        if (!randCell->hasMine()) {
            randCell->setHasMine(true);
            mines--;
        }
    }
}

int GameProxy::calcCell(int index)
{
    int count = 0;
    QList <int> neighbors = m_fieldModel->getNeighbors(index);
    for (int i = 0, length = neighbors.length(); i < length; i++) {
        if (m_fieldModel->getCell(neighbors.at(i))->hasMine())
            count++;
    }
    return count;
}

void GameProxy::calcCellsAll()
{
    Cell* tmpCell;
    for (int i = 0, length = m_fieldModel->getNumCells(); i < length; i++) {
        tmpCell = m_fieldModel->getCell(i);
        if (tmpCell->hasMine())
            tmpCell->setMinesBeside(m_fieldModel->Mine);
        else
            tmpCell->setMinesBeside(calcCell(i));
    }
}

void GameProxy::searchEmpry(int index)
{
    Cell* tmpCell;
    m_fieldModel->openCell(index);
    tmpCell = m_fieldModel->getCell(index);
    if (tmpCell->minesBeside() > 0) return;

    QList <int> neighbors = m_fieldModel->getNeighbors(index);
    int tmpIndex;

    for (int i = 0, length = neighbors.length(); i < length; i++) {
        tmpIndex = neighbors.at(i);
        tmpCell =  m_fieldModel->getCell(tmpIndex);
        if (!tmpCell->hasMine() && !tmpCell->isOpened()) {
            searchEmpry(tmpIndex);
        }
    }
}
