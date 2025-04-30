#include <iostream>
#include <string>
#include <iomanip>
#include "Stronghold.h"
using namespace std;

void displayBorder(int width = 60, char symbol = '-') {
    cout << string(width, symbol) << endl;
}

void displayCenteredText(const string& text, int width = 60, char borderChar = '|') {
    int padding = (width - text.length() - 2) / 2;
    cout << borderChar << string(padding, ' ') << text;
    if ((width - text.length()) % 2 != 0) {
        cout << string(padding + 1, ' ');
    }
    else {
        cout << string(padding, ' ');
    }
    cout << borderChar << endl;
}

void displayTitleBox(const string& title, const string& subtitle = "") {
    displayBorder(60, '=');
    displayCenteredText(title, 60, '|');
    if (!subtitle.empty()) {
        displayCenteredText(subtitle, 60, '|');
    }
    displayBorder(60, '=');
}

void displayKingdomStatus(const ResourceManager& rm, const Population& pop,
    const Army& army, const Bank& bank, const Leader& leader,
    const Peasant& peasant, const Merchant& merchant, const Noble& noble) {

    displayTitleBox("KINGDOM STATUS");

    cout << "\n--- LEADERSHIP ---\n";
    leader.display();

    cout << "\n--- POPULATION ---\n";
    pop.display();

    cout << "\n--- SOCIAL CLASSES ---\n";
    peasant.displayStatus();
    merchant.displayStatus();
    noble.displayStatus();

    cout << "\n--- MILITARY ---\n";
    army.display();

    cout << "\n--- ECONOMY ---\n";
    bank.display();

    cout << "\n--- RESOURCES ---\n";
    rm.display();

    displayBorder();
}

void gatherResources(ResourceManager& rm) {
    displayTitleBox("RESOURCE GATHERING");
    cout << "\nAvailable resources:\n";
    rm.display();

    cout << "\nEnter resource to gather (or 'back' to return): ";
    string name;
    cin >> name;

    if (name == "back") return;

    cout << "Enter amount to gather: ";
    int amount;
    cin >> amount;

    if (amount <= 0) {
        cout << "Amount must be positive.\n";
        return;
    }

    rm.gather(name, amount);
}

void consumeResources(ResourceManager& rm) {
    displayTitleBox("RESOURCE CONSUMPTION");
    cout << "\nAvailable resources:\n";
    rm.display();

    cout << "\nEnter resource to consume (or 'back' to return): ";
    string name;
    cin >> name;

    if (name == "back") return;

    cout << "Enter amount to consume: ";
    int amount;
    cin >> amount;

    if (amount <= 0) {
        cout << "Amount must be positive.\n";
        return;
    }

    rm.consume(name, amount);
}

void tradeResources(ResourceManager& rm) {
    displayTitleBox("RESOURCE TRADING");
    cout << "\nAvailable resources:\n";
    rm.display();

    cout << "\nEnter resource to trade from: ";
    string fromResource;
    cin >> fromResource;

    cout << "Enter resource to trade to: ";
    string toResource;
    cin >> toResource;

    cout << "Enter amount to trade: ";
    int amount;
    cin >> amount;

    if (amount <= 0) {
        cout << "Amount must be positive.\n";
        return;
    }

    rm.trade(fromResource, toResource, amount);
}

