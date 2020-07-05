// Title: BattleShip Final Project
// Class: CSC 2430 Spring 2020
// Author: Nicholas Sutanto, collaborated with Sagma Prajapati

#ifndef FINALPROJECT_GRID_H
#define FINALPROJECT_GRID_H

#endif //FINALPROJECT_GRID_H

using namespace std;

enum BoatSize { Destroyer = 2, Submarine = 3, Cruiser = 3, Battleship = 4, Carrier = 5 };
void initGrid(int grid[][10]);
void printBoard(int grid[][10]);
void printGameBoard(int grid[][10]);
int resetColAndRow(int col, int &row, int BoatSize, char d);
char getDirection(int d);
int checkSpaces(int grid[][10], int c, int r, int s, char d);
void editGrid(int grid[][10], int col, int row, int BoatSize, char dir);
int getSpace(int grid[][10], int row, int col);
