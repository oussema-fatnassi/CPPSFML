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

const int SIZE = 10;                                                    // Constants

class LoadFromFile {
public:
    LoadFromFile(const string& path);                                   // Constructor  
    void loadGrid();
    void printGrid() const;
    vector<Brick> createBricks(SoundManager& soundManager) const;

private:
    string getImagePath(int value) const;                               // Get the image path
    string filePath;                                                    // Member variables
    vector<vector<int>> grid;
    unordered_map<int, string> imagePaths;
};

#endif // LOADFROMFILE_HPP
