var numCols, numRows, numMines;
var cellsModel;

var Cell = function(isOpened, hasMine, hasFlag, numMines) {
    this.isOpened = isOpened;
    this.hasMine = hasMine;
    this.hasFlag = hasFlag;
    this.numMines = numMines;
};

Cell.prototype = {

};


var getRandomInt = function(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
};

var initList = function(list, count) {
    for (var i = 0; i < count; i++) {
        list.append(new Cell(false, false, false, 0));
    }
};

var fillList = function(list, count) {
    while (count) {
        var rand = getRandomInt(0, list.count);
        var randItem = list.get(rand);
        if (!randItem.hasMine) {
            randItem.hasMine = true;
            count--;
        }
    }
}

var isValid = function(index) {
    if (0 <= index && index < cellsModel.count) {
        return true;
    } else {
        return false;
    }
}

var getNeighbors = function(i, numCols) {
    var k, n = 1, neighbors = [];
    while (n <= 8) {
        // Determine the direction
        switch (n) {
        case 1:
            k = i - numCols - 1;
            break;
        case 2:
            k = i - numCols;
            break;
        case 3:
            k = i - numCols + 1;
            break;
        case 4:
            k = i - 1;
            break;
        case 5:
            k = i + 1;
            break;
        case 6:
            k = i + numCols - 1;
            break;
        case 7:
            k = i + numCols;
            break;
        case 8:
            k = i + numCols + 1;
            break;
        }
        if (isValid(k)) {
            neighbors.push(k);
        }
        n++;
    }
    return neighbors;
}

function flip(index) {
    console.log("start flip", new Date().getMilliseconds());
    if (!gameView.dataModel.get(index).hasFlag) {
        gameView.dataModel.get(index).isOpened = true;
    }
    console.log("end flip", new Date().getMilliseconds());
    console.log(getNeighbors(index));
}

function flag(index) {
    var cell = gameView.dataModel.get(index);
    if (!cell.isOpened) {
        cell.hasFlag = !cell.hasFlag;
    }
    gameView.dataModel.set(index, cell);
}

function createNewGame(numCols, numRows, numMines) {
    numCols = numCols;
    numRows = numRows;
    numMines = numMines;
    cellsModel = gameView.dataModel;
    cellsModel.clear();
    initList(cellsModel, numCols * numRows);
    fillList(cellsModel, numMines);
};


