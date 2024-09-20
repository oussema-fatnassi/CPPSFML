#include "LoadFromFile.hpp"

/*
Class definition for LoadFromFile, a class that loads a grid from a file and creates bricks from the grid.
*/

LoadFromFile::LoadFromFile(const string& path) : filePath(path) {
    // Initialize image paths
    imagePaths = {
        {1, "../assets/images/Grass.png"},
        {2, "../assets/images/Dirt.png"},
        {3, "../assets/images/Stone.png"},
        {4, "../assets/images/DeepSlate.png"},
        {5, "../assets/images/GoldOre.png"},
        {6, "../assets/images/Diamond.png"},
        {7, "../assets/images/Obsidian.png"},
        {8, "../assets/images/RubyOre.png"},
    };
}

// Load the grid from the file
void LoadFromFile::loadGrid() {
    // Open the file using the provided path
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return;
    }

    grid.clear();
    vector<int> row(SIZE, 0);
    vector<vector<int>> tempGrid(SIZE, row);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            file >> tempGrid[i][j];
        }
    }
    grid = tempGrid;
    file.close();
}

// Print the grid to the console
void LoadFromFile::printGrid() const {
    for (const auto& row : grid) {
        for (const auto& elem : row) {
            cout << elem << " | ";
        }
        cout << endl;
    }
}

// Get the image path for a given value
string LoadFromFile::getImagePath(int value) const {
    if (imagePaths.find(value) != imagePaths.end()) {
        return imagePaths.at(value);
    } else {
        return "default.png"; // Return a default image if the value is not found
    }
}

// Create a vector of bricks from the grid
vector<Brick> LoadFromFile::createBricks(SoundManager& soundManager) const {
    vector<Brick> bricks;
    const float brickWidth = 60.0f;
    const float brickHeight = 60.0f;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int value = grid[i][j];
            if (value != 0) {  // Assuming 0 means no brick
                float x = j * brickWidth;
                float y = i * brickHeight;
                sf::Vector2f position(x, y);
                sf::Vector2f dimension(brickWidth, brickHeight);
                string imagePath = getImagePath(value);
                Brick brick(position, dimension, imagePath, value, &soundManager);
                bricks.push_back(brick);
            }
        }
    }
    return bricks;
}
