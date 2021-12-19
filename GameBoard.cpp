

//
// Created by Vishweshwar Ramanakumar on 4/16/21.
//

#include "GameBoard.h"
#include "Random.h"
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

GameBoard::GameBoard(string filePath) {
    ifstream file;
    file.open(filePath);
    string line;
    string line1;
    int Width = 0;
    int Height = 0;
    int mineNumber = 0;
    if (file.is_open()) {
        getline(file, line1);
        Width = stoi(line1);
        getline(file, line1);
        Height = stoi(line1);
        getline(file, line1);
        mineNumber = stoi(line1);
    }
    if (Width >= 22) {
        this->width = Width;
    } else {
        this->width = 22;
    }
    this->height = Height;
    if (mineNumber <= Height * Width) {
        this->mineCount = mineNumber;
    } else {
        this->mineCount = this->width * this->height;
    }


    for (int i = 0; i < this->width; i++) {
        vector<Tile> tiles;
        layout.push_back(tiles);
        for (int j = 0; j < this->height; j++) {
            Tile tile(i, j, this->width, this->height);
            layout[i].push_back(tile);
        }
    }

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
            layout[i][j].sprite2.setTexture(TextureManager::GetTexture("tile_hidden"));
            //layout[i][j].sprite3.setTexture(TextureManager::GetTexture("tile_hidden"));
            layout[i][j].sprite.setPosition(32 * i, 32 * j);
            layout[i][j].sprite2.setPosition(32 * i, 32 * j);
            //layout[i][j].sprite3.setPosition(32 * i, 32 * j);
            layout[i][j].mineIndicator = 0;
        }
    }


    gameOver = false;

}

