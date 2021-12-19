#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include "GameBoard.h"
using namespace std;



int main() {


    GameBoard gameboard("boards/config.cfg");


    gameboard.SetMines();

    gameboard.SetNeighbors();

    gameboard.DrawBoard();

    //gameboard.ResetBoard();

    //gameboard.Test2();





    return 0;
}
