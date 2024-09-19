#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

const int SIZE = 9;
vector<vector<int>> Grid;

// Load a grid from a file
void loadGridFromFileSimple() {
    const char* filename = "matrice.txt";

    // Open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    Grid.clear();

    // Read the grid from the file
    vector<int> row(SIZE, 0);
    vector<vector<int>> grid(SIZE, row);
    int gridCount = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            file >> grid[i][j];
        }
    }
    Grid = grid;
    file.close();
}

// Print the grid
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (const auto& elem : row) {
            cout << elem << " | ";
        }
        cout << endl;
    }
}

// Map image paths to values
unordered_map<int, string> imagePaths = {
    {0, "empty.png"},
    {1, "image1.png"},
    {2, "image2.png"},
    {3, "image3.png"},
    {4, "image4.png"},
    {5, "image5.png"},
    {6, "image6.png"},
    {7, "image7.png"},
    {8, "image8.png"},
    {9, "image9.png"}
};

// Get the image path for a value
string getImagePath(int value) {
    if (imagePaths.find(value) != imagePaths.end()) {
        return imagePaths[value];
    } else {
        return "default.png"; // Return a default image if the value is not found
    }
}

/*int main() {
    cout << "Hello, World!" << endl;
    loadGridFromFileSimple();
    printGrid(Grid);
    return 0;
}*/
