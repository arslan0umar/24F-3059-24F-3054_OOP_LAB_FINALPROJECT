#include "Stronghold.h"
#include <iostream>
#include <string>
using namespace std;

ResourceManager::ResourceManager() : resourceCount(0) {
    resourceNames[0] = "Food";
    resourceValues[0] = 100;
    resourceNames[1] = "Gold";
    resourceValues[1] = 50;
    resourceNames[2] = "Wood";
    resourceValues[2] = 80;
    resourceNames[3] = "Stone";
    resourceValues[3] = 60;
    resourceNames[4] = "Iron";
    resourceValues[4] = 30;
    resourceCount = 5;
}

int ResourceManager::findResourceIndex(const string& name) const {
    for (int i = 0; i < resourceCount; i++) {
        if (resourceNames[i] == name) {
            return i;
        }
    }
    return -1;
}

void ResourceManager::gather(string resource, int amount, int playerId) {
    try {
        if (amount <= 0) {
            throw GameException("Cannot gather negative or zero amount of " + resource + "!");
        }
        int index = findResourceIndex(resource);
        if (index == -1) {
            if (resourceCount >= 10) {
                throw GameException("Resource storage is full!");
            }
            resourceNames[resourceCount] = resource;
            resourceValues[resourceCount] = amount;
            resourceCount++;
            cout << "Player " << playerId << " added new resource " << resource << " with " << amount << " units.\n";
        }
        else {
            resourceValues[index] += amount;
            cout << "Player " << playerId << " gathered " << amount << " units of " << resource << ". Total: " << resourceValues[index] << "\n";
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void ResourceManager::consume(string resource, int amount, int playerId) {
    try {
        if (amount <= 0) {
            throw GameException("Cannot consume negative or zero amount of " + resource + "!");
        }
        int index = findResourceIndex(resource);
        if (index == -1) {
            throw GameException("Resource " + resource + " not found!");
        }
        if (resourceValues[index] < amount) {
            throw GameException("Not enough " + resource + " to consume! Available: " + to_string(resourceValues[index]));
        }
        resourceValues[index] -= amount;
        cout << "Player " << playerId << " consumed " << amount << " units of " << resource << ". Remaining: " << resourceValues[index] << "\n";
        if (resourceValues[index] == 0) {
            for (int i = index; i < resourceCount - 1; i++) {
                resourceNames[i] = resourceNames[i + 1];
                resourceValues[i] = resourceValues[i + 1];
            }
            resourceCount--;
            cout << "Player " << playerId << ": " << resource << " has been fully depleted and removed.\n";
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void ResourceManager::trade(string from, string to, int rate) {
    try {
        if (rate <= 0) {
            throw GameException("Trade rate must be positive!");
        }
        int fromIndex = findResourceIndex(from);
        int toIndex = findResourceIndex(to);
        if (fromIndex == -1) {
            throw GameException("Resource " + from + " not found!");
        }
        if (resourceValues[fromIndex] < rate) {
            throw GameException("Not enough " + from + " to trade! Available: " + to_string(resourceValues[fromIndex]));
        }
        resourceValues[fromIndex] -= rate;
        if (toIndex == -1) {
            if (resourceCount >= 10) {
                throw GameException("Resource storage is full!");
            }
            resourceNames[resourceCount] = to;
            resourceValues[resourceCount] = rate;
            resourceCount++;
            cout << rate << " units of " << from << " traded for " << rate << " units of new resource " << to << ".\n";
        }
        else {
            resourceValues[toIndex] += rate;
            cout << rate << " units of " << from << " traded for " << rate << " units of " << to << ". New " << to << ": " << resourceValues[toIndex] << "\n";
        }
        if (resourceValues[fromIndex] == 0) {
            for (int i = fromIndex; i < resourceCount - 1; i++) {
                resourceNames[i] = resourceNames[i + 1];
                resourceValues[i] = resourceValues[i + 1];
            }
            resourceCount--;
            cout << from << " has been fully depleted and removed.\n";
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void ResourceManager::display() const {
    cout << "Resources:\n";
    if (resourceCount == 0) {
        cout << "  No resources available.\n";
    }
    else {
        for (int i = 0; i < resourceCount; i++) {
            cout << "  " << (i + 1) << ". " << resourceNames[i] << ": " << resourceValues[i] << " units\n";
        }
    }
}

bool ResourceManager::hasResource(const string& name, int amount) {
    int index = findResourceIndex(name);
    if (index == -1) {
        return false;
    }
    return resourceValues[index] >= amount;
}