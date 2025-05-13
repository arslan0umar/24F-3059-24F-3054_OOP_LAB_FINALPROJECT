#include "Stronghold.h"
#include <iostream>
#include <fstream>
using namespace std;

Conflict::Conflict() : warCount(0) {}

void Conflict::declareWar(int attacker, int defender, Army& attackerArmy, Army& defenderArmy,
    Leader& attackerLeader, Leader& defenderLeader,
    Peasant& attackerPeasant, Merchant& attackerMerchant, Noble& attackerNoble,
    Peasant& defenderPeasant, Merchant& defenderMerchant, Noble& defenderNoble) {
    try {
        if (attacker == defender) {
            throw GameException("Cannot declare war on self!");
        }
        if (warCount >= 20) {
            throw GameException("War log is full!");
        }
        int attackerStrength = attackerArmy.getSoldiers() * attackerArmy.getMorale() / 100;
        int defenderStrength = defenderArmy.getSoldiers() * defenderArmy.getMorale() / 100;
        cout << "War declared! Attacker strength (Player " << attacker << "): " << attackerStrength
            << " (Soldiers: " << attackerArmy.getSoldiers() << ", Morale: " << attackerArmy.getMorale() << "%)\n";
        cout << "Defender strength (Player " << defender << "): " << defenderStrength
            << " (Soldiers: " << defenderArmy.getSoldiers() << ", Morale: " << defenderArmy.getMorale() << "%)\n";
        if (attackerStrength > defenderStrength) {
            // Attacker wins
            defenderArmy.setSoldiers(defenderArmy.getSoldiers() - defenderArmy.getSoldiers() / 4);
            attackerArmy.setMorale(attackerArmy.getMorale() - 10);
            defenderArmy.setMorale(defenderArmy.getMorale() - 20);
            // Winner effects
            attackerLeader.setPopularity(attackerLeader.getPopularity() + 5);
            attackerArmy.setMorale(attackerArmy.getMorale() + 10);
            attackerPeasant.updateSatisfaction(5);
            attackerMerchant.updateSatisfaction(5);
            attackerNoble.updateSatisfaction(5);
            // Loser effects
            defenderLeader.setPopularity(defenderLeader.getPopularity() - 5);
            defenderArmy.setMorale(defenderArmy.getMorale() - 10);
            defenderPeasant.updateSatisfaction(-5);
            defenderMerchant.updateSatisfaction(-5);
            defenderNoble.updateSatisfaction(-5);
            cout << "Player " << attacker << " wins the battle against Player " << defender << "!\n";
            cout << "Effects on Player " << attacker << " (Winner):\n";
            cout << "  Leader Popularity: +" << 5 << ", Army Morale: +" << 10 << ", Social Satisfaction: +" << 5 << "\n";
            cout << "Effects on Player " << defender << " (Loser):\n";
            cout << "  Leader Popularity: -" << 5 << ", Army Morale: -" << 10 << ", Social Satisfaction: -" << 5 << "\n";
        }
        else {
            // Defender wins
            attackerArmy.setSoldiers(attackerArmy.getSoldiers() - attackerArmy.getSoldiers() / 4);
            attackerArmy.setMorale(attackerArmy.getMorale() - 20);
            defenderArmy.setMorale(defenderArmy.getMorale() - 10);
            // Winner effects
            defenderLeader.setPopularity(defenderLeader.getPopularity() + 5);
            defenderArmy.setMorale(defenderArmy.getMorale() + 10);
            defenderPeasant.updateSatisfaction(5);
            defenderMerchant.updateSatisfaction(5);
            defenderNoble.updateSatisfaction(5);
            // Loser effects
            attackerLeader.setPopularity(attackerLeader.getPopularity() - 5);
            attackerArmy.setMorale(attackerArmy.getMorale() - 10);
            attackerPeasant.updateSatisfaction(-5);
            attackerMerchant.updateSatisfaction(-5);
            attackerNoble.updateSatisfaction(-5);
            cout << "Player " << defender << " repels Player " << attacker << "'s attack!\n";
            cout << "Effects on Player " << defender << " (Winner):\n";
            cout << "  Leader Popularity: +" << 5 << ", Army Morale: +" << 10 << ", Social Satisfaction: +" << 5 << "\n";
            cout << "Effects on Player " << attacker << " (Loser):\n";
            cout << "  Leader Popularity: -" << 5 << ", Army Morale: -" << 10 << ", Social Satisfaction: -" << 5 << "\n";
        }
        wars[warCount].attacker = attacker;
        wars[warCount].defender = defender;
        wars[warCount].active = true;
        warCount++;
        saveWars();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Conflict::betray(int betrayer, int victim, Diplomacy& diplomacy, Army& betrayerArmy, Army& victimArmy,
    Leader& betrayerLeader, Leader& victimLeader,
    Peasant& betrayerPeasant, Merchant& betrayerMerchant, Noble& betrayerNoble,
    Peasant& victimPeasant, Merchant& victimMerchant, Noble& victimNoble) {
    try {
        if (!diplomacy.hasAlliance(betrayer, victim)) {
            throw GameException("No alliance to betray between Player " + to_string(betrayer) + " and Player " + to_string(victim));
        }
        diplomacy.breakAlliance(betrayer, victim);
        cout << "Player " << betrayer << " betrays Player " << victim << "!\n";
        declareWar(betrayer, victim, betrayerArmy, victimArmy, betrayerLeader, victimLeader,
            betrayerPeasant, betrayerMerchant, betrayerNoble,
            victimPeasant, victimMerchant, victimNoble);
        betrayerArmy.setMorale(betrayerArmy.getMorale() - 15); // Penalty for betrayal
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Conflict::displayWars() const {
    cout << "Active Wars:\n";
    bool found = false;
    for (int i = 0; i < warCount; i++) {
        if (wars[i].active) {
            cout << "Player " << wars[i].attacker << " vs Player " << wars[i].defender << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No active wars.\n";
    }
}

void Conflict::saveWars() const {
    ofstream file("wars.txt");
    if (file.is_open()) {
        for (int i = 0; i < warCount; i++) {
            file << wars[i].attacker << " " << wars[i].defender << " " << (wars[i].active ? 1 : 0) << "\n";
        }
        file.close();
    }
    else {
        cout << "Error: Unable to save wars.\n";
    }
}

void Conflict::loadWars() {
    ifstream file("wars.txt");
    warCount = 0;
    if (file.is_open()) {
        while (file >> wars[warCount].attacker >> wars[warCount].defender >> wars[warCount].active && warCount < 20) {
            warCount++;
        }
        file.close();
    }
    else {
        cout << "Error: Unable to load wars.\n";
    }
}