int main() {
    srand(time(0));

    ResourceManager resourceManager;
    Army army;
    Bank bank;
    Economy economy;
    Leader leader;
    Population population;
    EventManager eventManager;

    Peasant peasant;
    Merchant merchant;
    Noble noble;

    displayTitleBox("STRONGHOLD GAME", "Medieval Kingdom Simulator");

    cout << "\nWelcome to your kingdom, " << leader.getName() << "!\n";
    cout << "You are now in charge of managing all aspects of your medieval stronghold.\n";
    cout << "Make wise decisions to ensure the prosperity and survival of your realm.\n";

    bool running = true;
    int turn = 1;

    while (running) {
        displayBorder();
        displayTitleBox("TURN " + to_string(turn) + " - " + leader.getName() + "'s Realm");

        displayTitleBox("STRONGHOLD GAME MENU");
        cout << "1. Display Kingdom Status\n";
        cout << "2. Resource Management\n";
        cout << "3. Population Management\n";
        cout << "4. Military Management\n";
        cout << "5. Economy Management\n";
        cout << "6. Leadership Actions\n";
        cout << "7. Banking System\n";
        cout << "8. Trigger Random Event\n";
        cout << "9. Save Game\n";
        cout << "10. Load Game\n";
        cout << "0. Exit Game\n";
        cout << "\nEnter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            displayKingdomStatus(resourceManager, population, army, bank, leader,
                peasant, merchant, noble);
            break;

        case 2: {
            displayTitleBox("RESOURCE MANAGEMENT");
            cout << "1. Gather Resources\n";
            cout << "2. Consume Resources\n";
            cout << "3. Trade Resources\n";
            cout << "4. Display Resources\n";
            cout << "Enter choice: ";
            int resourceChoice;
            cin >> resourceChoice;

            switch (resourceChoice) {
            case 1: gatherResources(resourceManager); break;
            case 2: consumeResources(resourceManager); break;
            case 3: tradeResources(resourceManager); break;
            case 4:
                displayTitleBox("RESOURCES");
                resourceManager.display();
                break;
            default: cout << "Invalid resource management choice.\n";
            }
            break;
        }

        case 3: {
            displayTitleBox("POPULATION MANAGEMENT");
            cout << "1. View Population\n";
            cout << "2. Modify Population\n";
            cout << "3. View Social Class Status\n";
            cout << "Enter choice: ";
            int popChoice;
            cin >> popChoice;

            switch (popChoice) {
            case 1:
                displayTitleBox("POPULATION STATUS");
                population.display();
                break;
            case 2: {
                cout << "Enter amount to increase (+) or decrease (-): ";
                int amount;
                cin >> amount;
                population.modify(amount);
                break;
            }
            case 3:
                displayTitleBox("SOCIAL CLASS STATUS");
                peasant.displayStatus();
                merchant.displayStatus();
                noble.displayStatus();
                break;
            default:
                cout << "Invalid population management choice.\n";
            }
            break;
        }

        case 4: {
            displayTitleBox("MILITARY MANAGEMENT");
            cout << "1. Train Army\n";
            cout << "2. Pay Army\n";
            cout << "3. Display Army Status\n";
            cout << "Enter choice: ";
            int militaryChoice;
            cin >> militaryChoice;

            switch (militaryChoice) {
            case 1:
                displayTitleBox("ARMY TRAINING");
                army.train(resourceManager);
                break;
            case 2:
                displayTitleBox("ARMY PAYMENT");
                army.pay(resourceManager);
                break;
            case 3:
                displayTitleBox("ARMY STATUS");
                army.display();
                break;
            default: cout << "Invalid military management choice.\n";
            }
            break;
        }

        case 5:
            displayTitleBox("ECONOMY MANAGEMENT");
            economy.manage(resourceManager, peasant, merchant, noble);
            break;

        case 6:
            displayTitleBox("LEADERSHIP ACTIONS");
            leader.menu(population, army);
            break;

        case 7:
            displayTitleBox("BANKING SYSTEM");
            bank.menu(resourceManager);
            break;

        case 8:
            displayTitleBox("RANDOM EVENT");
            eventManager.trigger(resourceManager, population, army, peasant, merchant, noble);
            break;

        case 9: {
            displayTitleBox("SAVE GAME");
            Logger::saveGame(population, army, bank, leader, resourceManager,
                economy, peasant, merchant, noble);
            string scoreInfo = "Session saved on Turn " + to_string(turn) + " with Population " + to_string(population.getTotal());
            Logger::logScore(scoreInfo);
            cout << "Game saved successfully.\n";
            break;
        }

        case 10: {
            displayTitleBox("LOAD GAME");
            if (Logger::loadGame(population, army, bank, leader, resourceManager,
                economy, peasant, merchant, noble)) {
                cout << "Game loaded successfully.\n";
            }
            break;
        }

        case 0:
            running = false;
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }

        if (running && choice != 9 && choice != 10) {
            population.naturalChange();

            // Check for emigration due to low satisfaction
            peasant.checkEmigration(population);
            merchant.checkEmigration(population);
            noble.checkEmigration(population);

            // Food shortage effects
            if (!resourceManager.hasResource("Food", 10)) {
                displayTitleBox("WARNING");
                cout << "Food supplies are critically low!\n";
                population.modify(-5);
                peasant.updateSatisfaction(-5);
            }

            if (!resourceManager.hasResource("Food", 10)) {
                displayTitleBox("WARNING");
                cout << "Food supplies are critically low!\n";
                population.modify(-5);
                peasant.updateSatisfaction(-5);
            }

            if (rand() % 100 < 20) {
                displayTitleBox("RANDOM EVENT");
                cout << "A minor event occurred...\n";
                int minorEvent = rand() % 3;
                switch (minorEvent) {
                case 0:
                    cout << "Some trade caravans arrived, bringing extra gold!\n";
                    resourceManager.gather("Gold", 15);
                    break;
                case 1:
                    cout << "Local farmers had a good harvest this month.\n";
                    resourceManager.gather("Food", 20);
                    break;
                case 2:
                    cout << "Craftsmen produced extra building materials.\n";
                    resourceManager.gather("Wood", 15);
                    resourceManager.gather("Stone", 10);
                    break;
                }
            }

            turn++;
        }
    }

    displayTitleBox("GAME OVER");
    cout << "\nThank you for playing Stronghold!\n";
    cout << "Final score: " << population.getTotal() * 10 << "\n";

    // Log final score
    string finalScoreInfo = "Final score: " + to_string(population.getTotal() * 10) +
        " after " + to_string(turn) + " turns";
    Logger::logScore(finalScoreInfo);

    return 0;
}