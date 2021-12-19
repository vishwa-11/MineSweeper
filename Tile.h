//
// Created by Vishweshwar Ramanakumar on 4/16/21.
//

#ifndef PROJECT3_TILE_H
#define PROJECT3_TILE_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class Tile {

public:
    int mineIndicator = 0;
    int flagIndicator = 0;
    bool cleared;
    sf::Sprite sprite;
    sf::Sprite sprite2;
    sf::Sprite sprite3;
    sf::Sprite sprite4;
    sf::Sprite sprite5;
    sf::Sprite sprite6;
    sf::Sprite sprite7;

    bool debugged;

    int neighborCount = 0;
    int xCoordinate = 0;
    int yCoordinate = 0;
    Tile(int X, int Y, int height, int width);
};


#endif //PROJECT3_TILE_H