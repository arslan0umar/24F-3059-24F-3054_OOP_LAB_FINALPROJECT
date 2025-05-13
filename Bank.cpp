#include "Stronghold.h"
#include <iostream>
#include <string>
using namespace std;

Bank::Bank() : loan(0) {}

void Bank::setLoan(int newLoan) {
    try {
        if (newLoan < 0) {
            throw GameException("Loan amount cannot be negative!");
        }
        loan = newLoan;
        cout << "Loan set to " << loan << " gold.\n";
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Bank::menu(ResourceManager& rm, int playerId) {
    try {
        int choice;
        cout << "\n===== Banking Menu =====\n";
        cout << "1. Take Loan\n";
        cout << "2. Repay Loan\n";
        cout << "3. View Loan Status\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter amount to borrow: ";
            int amount;
            cin >> amount;
            if (amount <= 0) {
                throw GameException("Loan amount must be positive!");
            }
            setLoan(loan + amount);
            rm.gather("Gold", amount, playerId); // Added playerId
            cout << "Borrowed " << amount << " gold. New loan: " << loan << "\n";
            break;
        }
        case 2: {
            cout << "Enter amount to repay: ";
            int amount;
            cin >> amount;
            if (amount <= 0) {
                throw GameException("Repayment amount must be positive!");
            }
            if (amount > loan) {
                throw GameException("Cannot repay more than the current loan!");
            }
            if (!rm.hasResource("Gold", amount)) {
                throw GameException("Not enough gold to repay the loan!");
            }
            rm.consume("Gold", amount, playerId); // Added playerId
            setLoan(loan - amount);
            cout << "Repaid " << amount << " gold. Remaining loan: " << loan << "\n";
            break;
        }
        case 3:
            display();
            break;
        case 4:
            cout << "Returning to main menu.\n";
            break;
        default:
            throw GameException("Invalid choice!");
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Bank::display() const {
    cout << "Bank Status:\n";
    cout << "  Current Loan: " << loan << " gold\n";
    if (loan > 0) {
        cout << "  Interest due soon. Ensure you have gold to repay!\n";
    }
    else {
        cout << "  No outstanding loans.\n";
    }
}