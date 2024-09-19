#include "LoadFromFile.hpp"

LoadFromFile::LoadFromFile(const string& path) : filePath(path) {
    // Initialize image paths
    imagePaths = {
        {1, "../assets/images/Dirt.png"},
        {2, "../assets/images/Stone.png"},
        {3, "../assets/images/GoldOre.png"},
        {4, "../assets/images/Diamond.png"},
        {5, "../assets/images/Obsidian.png"},
        {6, "../assets/images/RubyOre.png"},
        {7, "../assets/images/TNT.png"}
    };
}

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

void LoadFromFile::printGrid() const {
    for (const auto& row : grid) {
        for (const auto& elem : row) {
            cout << elem << " | ";
        }
        cout << endl;
    }
}

string LoadFromFile::getImagePath(int value) const {
    if (imagePaths.find(value) != imagePaths.end()) {
        return imagePaths.at(value);
    } else {
        return "default.png"; // Return a default image if the value is not found
    }
}

vector<Brick> LoadFromFile::createBricks() const {
    vector<Brick> bricks;
    const float brickWidth = 50.0f;
    const float brickHeight = 50.0f;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int value = grid[i][j];
            if (value != 0) {  // Assuming 0 means no brick
                float x = j * brickWidth;
                float y = i * brickHeight;
                sf::Vector2f position(x, y);
                sf::Vector2f dimension(brickWidth, brickHeight);
                string imagePath = getImagePath(value);
                Brick brick(position, dimension, imagePath, value);
                bricks.push_back(brick);
            }
        }
    }
    return bricks;
}
