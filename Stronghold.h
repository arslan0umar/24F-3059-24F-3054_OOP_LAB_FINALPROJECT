#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <string>
using namespace std;

// Forward declarations for circular dependencies
class ResourceManager;
class Population;
class Army;

// Base class for social classes
class SocialClass {
public:
    SocialClass() : satisfaction(50) {}
    virtual void updateSatisfaction(int change) = 0;
    virtual void displayStatus() const = 0;
    virtual int checkEmigration(Population& pop) = 0; // New function to check for emigration
    int getSatisfaction() const { return satisfaction; }
protected:
    int satisfaction; // 0-100
};

class Peasant : public SocialClass {
public:
    void updateSatisfaction(int change) override;
    void displayStatus() const override;
    int checkEmigration(Population& pop) override;
};

class Merchant : public SocialClass {
public:
    void updateSatisfaction(int change) override;
    void displayStatus() const override;
    int checkEmigration(Population& pop) override;
};

class Noble : public SocialClass {
public:
    void updateSatisfaction(int change) override;
    void displayStatus() const override;
    int checkEmigration(Population& pop) override;
};

class ResourceManager {
public:
    ResourceManager();
    void gather(string resource, int amount);
    void consume(string resource, int amount);
    void trade(string from, string to, int rate);
    void display() const;
    void saveResources(const string& filename);
    void loadResources(const string& filename);
    bool hasResource(const string& name, int amount);
    int findResourceIndex(const string& name) const;
    // Accessor methods for save/load
    string getResourceName(int index) const { return resourceNames[index]; }
    int getResourceValue(int index) const { return resourceValues[index]; }
    int getResourceCount() const { return resourceCount; }
private:
    string resourceNames[10];
    int resourceValues[10];
    int resourceCount;
};

class Army {
public:
    Army();
    void train(ResourceManager& rm);
    void pay(ResourceManager& rm);
    void display() const;
    int getSoldiers() const { return soldiers; }
    int getMorale() const { return morale; }
    void setMorale(int newMorale) { morale = newMorale; }
    void setSoldiers(int newSoldiers) { soldiers = newSoldiers; }
    int morale;
private:
    int soldiers;
};

class Bank {
public:
    Bank();
    void menu(ResourceManager& rm);
    int getLoan() const { return loan; }
    void setLoan(int newLoan) { loan = newLoan; }
    void display() const;
private:
    int loan;
};

class Economy {
public:
    Economy();
    void manage(ResourceManager& rm, Peasant& peasant, Merchant& merchant, Noble& noble);
    void display() const;
    int getTaxRate() const { return taxRate; }
    void setTaxRate(int newRate) { taxRate = newRate; }
private:
    int taxRate;
};

class Population {
public:
    Population();
    void modify(int amt);
    void naturalChange(); // New function for natural population changes
    void display() const;
    int getTotal() const { return count; }
    void setTotal(int newCount) { count = newCount; }
private:
    int count;
};

class Leader {
public:
    Leader() : name("Default Leader"), popularity(50) {}
    void menu(Population& pop, Army& army);
    void display() const;
    string getName() const { return name; }
    int getPopularity() const { return popularity; }
    void setName(const string& newName) { name = newName; }
    void setPopularity(int newPopularity) { popularity = newPopularity; }
private:
    string name;
    int popularity; // 0-100
};

class EventManager {
public:
    void trigger(ResourceManager& rm, Population& pop, Army& army, Peasant& peasant,
        Merchant& merchant, Noble& noble);
};

class Logger {
public:
    static void logScore(const string& info);
    static void saveGame(const Population& pop, const Army& army,
        const Bank& bank, const Leader& leader,
        const ResourceManager& rm, const Economy& economy,
        const Peasant& peasant, const Merchant& merchant, const Noble& noble);
    static bool loadGame(Population& pop, Army& army, Bank& bank,
        Leader& leader, ResourceManager& rm, Economy& economy,
        Peasant& peasant, Merchant& merchant, Noble& noble);
};

#endif