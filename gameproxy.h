#ifndef GAMEPROXY_H
#define GAMEPROXY_H

#include <QObject>
#include "cellsmodel.h"
#include "time.h"
#include <QDebug>
#include <QSound>
#include <QTimer>
#include <QTime>

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
    Q_INVOKABLE void finishGame(bool isWon);

    CellsModel* getGameModel();

    Q_PROPERTY(QString gameTime READ getGameTime WRITE setGameTime NOTIFY gameTimeChanged)
    QString getGameTime();
    void setGameTime(QString value);

    Q_PROPERTY(bool isCompleted READ isCompleted WRITE setGameState NOTIFY gameStateChanged)
    Q_PROPERTY(bool isWon READ isWon WRITE setGameState NOTIFY gameStateChanged)
    bool isWon();
    bool isCompleted();
    void setGameState(int value);
    int getGameState();

    Q_PROPERTY(bool isPressed READ isPressed WRITE setIsPressed NOTIFY isPressedChanged)
    bool isPressed();
    void setIsPressed(bool value);

    enum States {
        GameNotStarted = 0,
        GameContinuing = 1,
        GameWon = 2,
        GameLost = 3,
    };

signals:
    void gameTimeChanged();
    void gameStateChanged();
    void isPressedChanged();

public slots:
    void onTimer();

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
    QSound* markedSound;

    QTimer* m_timer;
    QTime m_startTime;
    QTime m_curTime;
    QTime m_gameTime;
    QString m_strGameTime;

    int m_gameState;
    bool m_isPressed;
};

#endif // GAMEPROXY_H
