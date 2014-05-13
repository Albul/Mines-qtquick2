#include "cell.h"

bool Cell::isOpened() {
    return _isOpened ;
}

void Cell::setIsOpened(bool value) {
    if(_isOpened == value) {
        return ;
    }
    _isOpened = value;
    emit isOpenedChanged();
}

bool Cell::hasMine(){
    return _hasMine;
}

void Cell::setHasMine(bool value) {
    if(_hasMine == value) {
        return ;
    }
    _hasMine = value;
    emit hasMineChanged();
}

bool Cell::hasFlag(){
    return _hasFlag;
}

void Cell::setHasFlag(bool value) {
    if(_hasFlag == value) {
        return ;
    }
    _hasFlag = value;
    emit hasFlagChanged();
}

int Cell::minesBeside() {
    return _minesBeside;
}

void Cell::setMinesBeside(int value) {
    if (_minesBeside == value) {
        return ;
    }
    _minesBeside = value;
    emit minesBesideChanged();
}
