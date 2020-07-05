// Title: BattleShip Final Project
// Class: CSC 2430 Spring 2020
// Author: Nicholas Sutanto, collaborated with Sagma Prajapati

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

#include "grid.h"

using namespace std;

class Boat {

private:

    char dir;
    int length;
    vector<int> boatrow;
    vector<int> boatcol;
    int hits;
    string names;

public:

    //Default contstructor
    Boat(char d, int len, vector<int> row, vector<int> col, int hit, string name) {

        dir = d;
        length = len;
        boatrow = row;
        boatcol = col;
        hits = hit;
        names = name;
    }

    //set boat hit
    void setHit() {
        hits++;
    }

    int checkSunk(int BoatSize) {
        if(hits >= BoatSize) {
            return 'X';
        } else {

            return 0;
        }
    }

    //get boat grid coordinates
    void boatCoordinates() {
        cout << "Coordinates for boat " << names << endl << endl;
        for(int i=0; i<length; i++) {

            cout << "Grid [" << boatrow[i] << "][" << boatcol[i] << "]" << endl;
        }
        cout << endl;
    }

    //check coordinate bombed to find particular boat
    string getBoat(int r, int c) {
        for(int i=0; i<length; i++) {
            if((boatrow[i]==r) && (boatcol[i]==c)) {
                return names;
            }
        }
        return "";
    }
};

bool setBoat(int grid[][10], int BoatSize, int name, vector<Boat> &boatList);
void editBoatInfo(int grid[][10], int c, int r, int BoatSize, char d, vector<Boat> &boatList, int name);
int playGame(int grid[][10], vector<Boat> &boatList);

int main() {

    int grid[10][10];
    vector<Boat> boatList;
    char play;
    initGrid(grid);

    setBoat(grid, Carrier, 1, boatList);  //set the boats onto the grid
    setBoat(grid, Battleship, 2, boatList);
    setBoat(grid, Destroyer, 3, boatList);
    setBoat(grid, Submarine, 4, boatList);
    setBoat(grid, Cruiser, 5, boatList);

    cout << "Welcome to Battleships. Press p to play." << endl << endl;
    cin >> play;

    if(play == 'p') {
        playGame(grid, boatList);
    }
    return 0;
}

void initGrid(int grid[][10]) {
    for(int col = 0; col < 10; col++) {
        for(int row = 0; row < 10; row++) {
            grid[col][row] = 0;
        }
    }
}