void GameBoard::DrawBoard() {
    sf::RenderWindow window(sf::VideoMode(32 * width, 32 * height + 88), "Minesweeper");


    face.setTexture(TextureManager::GetTexture("face_happy"));
    face.setPosition((width - 1) * 16, height * 32);



    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition((width - 1) * 16 + 2 * (64), height * 32);

    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setPosition((width - 1) * 16 + 3 * (64), height * 32);

    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setPosition((width - 1) * 16 + 4 * (64), height * 32);

    test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.setPosition((width - 1) * 16 + 5 * (64), height * 32);


    while (window.isOpen()) {
        sf::Event event;

        sf::Vector2i mousepos = sf::Mouse::getPosition(window);
        auto faceBounds = face.getGlobalBounds();
        auto debugBounds = debug.getGlobalBounds();
        auto test1Bounds = test1.getGlobalBounds();
        auto test2Bounds = test2.getGlobalBounds();
        auto test3Bounds = test3.getGlobalBounds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (debugBounds.contains(mousepos.x, mousepos.y)) {

                        if (debugMode) {
                            for (int i = 0; i < width; i++) {
                                for (int j = 0; j < height; j++) {
                                    if (layout[i][j].mineIndicator == 1) {
                                        layout[i][j].sprite6.setTexture(TextureManager::GetTexture("tile_hidden"));
                                        layout[i][j].sprite6.setPosition(i * 32, j * 32);
                                        layout[i][j].sprite7.setTexture(TextureManager::GetTexture("tile_hidden"));
                                        layout[i][j].sprite7.setPosition(i * 32, j * 32);
                                    }
                                }
                            }
                            debugMode = false;
                        }
                        else {
                            for (int i = 0; i < width; i++) {
                                for (int j = 0; j < height; j++) {
                                    if (layout[i][j].mineIndicator == 1) {
                                        layout[i][j].sprite6.setTexture(TextureManager::GetTexture("tile_hidden"));
                                        layout[i][j].sprite6.setPosition(i * 32, j * 32);
                                        layout[i][j].sprite7.setTexture(TextureManager::GetTexture("mine"));
                                        layout[i][j].sprite7.setPosition(i * 32, j * 32);
                                    }
                                }
                            }
                            debugMode = true;
                        }

                    }
                    if (sf::Mouse::getPosition(window).x > ((width - 1) * 16) && sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 64) && sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
                        this->ResetBoard();
                        this->SetMines();
                        this->SetNeighbors();
                    }
                    if (sf::Mouse::getPosition(window).x > ((width - 1) * 16 + 3 * 64) && sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 4 * 64) && sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
                        this->ResetBoard();
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        this->Test1();
                    }
                    if (sf::Mouse::getPosition(window).x > ((width - 1) * 16 + 4 * 64) && sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 5 * 64) && sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
                        this->ResetBoard();
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        this->Test2();
                    }
                    if (sf::Mouse::getPosition(window).x > ((width - 1) * 16 + 5 * 64) && sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 6 * 64) && sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
                        this->ResetBoard();
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        this->Test3();
                    }

                }
                //event.mouseButton.button = sf::Mouse::Right;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    for (int i = 0; i < width; i++) {
                        for (int j = 0; j < height; j++) {
                            if (sf::Mouse::getPosition(window).x > (i * 32) && sf::Mouse::getPosition(window).x < ((i + 1) * 32) && sf::Mouse::getPosition(window).y > (j * 32) && sf::Mouse::getPosition(window).y < ((j + 1) * 32)) {
                                if (layout[i][j].flagIndicator == 0) {
                                    flagCount++;
                                    layout[i][j].flagIndicator = 1;
                                }
                                else if (layout[i][j].flagIndicator == 1) {
                                    flagCount--;
                                    layout[i][j].flagIndicator = 0;
                                }

                            }

                        }
                    }
                }
            }

        }


        window.clear();



        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {

                window.draw(layout[i][j].sprite);
                window.draw(layout[i][j].sprite2);
                window.draw(layout[i][j].sprite3);
                if (!debugMode && layout[i][j].mineIndicator == 1 && !gameOver) {
                    layout[i][j].sprite6.setTexture(TextureManager::GetTexture("tile_hidden"));
                    layout[i][j].sprite7.setTexture(TextureManager::GetTexture("mine"));
                    window.draw(layout[i][j].sprite6);
                    window.draw(layout[i][j].sprite7);
                }
                else if (debugMode && layout[i][j].mineIndicator == 1 && !gameOver) {
                    layout[i][j].sprite6.setTexture(TextureManager::GetTexture("tile_hidden"));
                    layout[i][j].sprite7.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i][j].sprite6);
                    window.draw(layout[i][j].sprite7);
                }
                if (layout[i][j].flagIndicator == 1) {
                    layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    layout[i][j].sprite6.setTexture(TextureManager::GetTexture("flag"));
                    layout[i][j].sprite6.setPosition(i * 32, j * 32);
                    window.draw(layout[i][j].sprite);
                    window.draw(layout[i][j].sprite6);
                }
            }
        }



        this->Click(window);
        this->Test1Click(window);
        this->Test2Click(window);
        this->Test3Click(window);





        int count = mineCount - flagCount;

        window.draw(face);
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        if (this->CheckGameStatus(window)) {
            count = 0;
            face.setTexture(TextureManager::GetTexture("face_win"));
            window.draw(face);
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    if (layout[i][j].mineIndicator == 1) {
                        layout[i][j].sprite2.setTexture(TextureManager::GetTexture("tile_hidden"));
                        window.draw(layout[i][j].sprite2);
                        layout[i][j].sprite3.setTexture(TextureManager::GetTexture("flag"));
                        flagCount++;
                        layout[i][j].sprite3.setPosition(i * 32, j * 32);
                        window.draw(layout[i][j].sprite3);
                    }
                }
            }

        }

        /*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (sf::Mouse::getPosition(window).x > ((width - 1) * 16) && sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 64) && sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
                this->ResetBoard();
                this->SetMines();
                this->SetNeighbors();
            }
        }*/

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (sf::Mouse::getPosition(window).x > ((width - 1) * 16) && sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 64) && sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
                this->ResetBoard();
                this->SetMines();
                this->SetNeighbors();
                face.setTexture(TextureManager::GetTexture("face_happy"));
                gameOver = false;
            }
        }





        if (count < 0) {
            for (int i = 0; i < 5; i++) {
                window.draw(this->SetDigit(count, i));
            }
        }

        else {
            for (int i = 0; i < 4; i++) {
                window.draw(this->SetDigit(count, i));
            }
        }
        window.display();


    }




}

