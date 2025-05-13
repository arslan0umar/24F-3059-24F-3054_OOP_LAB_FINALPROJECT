#include "Stronghold.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void Communication::sendMessage(int senderId, int receiverId, const string& message) {
    try {
        if (senderId == receiverId) {
            throw GameException("Cannot send message to self!");
        }
        if (message.empty()) {
            throw GameException("Message cannot be empty!");
        }
        if (messageCount >= 50) {
            throw GameException("Message log is full!");
        }
        // Format message: "From Player X to Player Y: message"
        string formattedMessage = "From Player " + to_string(senderId) + " to Player " + to_string(receiverId) + ": " + message;
        messages[messageCount] = formattedMessage;
        messageCount++;
        cout << "Message sent successfully: " << formattedMessage << "\n";
        saveMessages();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Communication::displayMessages(int playerId) const {
    try {
        cout << "Messages for Player " << playerId << ":\n";
        bool found = false;
        for (int i = 0; i < messageCount; i++) {
            // Check if the message is to or from the player
            size_t toPos = messages[i].find("to Player " + to_string(playerId));
            size_t fromPos = messages[i].find("From Player " + to_string(playerId));
            if (toPos != string::npos || fromPos != string::npos) {
                cout << messages[i] << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No messages found.\n";
        }
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Communication::saveMessages() const {
    try {
        ofstream file("messages.txt");
        if (!file.is_open()) {
            throw GameException("Unable to open messages.txt for saving!");
        }
        for (int i = 0; i < messageCount; i++) {
            file << messages[i] << "\n";
        }
        file.close();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}

void Communication::loadMessages() {
    try {
        ifstream file("messages.txt");
        if (!file.is_open()) {
            throw GameException("Unable to open messages.txt for loading!");
        }
        messageCount = 0;
        string line;
        while (getline(file, line) && messageCount < 50) {
            if (!line.empty()) {
                messages[messageCount] = line;
                messageCount++;
            }
        }
        file.close();
    }
    catch (const GameException& e) {
        cout << "Error: " << e.message << "\n";
    }
}