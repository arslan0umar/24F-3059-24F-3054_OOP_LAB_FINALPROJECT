#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void EventManager::trigger(ResourceManager& rm, Population& pop, Army& army, Peasant& peasant,
    Merchant& merchant, Noble& noble, int playerId) {
    try {
        int event = rand() % 4; // 4 possible events
        cout << "\n===== Random Event =====\n";
        switch (event) {
        case 0: // Good Harvest
            cout << "A bountiful harvest increases food supplies!\n";
            rm.gather("Food", 50, playerId); // Added playerId
            peasant.updateSatisfaction(5);
            break;
        case 1: // Bandit Raid
            cout << "Bandits raid your kingdom, stealing resources!\n";
            if (rm.hasResource("Gold", 20)) {
                rm.consume("Gold", 20, playerId); // Added playerId
            }
            else {
                army.setMorale(army.getMorale() - 10);
                cout << "No gold to steal, army morale decreases.\n";
            }
            break;
        case 2: // Plague
            cout << "A plague strikes, reducing population!\n";
            pop.modify(-20);
            peasant.updateSatisfaction(-10);
            merchant.updateSatisfaction(-5);
            noble.updateSatisfaction(-5);
            break;
        case 3: // Festival
            cout << "A grand festival boosts morale and satisfaction!\n";
            if (rm.hasResource("Food", 30)) {
                rm.consume("Food", 30, playerId); // Added playerId
                army.setMorale(army.getMorale() + 10);
                peasant.updateSatisfaction(10);
                merchant.updateSatisfaction(10);
                noble.updateSatisfaction(10);
            }
            else {
                cout << "Not enough food for the festival.\n";
            }
            break;
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}