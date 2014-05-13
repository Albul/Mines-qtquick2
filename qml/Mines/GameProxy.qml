import QtQuick 2.0

QtObject {
    id: gameProxy
    property int numCols: 0
    property int numRows: 0
    property int numMines: 0
    property bool gameCompleted: false
    property ListModel cellsModel: ListModel {}


    //    function Cell(isOpened, hasMine, hasFlag, numMines) {
    //        this.isOpened = isOpened;
    //        this.hasMine = hasMine;
    //        this.hasFlag = hasFlag;
    //        this.numMines = numMines;
    //    }

    function getRandomInt(min, max) {
        return Math.floor(Math.random() * (max - min + 1)) + min;
    }

    function getNeighbors(i) {
        var k, n = 1, neighbors = [];
        while (n <= 8) {
            // Determine the direction
            switch (n) {
            case 1:
                k = i - numCols - 1;
                if (i % numCols == 0)
                    k = -1;
                break;
            case 2:
                k = i - numCols;
                break;
            case 3:
                k = i - numCols + 1;
                if (i % numCols == numCols - 1)
                    k = -1;
                break;
            case 4:
                k = i - 1;
                if (i % numCols == 0)
                    k = -1;
                break;
            case 5:
                k = i + 1;
                if (i % numCols == numCols - 1)
                    k = -1;
                break;
            case 6:
                k = i + numCols - 1;
                if (i % numCols == 0)
                    k = -1;
                break;
            case 7:
                k = i + numCols;
                break;
            case 8:
                k = i + numCols + 1;
                if (i % numCols == numCols - 1)
                    k = -1;
                break;
            }
            if (isValid(k)) {
                neighbors.push(k);
            }
            n++;
        }
        return neighbors;
    }

    function calculateCell(index) {
        var count = 0, neighbors;

        // Check the neighboring cells
        neighbors = getNeighbors(index);
        for (var i = 0, length = neighbors.length; i < length; i++) {
            if (cellsModel.get(neighbors[i]).hasMine)
                count++;
        }
        return count;
    }


    function calculateCells() {
        for (var i = 0, length = cellsModel.count; i < length; i++) {
            if (!cellsModel.get(i).hasMine)
                cellsModel.get(i).numMines = calculateCell(i);
            else
                cellsModel.get(i).numMines = -1;
        }
    }

    function searchEmpty(index) {
        var cell = cellsModel.get(index);


//        if (cell.numMines > 0 && !cell.hasMine) return;

        var k, l, neighbors;
        neighbors = getNeighbors(index);
        for (var i = 0, length = neighbors.length; i < length; i++) {
            cell = cellsModel.get(neighbors[i]);
            if (!cell.hasMine) {
                openCell(neighbors[i]);
            }
            if (cell.numMines == 0) {
                searchEmpty(neighbors[i]);
            }
        }
    }

    function createCell(isOpened, hasMine, hasFlag, numMines, forceOpened) {
        var cell = {};
        cell.isOpened = isOpened;
        cell.hasMine = hasMine;
        cell.hasFlag = hasFlag;
        cell.numMines = numMines;
        cell.forceOpened = forceOpened;
        return cell;
    }

    function initList(list, count) {
        for (var i = 0; i < count; i++) {
            list.append(createCell(false, false, false, 0, false));
        }
    }

    function fillList(list, count) {
        while (count) {
            var rand = getRandomInt(0, list.count);
            var randItem = list.get(rand);
            if (!randItem.hasMine) {
                randItem.hasMine = true;
                count--;
            }
        }
    }

    function isValid(index) {
        if (0 <= index && index < cellsModel.count) {
            return true;
        } else {
            return false;
        }
    }

    function openCell(index) {
        cellsModel.get(index).isOpened = true;
    }

    function flip(index) {
        console.log("start flip", new Date().getMilliseconds());
        var cell = cellsModel.get(index);
        if (!cell.hasFlag) {
            openCell(index);
            if (cell.numMines == 0) {
                searchEmpty(index);
            }
            if (cellsModel.get(index).hasMine) {
                for (var i = 0; i < cellsModel.count; i++) {
                    if (!cellsModel.get(i).isOpened) {
                        cellsModel.get(i).forceOpened = true;
                    }
                }
                gameCompleted = true;
                console.log("end of game");
            }
        }
        console.log("end flip", new Date().getMilliseconds());
    }

    function flag(index) {
        var cell = cellsModel.get(index);
        if (!cell.isOpened) {
            cell.hasFlag = !cell.hasFlag;
        }
        cellsModel.set(index, cell);
    }

    function createNewGame(cols, rows, mines) {
        numCols = cols;
        numRows = rows;
        numMines = mines;
        cellsModel.clear();
        initList(cellsModel, numCols * numRows);
        fillList(cellsModel, numMines);
        calculateCells();
    }
}