void GameBoard::SetNeighbors() {

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (j != 0 && i != 0) {
                if (layout[i - 1][j - 1].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
            if (j != 0) {
                if (layout[i][j - 1].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
            if (j != 0 && i != width - 1) {
                if (layout[i + 1][j - 1].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
            if (i != 0) {
                if (layout[i - 1][j].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
            if (i != width - 1) {
                if (layout[i + 1][j].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
            if (j != height - 1 && i != 0) {
                if (layout[i - 1][j + 1].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
            if (j != height - 1) {
                if (layout[i][j + 1].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
            if (j != height - 1 && i != width - 1) {
                if (layout[i + 1][j + 1].mineIndicator == 1) {
                    layout[i][j].neighborCount++;
                }
            }
        }
    }
}

void GameBoard::SetMines() {
    int limit = mineCount / height;
    int count = 0;
    int totalCount = 0;

    int side = Random::Int(0, 1);

    if (side == 0) {
        for (int j = 0; j < height - 1; j += 2) {
            for (int i = 0; i < width; i++) {
                if (count == limit) {
                    layout[i][j].mineIndicator = 0;
                }
                else {
                    layout[i][j].mineIndicator = Random::Int(0, 1);
                    if (layout[i][j].mineIndicator == 1) {
                        count++;
                        totalCount++;
                    }
                }
            }
            count = 0;
        }
    }
    else if (side == 1) {
        for (int j = 0; j < height - 1; j += 2) {
            for (int i = width - 1; i >= 0; i--) {
                if (count < limit) {
                    layout[i][j].mineIndicator = Random::Int(0, 1);
                    if (layout[i][j].mineIndicator == 1) {
                        count++;
                        totalCount++;
                    }
                }
                else {
                    layout[i][j].mineIndicator = 0;
                }
            }
            count = 0;
        }
    }

    side = Random::Int(0, 1);

    if (side == 0) {
        for (int j = 1; j < height - 1; j += 2) {
            for (int i = 0; i < width; i++) {
                if (count == limit) {
                    layout[i][j].mineIndicator = 0;
                }
                else {
                    layout[i][j].mineIndicator = Random::Int(0, 1);
                    if (layout[i][j].mineIndicator == 1) {
                        count++;
                        totalCount++;
                    }
                }
            }
            count = 0;
        }
    }
    else {
        for (int j = 1; j < height - 1; j += 2) {
            for (int i = width - 1; i >= 0; i--) {
                if (count < limit) {
                    layout[i][j].mineIndicator = Random::Int(0, 1);
                    if (layout[i][j].mineIndicator == 1) {
                        count++;
                        totalCount++;
                    }
                }
                else {
                    layout[i][j].mineIndicator = 0;
                }
            }
            count = 0;
        }
    }
    count = 0;

    for (int i = 0; i < width; i++) {
        if (totalCount == mineCount) {
            layout[i][height - 1].mineIndicator = 0;
        }
        else {
            layout[i][height - 1].mineIndicator = Random::Int(0, 1);
            if (layout[i][height - 1].mineIndicator == 1) {
                count++;
                totalCount++;
            }
        }

    }
}

void GameBoard::ResetBoard() {
    gameOver = false;
    debugMode = true;
    flagCount = 0;
    layout.clear();

    ifstream file;
    file.open("boards/config.cfg");
    string line;
    string line1;
    int Width = 0;
    int Height = 0;
    int mineNumber = 0;
    if (file.is_open()) {
        getline(file, line1);
        Width = stoi(line1);
        getline(file, line1);
        Height = stoi(line1);
        getline(file, line1);
        mineNumber = stoi(line1);
    }
    if (Width >= 22) {
        this->width = Width;
    } else {
        this->width = 22;
    }
    this->height = Height;
    if (mineNumber <= Height * Width) {
        this->mineCount = mineNumber;
    } else {
        this->mineCount = this->width * this->height;
    }

    for (int i = 0; i < this->width; i++) {
        vector<Tile> tiles;
        layout.push_back(tiles);
        for (int j = 0; j < this->height; j++) {
            Tile tile(i, j, this->width, this->height);
            layout[i].push_back(tile);
        }
    }

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
            layout[i][j].sprite2.setTexture(TextureManager::GetTexture("tile_hidden"));
            //layout[i][j].sprite3.setTexture(TextureManager::GetTexture("tile_hidden"));

            layout[i][j].sprite.setPosition(32 * i, 32 * j);
            layout[i][j].sprite2.setPosition(32 * i, 32 * j);
            //layout[i][j].sprite3.setPosition(32 * i, 32 * j);
            layout[i][j].mineIndicator = 0;

        }
    }

}

void GameBoard::Test1() {
    this->ResetBoard();
    ifstream file1;
    file1.open("boards/testboard1.brd");
    string line;
    char line1[width];
    int count = mineCount;
    mineCount = 0;

    for (int j = 0; j < height; j++) {
        getline(file1, line);
        strcpy(line1, line.c_str());
        for (int i = 0; i < width; i++) {
            layout[i][j].mineIndicator = line1[i] - '0';
            if (layout[i][j].mineIndicator == 1) {
                mineCount++;
            }
            //cout << (layout[i][j].mineIndicator);

        }
        //cout << endl;
    }



    //cout << mineCount << endl;
    //cout << totalCount;



    file1.close();
    this->SetNeighbors();
    /*this->DrawBoard();
    mineCount = count;
    this->ResetBoard();*/
}

void GameBoard::Test2() {
    this->ResetBoard();

    ifstream file1;
    file1.open("boards/testboard2.brd");
    string line;
    char line1[width];
    int count = mineCount;

    mineCount = 0;
    for (int j = 0; j < height; j++) {
        getline(file1, line);
        strcpy(line1, line.c_str());
        for (int i = 0; i < width; i++) {
            layout[i][j].mineIndicator = line1[i] - '0';
            if (layout[i][j].mineIndicator == 1) {
                mineCount++;
            }
            //cout << (layout[i][j].mineIndicator);

        }
        //cout << endl;
    }



    //cout << mineCount << endl;
    //cout << totalCount;



    file1.close();

    this->SetNeighbors();


    /*this->DrawBoard();

    mineCount = count;
    this->ResetBoard();*/
}

void GameBoard::Test3() {
    this->ResetBoard();
    ifstream file1;
    file1.open("boards/testboard3.brd");
    string line;
    char line1[width];
    int count = mineCount;
    mineCount = 0;

    for (int j = 0; j < height; j++) {
        getline(file1, line);
        strcpy(line1, line.c_str());
        for (int i = 0; i < width; i++) {
            layout[i][j].mineIndicator = line1[i] - '0';
            if (layout[i][j].mineIndicator == 1) {
                mineCount++;
            }
            //cout << (layout[i][j].mineIndicator);
        }
        //cout << endl;
    }
    //cout << mineCount << endl;
    //cout << totalCount;
    file1.close();

    this->SetNeighbors();
    /*
     * this->DrawBoard();
    mineCount = count;
    this->ResetBoard();*/
}

sf::Sprite GameBoard::SetDigit(int count, int j) {


    if (count < 0) {
        sf::Sprite digit[5];
        int counter[5];
        counter[0] = -1;
        count = abs(count);
        counter[1] = count / 100;
        counter[2] = (count % 100) / 10;
        counter[3] = count - (100 * counter[1]) - (10 * counter[2]);
        counter[4] = 5;
        digit[4].setTexture(TextureManager::GetTexture("digits"));
        digit[4].setTextureRect(sf::IntRect(21, 0, 8, 32));
        digit[4].setPosition(84, height * 32);

        for (int i = 0; i < 4; i++) {
            digit[i].setTexture(TextureManager::GetTexture("digits"));
            if (counter[i] == -1) {
                digit[i].setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
            }

            else if (counter[i] == 0) {
                digit[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
            }
            else if (counter[i] == 1) {
                digit[i].setTextureRect(sf::IntRect(21 * 1, 0, 21, 32));
            }
            else if (counter[i] == 2) {
                digit[i].setTextureRect(sf::IntRect(21 * 2, 0, 21, 32));
            }
            else if (counter[i] == 3) {
                digit[i].setTextureRect(sf::IntRect(21 * 3, 0, 21, 32));

            }
            else if (counter[i] == 4) {
                digit[i].setTextureRect(sf::IntRect(21 * 4, 0, 21, 32));

            }
            else if (counter[i] == 5) {
                digit[i].setTextureRect(sf::IntRect(21 * 5, 0, 21, 32));

            }
            else if (counter[i] == 6) {
                digit[i].setTextureRect(sf::IntRect(21 * 6, 0, 21, 32));
            }
            else if (counter[i] == 7) {
                digit[i].setTextureRect(sf::IntRect(21 * 7, 0, 21, 32));

            }
            else if (counter[i] == 8) {
                digit[i].setTextureRect(sf::IntRect(21 * 8, 0, 21, 32));

            }
            else if (counter[i] == 9) {
                digit[i].setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));

            }
            digit[i].setPosition(21 * (i), height * 32);

        }
        return digit[j];
    }

    else {
        sf::Sprite digit[4];
        int counter[4];
        counter[0] = count / 100;
        counter[1] = (count % 100) / 10;
        counter[2] = count - (100 * counter[0]) - (10 * counter[1]);
        counter[3] = 5;
        digit[3].setTexture(TextureManager::GetTexture("digits"));
        digit[3].setTextureRect(sf::IntRect(21, 0, 8, 32));
        digit[3].setPosition(84, height * 32);

        for (int i = 0; i < 3; i++) {
            digit[i].setTexture(TextureManager::GetTexture("digits"));
            if (counter[i] == 0) {
                digit[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
            }
            else if (counter[i] == 1) {
                digit[i].setTextureRect(sf::IntRect(21 * 1, 0, 21, 32));
            }
            else if (counter[i] == 2) {
                digit[i].setTextureRect(sf::IntRect(21 * 2, 0, 21, 32));
            }
            else if (counter[i] == 3) {
                digit[i].setTextureRect(sf::IntRect(21 * 3, 0, 21, 32));

            }
            else if (counter[i] == 4) {
                digit[i].setTextureRect(sf::IntRect(21 * 4, 0, 21, 32));

            }
            else if (counter[i] == 5) {
                digit[i].setTextureRect(sf::IntRect(21 * 5, 0, 21, 32));

            }
            else if (counter[i] == 6) {
                digit[i].setTextureRect(sf::IntRect(21 * 6, 0, 21, 32));
            }
            else if (counter[i] == 7) {
                digit[i].setTextureRect(sf::IntRect(21 * 7, 0, 21, 32));

            }
            else if (counter[i] == 8) {
                digit[i].setTextureRect(sf::IntRect(21 * 8, 0, 21, 32));

            }
            else if (counter[i] == 9) {
                digit[i].setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));

            }
            digit[i].setPosition(21 * (i + 1), height * 32);

        }
        return digit[j];
    }






}

void GameBoard::Click(sf::RenderWindow &window) {
    int count = mineCount;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                if (sf::Mouse::getPosition(window).x > (i * 32) && sf::Mouse::getPosition(window).x < ((i + 1) * 32) && sf::Mouse::getPosition(window).y > (j * 32) && sf::Mouse::getPosition(window).y < ((j + 1) * 32)) {

                    if (layout[i][j].mineIndicator == 1) {
                        if (layout[i][j].flagIndicator == 0) {
                            for (int a = 0; a < width; a++) {
                                for (int b = 0; b < width; b++) {
                                    if (layout[a][b].mineIndicator == 1) {
                                        layout[a][b].sprite2.setTexture(TextureManager::GetTexture("mine"));
                                        layout[a][b].sprite2.setPosition(a * 32, b * 32);
                                        window.draw(layout[a][b].sprite2);
                                        layout[a][b].cleared = true;
                                    }
                                }
                            }
                            gameOver = true;
                            break;
                        }
                        else {
                            layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                            window.draw(layout[i][j].sprite);
                            layout[i][j].sprite3.setTexture(TextureManager::GetTexture("flag"));
                            window.draw(layout[i][j].sprite3);
                        }


                    }
                    else {
                        if (layout[i][j].neighborCount == 0) {
                            if (layout[i][j].flagIndicator == 0) {
                                layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
                                layout[i][j].sprite.setPosition(i * 32, j * 32);
                                window.draw(layout[i][j].sprite);
                                layout[i][j].sprite2.setTexture(TextureManager::GetTexture("tile_revealed"));
                                layout[i][j].sprite2.setPosition(i * 32, j * 32);
                                window.draw(layout[i][j].sprite2);
                                RecursiveReveal(i, j);
                            }
                            else {
                                layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                                window.draw(layout[i][j].sprite);
                                layout[i][j].sprite3.setTexture(TextureManager::GetTexture("flag"));
                                window.draw(layout[i][j].sprite3);
                            }

                        }
                        if (layout[i][j].flagIndicator == 0) {
                            this->NumberDrawer(window, i, j);
                        }
                        else {
                            layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                            window.draw(layout[i][j].sprite);
                            layout[i][j].sprite3.setTexture(TextureManager::GetTexture("flag"));
                            window.draw(layout[i][j].sprite3);
                        }
                    }
                }

            }
            if (gameOver) {
                break;
            }
        }


        if (gameOver) {
            face.setTexture(TextureManager::GetTexture("face_lose"));
            face.setPosition((width - 1) * 16, height * 32);
            window.draw(face);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (sf::Mouse::getPosition(window).x > ((width - 1) * 16) && sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 64) && sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
                    this->ResetBoard();
                    this->SetMines();
                    this->SetNeighbors();
                    face.setTexture(TextureManager::GetTexture("face_happy"));
                    gameOver = false;
                }
            }
        }
    }

}

void GameBoard::RecursiveReveal(int i, int j) {

    if (layout[i][j].cleared || layout[i][j].neighborCount != 0 || layout[i][j].mineIndicator == 1) {
        return;
    }
    else {
        layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
        layout[i][j].sprite.setPosition(i * 32, j * 32);
        window.draw(layout[i][j].sprite);
        layout[i][j].sprite2.setTexture(TextureManager::GetTexture("tile_revealed"));
        layout[i][j].sprite2.setPosition(i * 32, j * 32);
        window.draw(layout[i][j].sprite2);
        layout[i][j].cleared = true;

        if (j != 0 && i != 0) {
            if (layout[i - 1][j - 1].neighborCount == 0 && !layout[i - 1][j - 1].cleared) {
                RecursiveReveal(i - 1, j - 1);
            }
            else if (layout[i - 1][j - 1].mineIndicator == 1) {
                if (!debugMode) {
                    layout[i - 1][j - 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i - 1][j - 1].sprite);
                }

            }
            else if (layout[i - 1][j - 1].flagIndicator == 1) {
                layout[i - 1][j - 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i - 1][j - 1].sprite);
                layout[i - 1][j - 1].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i - 1][j - 1].sprite3);
                layout[i - 1][j - 1].cleared = false;
            }
            else {
                this->NumberDrawer(window, i - 1, j - 1);
                //break;
            }
        }
        if (j != 0) {
            if (layout[i][j - 1].neighborCount == 0 && !layout[i][j - 1].cleared) {
                RecursiveReveal(i, j - 1);
            }
            else if (layout[i][j - 1].mineIndicator == 1) {
                if (!debugMode) {
                    layout[i][j - 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i][j - 1].sprite);
                }
            }
            else if (layout[i][j - 1].flagIndicator == 1) {
                layout[i][j - 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i][j - 1].sprite);
                layout[i][j - 1].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i][j - 1].sprite3);
                layout[i][j - 1].cleared = false;

            }
            else {
                this->NumberDrawer(window, i, j - 1);
                //break;
            }
        }

        if (j != 0 && i != width - 1) {
            if (layout[i + 1][j - 1].neighborCount == 0 && !layout[i + 1][j - 1].cleared) {
                RecursiveReveal(i + 1, j - 1);
            }
            else if (layout[i + 1][j - 1].mineIndicator == 1 && !debugMode) {
                if (!debugMode) {
                    layout[i + 1][j - 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i + 1][j - 1].sprite);
                }

            }
            else if (layout[i + 1][j - 1].flagIndicator == 1) {
                layout[i + 1][j - 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i + 1][j - 1].sprite);
                layout[i + 1][j - 1].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i + 1][j - 1].sprite3);
                layout[i + 1][j - 1].cleared = false;

            }
            else {
                this->NumberDrawer(window, i + 1, j - 1);
                //break;
            }
        }

        if (i != 0) {
            if (layout[i - 1][j].neighborCount == 0 && !layout[i - 1][j].cleared) {
                RecursiveReveal(i - 1, j);
            }
            else if (layout[i - 1][j].mineIndicator == 1) {
                if (!debugMode) {
                    layout[i - 1][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i - 1][j].sprite);
                }

            }
            else if (layout[i - 1][j].flagIndicator == 1) {
                layout[i - 1][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i - 1][j].sprite);
                layout[i - 1][j].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i - 1][j].sprite3);
                layout[i - 1][j].cleared = false;

            }
            else {
                this->NumberDrawer(window, i - 1, j);
                //break;
            }
        }

        if (i != width - 1) {
            if (layout[i + 1][j].neighborCount == 0 && !layout[i + 1][j].cleared) {
                RecursiveReveal(i + 1, j);
            }
            else if (layout[i + 1][j].mineIndicator == 1) {
                if (!debugMode) {
                    layout[i + 1][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i + 1][j].sprite);
                }

            }
            else if (layout[i + 1][j].flagIndicator == 1) {
                layout[i + 1][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i + 1][j].sprite);
                layout[i + 1][j].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i + 1][j].sprite3);
                layout[i + 1][j].cleared = false;

            }
            else {
                this->NumberDrawer(window, i + 1, j);
                //break;
            }
        }

        if (j != height - 1 && i != 0) {
            if (layout[i - 1][j + 1].neighborCount == 0 && !layout[i - 1][j + 1].cleared) {
                RecursiveReveal(i - 1, j + 1);
            }
            else if (layout[i - 1][j + 1].mineIndicator == 1) {
                if (!debugMode) {
                    layout[i - 1][j + 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i - 1][j + 1].sprite);
                }

            }
            else if (layout[i - 1][j + 1].flagIndicator == 1) {
                layout[i - 1][j + 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i - 1][j + 1].sprite);
                layout[i - 1][j + 1].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i - 1][j + 1].sprite3);
                layout[i - 1][j + 1].cleared = false;

            }
            else {
                this->NumberDrawer(window, i - 1, j + 1);
                //break;
            }
        }
        if (j != height - 1) {
            if (layout[i][j + 1].neighborCount == 0 && !layout[i][j + 1].cleared) {
                RecursiveReveal(i, j + 1);
            }
            else if (layout[i][j + 1].mineIndicator == 1) {
                layout[i][j + 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i][j + 1].sprite);

            }
            else if (layout[i][j + 1].flagIndicator == 1) {
                layout[i][j + 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i][j + 1].sprite);
                layout[i][j + 1].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i][j + 1].sprite3);
                layout[i][j + 1].cleared = false;

            }
            else {
                this->NumberDrawer(window, i, j + 1);
                //break;
            }
        }

        if (j != height - 1 && i != width - 1) {
            if (layout[i + 1][j + 1].neighborCount == 0 && !layout[i + 1][j + 1].cleared) {
                RecursiveReveal(i + 1, j + 1);
            }
            else if (layout[i + 1][j + 1].mineIndicator == 1) {
                if (!debugMode) {
                    layout[i + 1][j + 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                    window.draw(layout[i + 1][j + 1].sprite);
                }

            }
            else if (layout[i + 1][j + 1].flagIndicator == 1) {
                layout[i + 1][j + 1].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                window.draw(layout[i + 1][j + 1].sprite);
                layout[i + 1][j + 1].sprite3.setTexture(TextureManager::GetTexture("flag"));
                window.draw(layout[i + 1][j + 1].sprite3);
                layout[i + 1][j + 1].cleared = false;

            }
            else {
                this->NumberDrawer(window, i + 1, j + 1);
                //break;
            }
        }





    }

}

