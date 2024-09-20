#ifndef LOADFROMFILE_HPP
#define LOADFROMFILE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "SoundManager.hpp"
#include "Brick.hpp"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Constants
const int SIZE = 10;

class LoadFromFile {
public:
    // Constructor
    LoadFromFile(const string& path);

    // Load a grid from the file
    void loadGrid();

    // Print the grid
    void printGrid() const;

    // Create a vector of bricks from the grid
    vector<Brick> createBricks(SoundManager& soundManager) const;

private:
    // Helper function to get the image path for a value
    string getImagePath(int value) const;

    // Member variables
    string filePath;
    vector<vector<int>> grid;
    unordered_map<int, string> imagePaths;
};

#endif // LOADFROMFILE_HPP