void printBoard(int grid[][10]) {
    cout << "   0|1|2|3|4|5|6|7|8|9|" << endl << endl;
    for(int i = 0; i < 10; i++)   {
        for(int j = 0; j < 10; j++) {

            if(j == 0) {
                cout << i << "  " ;
            }
            cout << grid[i][j] ;
            if(j!= 9) {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void printGameBoard(int grid[][10]) { //Print game board

    cout << "   0|1|2|3|4|5|6|7|8|9|" << endl << endl;
    for (int i = 0; i < 10; i++)  //column loop
    {
        for (int j = 0; j < 10; j++)  //row loop
        {
            if (j == 0) {
                cout << i << "  ";
            }
            if (grid[i][j] == 1)  //if the space is a hit, print O
            {
                cout << "O";
            } else if
                    (grid[i][j] == 9)  //if the space is a miss, print X
            {
                cout << "X";
            } else
            {
                cout << 0;  //otherwise, just print a 0
            }

                if (j != 9) {
                    cout << "|";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    bool setBoat(int grid[][10], int BoatSize, int name, vector<Boat> &boatList) { //Place boats

        srand(time(0));

        int col = 0;
        int row = 0;
        char d = 'v';
        bool placementFailure = true;
        char check = 'v';
        int space = 0;

        d = getDirection(rand() % 10);
        col = resetColAndRow(col, row, BoatSize, d);

        while (placementFailure) {
            if (d == 'h') {
                space = checkSpaces(grid, col, row, BoatSize, d);
                if (space == 1) {

                    d = getDirection(rand() % 10);
                    col = resetColAndRow(col, row, BoatSize, d);
                    space == 0;
                    continue;
                }

                editGrid(grid, col, row, BoatSize, d);//place the boat on the grid
                editBoatInfo(grid, col, row, BoatSize, d, boatList, name);//create boat object
                return 0;

            }

            else if (d == 'v') {
                space = checkSpaces(grid, col, row, BoatSize, d);
                if (space == 1) {
                    d = getDirection(rand() % 10);
                    col = resetColAndRow(col, row, BoatSize, d);
                    space == 0;
                    continue;
                }
                editGrid(grid, col, row, BoatSize, d);
                editBoatInfo(grid, col, row, BoatSize, d, boatList, name);
                return 0;
            }
        }
    }

    char getDirection(int d) {

        if (d > 4) {
            return 'h';
        } else {
            return 'v';
        }
    }

    void editGrid(int grid[][10], int col, int row, int BoatSize, char dir) { //put boat number on the grid

        if (dir == 'h') {
            for (int i = 0; i < BoatSize; i++) {
                grid[row][col] = BoatSize;
                col++;
                cout << endl;
            }
        } else if (dir == 'v') {
            for (int i = 0; i < BoatSize; i++) {
                grid[row][col] = BoatSize;
                row++;
                cout << endl;
            }
        } else {
            cout << "Error" << endl;
        }

    }

    int checkSpaces(int grid[][10], int c, int r, int s, char d) { //check  grid for overlap

        int check = 0;
        if (d == 'h') {
            for (int i = c; i < c + s; i++) {
                check = grid[r][i];
                if (check != 0) {
                    return 1;
                }
            }

            return 0;
        } else {
            for (int i = r; i < r + s; i++) {
                check = grid[i][c];
                if (check != 0) {
                    return 1;

                }
            }

            return 0;
        }
    }

    int resetColAndRow(int col, int &row, int BoatSize, char d) {
        switch (BoatSize) {
            case Submarine:
                if (d == 'h') {
                    col = rand() % 8;
                    row = rand() % 10;
                } else {
                    col = rand() % 10;
                    row = rand() % 8;
                }
                break;
            case Destroyer:
                if (d == 'h') {
                    col = rand() % 7;
                    row = rand() % 10;
                } else {
                    col = rand() % 10;
                    row = rand() % 7;
                }
                break;
            case Battleship:
                if (d == 'h') {
                    col = rand() % 6;
                    row = rand() % 10;
                } else {
                    col = rand() % 10;
                    row = rand() % 6;
                }
                break;
            case Carrier:
                if (d == 'h') {
                    col = rand() % 5;
                    row = rand() % 10;
                } else {
                    col = rand() % 10;
                    row = rand() % 5;
                }
        }
        return col;
    }

    void editBoatInfo(int grid[][10], int c, int r, int BoatSize, char d, vector<Boat> &boatList, int name) {
        switch (name) {
            case 1:
                if (d == 'h') {
                    vector<int> r1(5);

                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(5);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Carrier
                    Boat carrierBoat('h', 5, r1, c1, 0, "Carrier");
                    boatList.push_back(carrierBoat);
                } else if (d == 'v') {
                    vector<int> r1(5);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(5);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Carrier
                    Boat carrierBoat('v', 5, r1, c1, 0, "Carrier");
                    boatList.push_back(carrierBoat);
                }
                break;
            case 2:
                if (d == 'h') {
                    vector<int> r1(4);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(4);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Battleship 1
                    Boat battleship1Boat('h', 4, r1, c1, 0, "Battleship 1");
                    boatList.push_back(battleship1Boat);
                } else if (d == 'v') {
                    vector<int> r1(4);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(4);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Battleship 1
                    Boat battleship1Boat('v', 4, r1, c1, 0, "Battleship 1");
                    boatList.push_back(battleship1Boat);
                }
                break;
            case 3:
                if (d == 'h') {
                    vector<int> r1(4);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(4);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Battleship 2
                    Boat battleship2Boat('h', 4, r1, c1, 0, "Battleship 2");
                    boatList.push_back(battleship2Boat);

                } else if (d == 'v') {
                    vector<int> r1(4);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(4);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Battleship 2
                    Boat battleship2Boat('v', 4, r1, c1, 0, "Battleship 2");
                    boatList.push_back(battleship2Boat);
                }
                break;
            case 4:
                if (d == 'h') {
                    vector<int> r1(3);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(3);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Destroyer 1
                    Boat destroyer1Boat('h', 3, r1, c1, 0, "Destroyer 1");
                    boatList.push_back(destroyer1Boat);

                } else if (d == 'v') {
                    vector<int> r1(3);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(3);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Destroyer 1
                    Boat destroyer1Boat('v', 3, r1, c1, 0, "Destroyer 1");
                    boatList.push_back(destroyer1Boat);
                }
                break;
            case 5:
                if (d == 'h') {
                    vector<int> r1(3);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(3);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Destroyer 2
                    Boat destroyer2Boat('h', 3, r1, c1, 0, "Destroyer 2");
                    boatList.push_back(destroyer2Boat);

                } else if (d == 'v') {
                    vector<int> r1(3);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(3);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Destroyer 2
                    Boat destroyer2Boat('v', 3, r1, c1, 0, "Destroyer 2");
                    boatList.push_back(destroyer2Boat);
                }
                break;
            case 6:
                if (d == 'h') {
                    vector<int> r1(3);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(3);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Destroyer 3
                    Boat destroyer3Boat('h', 3, r1, c1, 0, "Destroyer 3");
                    boatList.push_back(destroyer3Boat);

                } else if (d == 'v') {
                    vector<int> r1(3);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(3);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Destroyer 3
                    Boat destroyer3Boat('v', 3, r1, c1, 0, "Destroyer 3");
                    boatList.push_back(destroyer3Boat);
                }
                break;
            case 7:
                if (d == 'h') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Submarine1
                    Boat submarine1Boat('h', 2, r1, c1, 0, "Submarine 1");
                    boatList.push_back(submarine1Boat);

                } else if (d == 'v') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Submarine 1
                    Boat submarine1Boat('v', 2, r1, c1, 0, "Submarine 1");
                    boatList.push_back(submarine1Boat);
                }
                break;
            case 8:
                if (d == 'h') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Submarine 2
                    Boat submarine2Boat('h', 2, r1, c1, 0, "Submarine 2");
                    boatList.push_back(submarine2Boat);

                } else if (d == 'v') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Submarine 2
                    Boat submarine2Boat('v', 2, r1, c1, 0, "Submarine 2");
                    boatList.push_back(submarine2Boat);
                }
                break;
            case 9:
                if (d == 'h') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Submarine 3
                    Boat submarine3Boat('h', 2, r1, c1, 0, "Submarine 3");
                    boatList.push_back(submarine3Boat);

                } else if (d == 'v') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Submarine 3
                    Boat submarine3Boat('v', 2, r1, c1, 0, "Submarine 3");
                    boatList.push_back(submarine3Boat);
                }
                break;
            case 10:
                if (d == 'h') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                        c++;
                    }
                    //Submarine 4
                    Boat submarine4Boat('h', 2, r1, c1, 0, "Submarine 4");
                    boatList.push_back(submarine4Boat);

                } else if (d == 'v') {
                    vector<int> r1(2);
                    for (int i = 0; i < (int) r1.size(); ++i) {
                        r1.at(i) = r;
                        r++;
                    }
                    vector<int> c1(2);
                    for (int i = 0; i < (int) c1.size(); ++i) {
                        c1.at(i) = c;
                    }
                    //Submarine 4
                    Boat submarine4Boat('v', 2, r1, c1, 0, "Submarine 4");
                    boatList.push_back(submarine4Boat);
                }
                break;
        }
    }

    int playGame(int grid[][10], vector<Boat> &boatList) {


        bool gameInProgress = true;
        int row = 0;
        int col = 0;
        int guess = 0;
        int hit = 0;
        int miss = 0;
        int space = 0;
        char d = 'g';
        string btname = "";
        int sunk = 0;

        while (gameInProgress) {


            printGameBoard(grid);
            cout << "Enter a row coordinate: ";
            cin >> row;
            cout << "Enter a column coordinate: ";
            cin >> col;
            cout << endl;
            guess++;
            space = getSpace(grid, row, col);

            switch (space) {
                case 0:
                    cout << "You missed" << endl;
                    grid[row][col] = 9;
                    miss++;
                    break;
                case 1:
                    cout << "You already fired here" << endl;
                    break;
                case 2:
                    grid[row][col] = 1;
                    hit++;

                    btname = boatList[6].getBoat(row, col);  //Check to see if boat is Submarine 1
                    if (btname == "Submarine 1") {
                        cout << "You bombed " << btname << "!" << endl;
                        boatList[6].setHit();
                        sunk = boatList[6].checkSunk(Submarine);
                        if (sunk == 9) {
                            cout << "You sunk Submarine 1." << endl;
                        }

                    } else if (btname.empty()) {
                        btname = boatList[7].getBoat(row, col);  //Check to see if boat is Submarine 2
                        if (btname == "Submarine 2") {
                            cout << "You bombed " << btname << "!" << endl;
                            boatList[7].setHit();
                            sunk = boatList[7].checkSunk(Submarine);
                            if (sunk == 9) {
                                cout << "You sunk Submarine 2." << endl;
                            }

                        } else if (btname.empty()) {
                            btname = boatList[8].getBoat(row, col);  //Check to see if boat is Submarine 3
                            cout << "You bombed " << btname << "!" << endl;
                            boatList[8].setHit();
                            sunk = boatList[8].checkSunk(Submarine);
                            if (sunk == 9) {
                                cout << "You sunk Submarine 3." << endl;
                            }

                        } else if (btname.empty()) {
                            btname = boatList[9].getBoat(row, col);  //Check to see if boat is Submarine 4
                            cout << "You bombed " << btname << "!" << endl;
                            boatList[9].setHit();
                            sunk = boatList[9].checkSunk(Submarine);
                            if (sunk == 9) {
                                cout << "You sunk Submarine 4." << endl;
                            }
                        }
                    }
                    btname.clear();
                    break;
                case 3:
                    grid[row][col] = 1;
                    hit++;

                    btname = boatList[3].getBoat(row, col);  //Check to see if boat is Destroyer 1
                    if (btname == "Destroyer 1") {
                        cout << "You bombed " << btname << "!" << endl;
                        boatList[3].setHit();
                        sunk = boatList[3].checkSunk(Destroyer);
                        if (sunk == 9) {
                            cout << "You sunk Destroyer 1." << endl;
                        }

                    } else if (btname.empty()) {
                        btname = boatList[4].getBoat(row, col);  //Check to see if boat is Destroyer 2
                        if (btname == "Destroyer 2") {
                            cout << "You bombed " << btname << "!" << endl;
                            boatList[4].setHit();
                            sunk = boatList[4].checkSunk(Destroyer);
                            if (sunk == 9) {
                                cout << "You sunk Destroyer 2." << endl;
                            }

                        } else if (btname.empty()) {
                            btname = boatList[5].getBoat(row, col);  //Check to see if boat is Destroyer 3
                            cout << "You bombed " << btname << "!" << endl;
                            boatList[5].setHit();
                            sunk = boatList[5].checkSunk(Destroyer);
                            cout << "sunk is " << sunk << endl;
                            if (sunk == 9) {
                                cout << "You sunk Destroyer 3." << endl;
                            }
                        }
                    }
                    btname.clear();
                    break;
                case 4:
                    grid[row][col] = 1;
                    hit++;

                    btname = boatList[1].getBoat(row, col);  //Check to see if boat is Battleship 1
                    if (btname == "Battleship 1") {
                        cout << "You bombed " << btname << "!" << endl;
                        boatList[1].setHit();
                        sunk = boatList[1].checkSunk(Battleship);
                        if (sunk == 9) {
                            cout << "You sunk Battleship 1." << endl;
                        }
                    }
                    if (btname.empty()) {
                        btname = boatList[2].getBoat(row, col);  //Check to see if boat is Battleship 2
                        cout << "You have bombed " << btname << "!" << endl;
                        boatList[2].setHit();
                        sunk = boatList[2].checkSunk(Battleship);
                        if (sunk == 9) {
                            cout << "You have sunk Battleship 2." << endl;
                        }
                    }
                    btname.clear();
                    break;
                case 5:
                    cout << "You bombed the carrier! " << endl;
                    grid[row][col] = 1;
                    hit++;
                    boatList[0].setHit();
                    sunk = boatList[0].checkSunk(Carrier);
                    if (sunk == 9) {
                        cout << "You sunk the carrier." << endl;
                    }
                    break;
            }

            if (hit == 30) {
                gameInProgress = false;
            }
        }

        cout << "You sunk all the battleships in " << guess << " moves" << endl;

    }

    int getSpace(int grid[][10], int row, int col) {
        int space = 0;
        space = grid[row][col];
        return space;
    }
