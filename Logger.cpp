#include "Stronghold.h"
#include <fstream>
#include <iostream>
using namespace std;

void Logger::logScore(const string& info) {
    ofstream file("score.txt", ios::app);
    if (file.is_open()) {
        file << info << "\n";
        file.close();
        cout << "Score logged successfully to score.txt\n";
    }
    else {
        cout << "Error: Unable to open score.txt for logging\n";
    }
}

void Logger::saveGame(const Population& pop, const Army& army,
    const Bank& bank, const Leader& leader,
    const ResourceManager& rm) {
    ofstream file("game_save.txt");
    if (file.is_open()) {
        file << "POPULATION " << pop.getTotal() << "\n";

        file << "ARMY " << army.getSoldiers() << " " << army.getMorale() << "\n";

        file << "BANK " << bank.getLoan() << "\n";

        file << "LEADER " << leader.getName() << " " << leader.getPopularity() << "\n";


        file.close();
        cout << "Game state saved successfully to game_save.txt\n";
    }
    else {
        cout << "Error: Unable to open game_save.txt for saving\n";
    }
}

bool Logger::loadGame(Population& pop, Army& army, Bank& bank,
    Leader& leader, ResourceManager& rm) {
    ifstream file("game_save.txt");
    if (file.is_open()) {
        string marker;

        if (file >> marker && marker == "POPULATION") {
            int count;
            if (file >> count) {
                pop.setTotal(count);
            }
        }

        if (file >> marker && marker == "ARMY") {
            int soldiers, morale;
            if (file >> soldiers >> morale) {
                army.setSoldiers(soldiers);
                army.setMorale(morale);
            }
        }

        if (file >> marker && marker == "BANK") {
            int loan;
            if (file >> loan) {
                bank.setLoan(loan);
            }
        }

        if (file >> marker && marker == "LEADER") {
            string name;
            int popularity;

            if (file >> name >> popularity) {
                leader.setName(name);
                leader.setPopularity(popularity);
            }
        }

        rm.loadResources("game_save.txt");

        file.close();
        cout << "Game state loaded successfully from game_save.txt\n";
        return true;
    }
    else {
        cout << "Error: Unable to open game_save.txt for loading\n";
        return false;
    }
}