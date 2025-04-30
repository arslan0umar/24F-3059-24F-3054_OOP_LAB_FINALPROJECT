#include "Stronghold.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void EventManager::trigger(ResourceManager& rm, Population& pop, Army& army,
    Peasant& peasant, Merchant& merchant, Noble& noble) {

    cout << "\n===== Random Event Triggered =====\n";

    
    srand(time(0));
    int randEvent = rand() % 5;

    switch (randEvent) {
    case 0: {
        cout << "FAMINE: A devastating famine has struck your kingdom!\n";
        cout << "Food stores reduced, population decreased, and morale lowered.\n";

        int foodLoss = 30 + (rand() % 20);
        if (rm.hasResource("Food", foodLoss)) {
            rm.consume("Food", foodLoss);
        }
        else {
            rm.consume("Food", 0); 
        }

        pop.modify(-(10 + (rand() % 15)));
        army.morale -= 10;
        if (army.morale < 0) army.morale = 0;

        peasant.updateSatisfaction(-15);
        merchant.updateSatisfaction(-5);
        noble.updateSatisfaction(-3);

        cout << "The famine has severely impacted your kingdom.\n";
        break;
    }
    case 1: {
        cout << "WAR: A neighboring kingdom has declared war!\n";

        int soldierLoss = army.getSoldiers() / 4;
        army.setSoldiers(army.getSoldiers() - soldierLoss);
        army.morale -= 15;
        if (army.morale < 0) army.morale = 0;

        cout << "You lost " << soldierLoss << " soldiers in battle.\n";
        cout << "Army morale has decreased to " << army.morale << ".\n";

        rm.consume("Gold", 20);
        rm.consume("Iron", 15);

        peasant.updateSatisfaction(-10);
        merchant.updateSatisfaction(-8);
        noble.updateSatisfaction(5); 

        break;
    }
    case 2: {
        cout << "PLAGUE: A deadly plague spreads through your kingdom!\n";

        int popLoss = pop.getTotal() / 5;
        pop.modify(-popLoss);

        cout << "You lost " << popLoss << " people to the disease.\n";

        rm.consume("Gold", 15);
        rm.consume("Food", 10);

        peasant.updateSatisfaction(-12);
        merchant.updateSatisfaction(-10);
        noble.updateSatisfaction(-8);

        break;
    }
    case 3: {
        cout << "GOOD HARVEST: This year's harvest was exceptional!\n";

        int foodGain = 50 + (rand() % 30);
        rm.gather("Food", foodGain);

        cout << "Food stores increased by " << foodGain << ".\n";

        army.morale += 5;
        if (army.morale > 100) army.morale = 100;

        peasant.updateSatisfaction(10);
        merchant.updateSatisfaction(5);
        noble.updateSatisfaction(3);

        break;
    }
    case 4: {
        cout << "TRADE BOOM: A sudden increase in trade has boosted your economy!\n";

        int goldGain = 50 + (rand() % 50);
        rm.gather("Gold", goldGain);

        cout << "Treasury increased by " << goldGain << " gold.\n";

        peasant.updateSatisfaction(5);
        merchant.updateSatisfaction(15);
        noble.updateSatisfaction(8);

        break;
    }
    }

    cout << "Event effects have been applied to your kingdom.\n";
}