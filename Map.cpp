#include "Stronghold.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

Map::Map() : positionCount(0) {}

void Map::movePlayer(int playerId, int newX, int newY) {
    try {
        if (newX < 0 || newX >= 10 || newY < 0 || newY >= 10) {
            throw GameException("Map coordinates must be between 0 and 9!");
        }
        for (int i = 0; i < positionCount; i++) {
            if (positions[i].playerId == playerId) {
                positions[i].x = newX;
                positions[i].y = newY;
                cout << "Player " << playerId << " moved to (" << newX << ", " << newY << ").\n";
                saveMap();
                return;
            }
        }
        if (positionCount >= 10) {
            throw GameException("Map is full!");
        }
        positions[positionCount].playerId = playerId;
        positions[positionCount].x = newX;
        positions[positionCount].y = newY;
        positionCount++;
        cout << "Player " << playerId << " placed at (" << newX << ", " << newY << ").\n";
        saveMap();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

bool Map::isPositionOccupied(int x, int y) const {
    for (int i = 0; i < positionCount; i++) {
        if (positions[i].x == x && positions[i].y == y) {
            return true;
        }
    }
    return false;
}

void Map::displayMap() const {
    cout << "Map (10x10 Grid):\n";
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            bool occupied = false;
            for (int i = 0; i < positionCount; i++) {
                if (positions[i].x == x && positions[i].y == y) {
                    cout << "P" << positions[i].playerId;
                    occupied = true;
                    break;
                }
            }
            if (!occupied) {
                cout << "..";
            }
            cout << " ";
        }
        cout << "\n";
    }
}

void Map::saveMap() const {
    ofstream file("map.txt");
    if (file.is_open()) {
        for (int i = 0; i < positionCount; i++) {
            file << positions[i].playerId << " " << positions[i].x << " " << positions[i].y << "\n";
        }
        file.close();
    }
    else {
        cout << "Error: Unable to save map.\n";
    }
}

void Map::loadMap() {
    ifstream file("map.txt");
    positionCount = 0;
    if (file.is_open()) {
        while (file >> positions[positionCount].playerId >> positions[positionCount].x >> positions[positionCount].y && positionCount < 10) {
            positionCount++;
        }
        file.close();
    }
    else {
        cout << "Error: Unable to load map.\n";
    }
}