void GameBoard::NumberDrawer(sf::RenderWindow &window, int i, int j) {
    for (int k = 1; k < 9; k++) {
        if (layout[i][j].neighborCount == k) {
            layout[i][j].sprite2.setTexture(TextureManager::GetTexture("number_" + to_string(k)));
            layout[i][j].sprite2.setPosition(i * 32, j * 32);
            window.draw(layout[i][j].sprite2);
            layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_revealed"));
            layout[i][j].sprite.setPosition(i * 32, j * 32);
            window.draw(layout[i][j].sprite);
            layout[i][j].cleared = true;
            break;
        }
    }
}

void GameBoard::DebugClick(sf::RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (sf::Mouse::getPosition(window).x > ((width - 1) * 16 + 2 * (64)) &&
            sf::Mouse::getPosition(window).x < ((width - 1) * 16 + 3 * (64)) &&
                                               sf::Mouse::getPosition(window).y > (height * 32) && sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
            if (debugMode) {
                for (int i = 0; i < width; i++) {
                    for (int j = 0; j < height; j++) {
                        if (layout[i][j].mineIndicator == 1) {
                            layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                            layout[i][j].sprite.setPosition(i * 32, j * 32);
                            window.draw(layout[i][j].sprite);
                            layout[i][j].sprite2.setTexture(TextureManager::GetTexture("tile_hidden"));
                            layout[i][j].sprite2.setPosition(i * 32, j * 32);
                            window.draw(layout[i][j].sprite2);
                        }
                    }
                }
                debugMode = false;
            }
            else {
                for (int i = 0; i < width; i++) {
                    for (int j = 0; j < height; j++) {
                        if (layout[i][j].mineIndicator == 1) {
                            layout[i][j].sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
                            layout[i][j].sprite.setPosition(i * 32, j * 32);
                            window.draw(layout[i][j].sprite);
                            layout[i][j].sprite2.setTexture(TextureManager::GetTexture("mine"));
                            layout[i][j].sprite2.setPosition(i * 32, j * 32);
                            window.draw(layout[i][j].sprite2);
                        }
                    }
                }
                debugMode = true;
            }
        }
    }
}


