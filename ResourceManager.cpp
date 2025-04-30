#include "Stronghold.h"
#include <iostream>
#include <fstream>
using namespace std;

ResourceManager::ResourceManager() {
    resourceCount = 5; 
    resourceNames[0] = "Food";
    resourceNames[1] = "Wood";
    resourceNames[2] = "Stone";
    resourceNames[3] = "Iron";
    resourceNames[4] = "Gold";
    for (int i = 0; i < resourceCount; i++) {
        resourceValues[i] = 100;
    }
}

void ResourceManager::gather(string resource, int amount) {
    int index = findResourceIndex(resource);

    if (index != -1) {
        resourceValues[index] += amount;
        cout << "Gathered " << amount << " " << resource << ".\n";
    }
    else {
        cout << "Resource not found. Available resources are:\n";
        display();
    }
}

void ResourceManager::consume(string resource, int amount) {
    int index = findResourceIndex(resource);

    if (index != -1) {
        if (resourceValues[index] >= amount) {
            resourceValues[index] -= amount;
            cout << "Consumed " << amount << " " << resource << ".\n";
        }
        else {
            cout << "Not enough " << resource << " to consume. Available: " << resourceValues[index] << "\n";
        }
    }
    else {
        cout << "Resource not found. Available resources are:\n";
        display();
    }
}

void ResourceManager::trade(string from, string to, int rate) {
    int fromIndex = findResourceIndex(from);
    int toIndex = findResourceIndex(to);

    if (fromIndex != -1 && toIndex != -1) {
        if (resourceValues[fromIndex] >= rate) {
            resourceValues[fromIndex] -= rate;
            resourceValues[toIndex] += rate;
            cout << "Traded " << rate << " " << from << " for " << to << ".\n";
        }
        else {
            cout << "Not enough " << from << " to trade. Available: " << resourceValues[fromIndex] << "\n";
        }
    }
    else {
        cout << "One or both resources not found. Available resources are:\n";
        display();
    }
}

void ResourceManager::display() const {
    cout << "Resource Status:\n";
    for (int i = 0; i < resourceCount; i++) {
        cout << i + 1 << ". " << resourceNames[i] << ": " << resourceValues[i] << "\n";
    }
}

bool ResourceManager::hasResource(const string& name, int amount) {
    int index = findResourceIndex(name);
    return (index != -1 && resourceValues[index] >= amount);
}

int ResourceManager::findResourceIndex(const string& name) const {
    for (int i = 0; i < resourceCount; i++) {
        if (resourceNames[i] == name) {
            return i;
        }
    }
    return -1;
}

void ResourceManager::saveResources(const string& filename) {
    ofstream out(filename);
    if (out.is_open()) {
        out << resourceCount << "\n";
        for (int i = 0; i < resourceCount; i++) {
            out << resourceNames[i] << " " << resourceValues[i] << "\n";
        }
        cout << "Resources saved successfully to " << filename << ".\n";
        out.close();
    }
    else {
        cout << "Error: Unable to open file for saving resources.\n";
    }
}

void ResourceManager::loadResources(const string& filename) {
    ifstream in(filename);
    if (in.is_open()) {
        in >> resourceCount;
        for (int i = 0; i < resourceCount; i++) {
            in >> resourceNames[i] >> resourceValues[i];
        }
        cout << "Resources loaded successfully from " << filename << ".\n";
        in.close();
    }
    else {
        cout << "Error: Unable to open file for loading resources.\n";
    }
}