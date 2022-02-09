#include "Game/BaseBoard.h"

BaseBoard::BaseBoard() {
}

bool BaseBoard::canPlaceTile(int x, int y, int col){
    // If there is already a tile there, we can't place a new tile there
    if (state[x][y] != 0){
        return false;
    }

    // Set opCol to the opposite colour value from given colour
    int opCol = (col == 1) ? 2 : 1;
    int xPos, yPos;

    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            // We are not interested in not moving, aka slight optimisation
            if (dx == dy && dx == 0)
                continue;
            // At the very least direct neighbour has to be of opposite colour
            if (state[x+dx][y+dy] != opCol)
                continue;

            for (int z = 2; z < 8; z++){
                xPos = x+dx*z;
                yPos = y+dy*z;
                // Stop when we reach out-of-bounds
                if (xPos < 0 || yPos < 0 || xPos > 7 || yPos > 7)
                    break;

                // Gaps are not allowed
                if (state[xPos][yPos] == 0)
                    break;
                // If we find our colour after opCol without any gaps, the move is valid through at least this
                // direction, so we can stop checking further and just return true.
                if (state[xPos][yPos] == col)
                    return true;
            }
        }
    }

    return false;
}

void BaseBoard::placeTile(int x, int y, int col){
    state[x][y] = col;

    // Set opCol to the opposite colour value from given colour
    int opCol = (col == 1) ? 2 : 1;
    int xPos, yPos;

    for (int dx = -1; dx <= 1; dx++){
        for (int dy = -1; dy <= 1; dy++){
            // At the very least direct neighbour has to be of opposite colour
            if (state[x+dx][y+dy] != opCol)
                continue;

            for (int z = 2; z < 8; z++){
                xPos = x+dx*z;
                yPos = y+dy*z;
                // Stop when we reach out-of-bounds
                if (xPos < 0 || yPos < 0 || xPos > 7 || yPos > 7)
                    break;

                // Gaps are not allowed
                if (state[xPos][yPos] == 0)
                    break;
                // If we find our colour after opCol without any gaps, the move is valid through at least this
                // direction, so we can fill it now.
                if (state[xPos][yPos] == col) {
                    fillDirection(x,y,dx,dy,z,col);
                }
            }
        }
    }
}

void BaseBoard::fillDirection(int x, int y, int dx, int dy, int length, int col){
    for (int i = 1; i < length; i++){
        state[x+dx*i][y+dy*i] = col;
    }
}

void BaseBoard::resetBoard(){
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++) {
            state[x][y] = 0;
        }
    }
    // Starting position of any board
    state[3][3] = 1;
    state[4][4] = 1;
    state[3][4] = 2;
    state[4][3] = 2;
}