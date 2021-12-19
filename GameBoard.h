//
// Created by Vishweshwar Ramanakumar on 4/16/21.
//

#ifndef PROJECT3_GAMEBOARD_H
#define PROJECT3_GAMEBOARD_H
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TextureManager.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <array>
using std::unordered_map;
using std::string;
using namespace std;


class GameBoard {
public:
    GameBoard(string filePath);
    void SetNeighbors();
    void SetMines();
    void DrawBoard();
    void ResetBoard();
    void Test1();
    void Test2();
    void Test3();
    sf::Sprite SetDigit(int count, int j);
    void Click(sf::RenderWindow &window);
    void DebugClick(sf::RenderWindow &window);
    void Test1Click(sf::RenderWindow &window);
    void Test2Click(sf::RenderWindow &window);
    void Test3Click(sf::RenderWindow &window);
    void RecursiveReveal(int i, int j);
    void NumberDrawer(sf::RenderWindow &window, int i, int j);
    bool CheckGameStatus(sf::RenderWindow &window);
    int width = 22;
    int height = 0;
    int mineCount = 0;
    int actualCount = 0;
    int flagCount = 0;
    bool gameOver = false;
    bool test1Mode;
    bool test2Mode;
    bool test3Mode;

    vector<vector<Tile>> layout;
    sf::RenderWindow window;
    sf::Sprite face;
    sf::Sprite debug;
    sf::Sprite test1;
    sf::Sprite test2;
    sf::Sprite test3;
    bool debugMode = true;


};


#endif //PROJECT3_GAMEBOARD_H