bool GameBoard::CheckGameStatus(sf::RenderWindow &window) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (layout[i][j].cleared && layout[i][j].mineIndicator == 0) {
                continue;
            }
            else if (layout[i][j].mineIndicator == 1) {
                continue;
            }
            else if (!layout[i][j].cleared && layout[i][j].mineIndicator == 0) {
                return false;
            }
        }
    }
    gameOver = true;
    return true;
}

void GameBoard::Test1Click(sf::RenderWindow &window) {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (sf::Mouse::getPosition(window).x > ((width - 1) * 16 + 3 * (64)) &&
            sf::Mouse::getPosition(window).x<((width - 1) * 16 + 4 * (64)) &&
                                             sf::Mouse::getPosition(window).y>(height * 32) &&
            sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
            this->Test1();
        }

    }
}

void GameBoard::Test2Click(sf::RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (sf::Mouse::getPosition(window).x > ((width - 1) * 16 + 4 * (64)) &&
            sf::Mouse::getPosition(window).x<((width - 1) * 16 + 5 * (64)) &&
                                             sf::Mouse::getPosition(window).y>(height * 32) &&
            sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
            this->Test2();
        }

    }
}

void GameBoard::Test3Click(sf::RenderWindow &window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (sf::Mouse::getPosition(window).x > ((width - 1) * 16 + 5 * (64)) &&
            sf::Mouse::getPosition(window).x<((width - 1) * 16 + 6 * (64)) &&
                                             sf::Mouse::getPosition(window).y>(height * 32) &&
            sf::Mouse::getPosition(window).y < (height * 32 + 64)) {
            this->Test3();
        }

    }
}

