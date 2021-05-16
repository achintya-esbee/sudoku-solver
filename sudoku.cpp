#include <bits/stdc++.h>
using namespace std;
#define n 9

bool solveSudoku (int grid [n][n]);
void display (int grid[n][n]);
bool usedInRow (int grid[n][n], int row, int num);
bool usedInCol (int grid[n][n], int col, int num);
bool usedInBox (int grid[n][n], int row, int col, int num);
bool isSafe (int grid[n][n], int row, int col, int num);
bool findUnassignedLocation (int grid[n][n], int& row, int& col);

int main() {
    //init puzzle grid
    int grid[n][n] = {  { 1, 0, 0, 4, 8, 9, 0, 0, 6},
                        { 7, 3, 0, 0, 0, 0, 0, 4, 0},
                        { 0, 0, 0, 0, 0, 1, 2, 9, 5},
                        { 0, 0, 7, 1, 2, 0, 6, 0, 0},
                        { 5, 0, 0, 7, 0, 3, 0, 0, 8},
                        { 0, 0, 6, 0, 9, 5, 7, 0, 0},
                        { 9, 1, 4, 6, 0, 0, 0, 0, 0},
                        { 0, 2, 0, 0, 0, 0, 0, 3, 7},
                        { 8, 0, 0, 5, 1, 2, 0, 0, 4} };
    
    //display board
    //cout << "The puzzle grid you entered: \n";
    //display(grid);

    //driver
    if (solveSudoku(grid) == true) 
        display(grid); 
    else
        cout << "No solution exists"; 
}

void display (int grid[n][n]) {
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            cout << grid [i][j] << " ";
            if (j==2 || j==5) {
                cout << "| ";
            }
        }
        cout << "\n";
        if (i==2 || i==5) {
            for (int k=0; k<21; k++) {
                cout << "-";
            }
            cout << "\n";
        }
        
    }
}

bool solveSudoku (int grid[n][n]) {
    int row, col;

    //checks if there are any unused cells
    if (!findUnassignedLocation(grid, row, col)){
        //we are done
        return true;
    }

    //to consider numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        //checking if its safe
        if (isSafe(grid, row, col, num)) {
            //make a temp number change
            grid[row][col] = num;

            //calls recursively, if success, sudoku solved
            if (solveSudoku(grid))
                return true;

            //choice is unmade if we meet a deadend 
            grid[row][col] = 0;
        }
    }
    return false;
}

bool usedInCol(int grid[n][n], int col, int num) 
{ 
    for (int row = 0; row < n; row++) 
        if (grid[row][col] == num) 
            return true; 
    return false; 
} 

bool usedInRow(int grid[n][n], int row, int num) 
{ 
    for (int col = 0; col < n; col++) 
        if (grid[row][col] == num) 
            return true; 
    return false; 
} 

bool usedInBox(int grid[n][n], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) 
        for (int col = 0; col < 3; col++) 
            if (grid[row + boxStartRow][col + boxStartCol] == num) 
                return true; 
    return false; 
}

bool isSafe(int grid[n][n], int row, int col, int num) {
    return !usedInRow(grid, row, num) && !usedInCol(grid, col, num)
        && !usedInBox(grid, row-row%3, col-col%3, num) && grid[row][col] == 0;
}

bool findUnassignedLocation (int grid[n][n], int& row, int& col) {
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}