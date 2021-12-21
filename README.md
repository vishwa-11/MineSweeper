# The tile class contains specific behavior for each tile along with the values that each tile contains (mine, flag or empty).
# Additionally, the state of each tile determines the image used to cover it. There are images for selected squares, unselected squares,
# tiles with mines, tiles with flags and tiles with numbers. TextureManager helps facilitate the loading of each image file.
# Random helps to randomize the board at each setup. The board class is used to initiliaze the board. It also contains methods that dictate
# every facet of the boards behavior when it interacts with the user. When a user clicks on a square, there are methods that are executed
# depending on what the tile contains as pertaining to the rules of minesweeper. There are also 3 test boards that I included in order to see
# whether my board was functioning properly. The first board only contains one mine and is an extreme test case. The other two boards contain
# handwritten phrases. The main method essentially only runs methods from the board class since the board class contains methods from all the other
# present classes. 
