#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Cell class to represent a single cell in the grid
class Cell {
    bool alive;

public:
    Cell() : alive(false) {}

    bool isAlive() const { return alive; }
    void setAlive(bool state) { alive = state; }
};

// Grid class to manage the grid of cells
class Grid {
    int rows, cols;
    vector<vector<Cell>> grid;

public:
    Grid(int r, int c) : rows(r), cols(c), grid(r, vector<Cell>(c)) {}

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    Cell& getCell(int row, int col) {
        return grid[row][col];
    }

    void displayGrid() const {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                cout << (grid[row][col].isAlive() ? "O" : ".");
            }
            cout << endl;
        }
        cout << endl;
    }

    int countLiveNeighbors(int row, int col) const {
        int liveNeighbors = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int r = row + i;
                int c = col + j;
                if (r >= 0 && r < rows && c >= 0 && c < cols) {
                    if (grid[r][c].isAlive()) {
                        liveNeighbors++;
                    }
                }
            }
        }
        return liveNeighbors;
    }

    void updateGrid() {
        vector<vector<Cell>> newGrid = grid;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                int liveNeighbors = countLiveNeighbors(row, col);
                if (grid[row][col].isAlive()) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        newGrid[row][col].setAlive(false); // Cell dies
                    }
                } else {
                    if (liveNeighbors == 3) {
                        newGrid[row][col].setAlive(true); // Cell becomes alive
                    }
                }
            }
        }
        grid = newGrid;
    }
};

// GameOfLife class to control the simulation
class GameOfLife {
    Grid grid;

public:
    GameOfLife(int rows, int cols) : grid(rows, cols) {}

    void setInitialState() {
        int row, col;
        cout << "Enter initial live cells (row col). Enter -1 -1 to stop:" << endl;
        while (true) {
            cin >> row >> col;
            if (row == -1 && col == -1) break;
            if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
                grid.getCell(row, col).setAlive(true);
            } else {
                cout << "Invalid position. Try again." << endl;
            }
        }
    }

    void runSimulation() {
        while (true) {
            grid.displayGrid();
            grid.updateGrid();
            this_thread::sleep_for(chrono::milliseconds(500)); // Delay for visualization
            system("clear"); // Clear the console (use "cls" if on Windows)
        }
    }
};

int main() {
    int rows = 20, cols = 20;
    GameOfLife game(rows, cols);

    game.setInitialState();
    game.runSimulation();

    return 0;
}
