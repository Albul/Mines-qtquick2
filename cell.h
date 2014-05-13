#ifndef CELL_H
#define CELL_H
#include <QObject>

class Cell : public QObject
{   
    Q_OBJECT

private:
    bool _isOpened;
    bool _hasMine;
    bool _hasFlag;
    int _minesBeside;

public:
    Cell():_isOpened(false), _hasMine(false), _hasFlag(false), _minesBeside(0) {}

    Q_PROPERTY(bool isOpened READ isOpened WRITE setIsOpened NOTIFY isOpenedChanged)
    bool isOpened();
    void setIsOpened(bool value);

    Q_PROPERTY(bool hasMine READ hasMine WRITE setHasMine NOTIFY hasMineChanged)
    bool hasMine();
    void setHasMine(bool value);

    Q_PROPERTY(bool hasFlag READ hasFlag WRITE setHasFlag NOTIFY hasFlagChanged)
    bool hasFlag();
    void setHasFlag(bool value);

    Q_PROPERTY(int minesBeside READ minesBeside WRITE setMinesBeside NOTIFY minesBesideChanged)
    int minesBeside();
    void setMinesBeside(int value);

signals:
    void isOpenedChanged();
    void hasMineChanged();
    void hasFlagChanged();
    void minesBesideChanged();
};

#endif // CELL_H
