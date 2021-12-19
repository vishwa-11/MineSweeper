//
// Created by Vishweshwar Ramanakumar on 4/16/21.
//

#include "Tile.h"

Tile::Tile(int X, int Y, int height, int width) {
    xCoordinate = X;
    yCoordinate = Y;
    neighborCount = 0;
    mineIndicator = 0;
    cleared = false;
}
