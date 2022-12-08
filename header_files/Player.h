#pragma once // preprocessing directive for avoiding to add this file twice.

// Declaration of the libraries and headers needed.
#include "../header_files/Map.h"
#include "../header_files/Cards.h"
#include "../header_files/Orders.h"
#include "../header_files/GameEngine.h"
#include "../header_files/PlayerStrategies.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Forward class declarartion
class Territory;
class Hand;
class Order;
class OrdersList;
class OrderOperation;
class GameEngine;
class PlayerStrategy;

class Player
{

public:

    friend ostream& operator<<(ostream& out, const Player& player); // Stream insertion operator

    // ---- Constructor methods ---- 
    Player(); //default constructor
    Player(const string &name); // constructor with name of the player
    Player(const string &name, Hand* hand); //Constructor with name and hand 
    Player(const string &name, Hand*, GameEngine*); // Constructor with name, hand, engine, and strategy
    Player(const string& name, Hand* hand, GameEngine* game, PlayerStrategy* strategy);
    Player(const Player &p);  // Copy constructor
    Player& operator =(const Player& player);   // Assignment operator

    // ---- Destructor method ----
    ~Player();  // Destructor

    // ---- Mutator methods ----
    void addTerritory(Territory* territory); // add territory to player.
    void SetHand(Hand* hand);
    void SetName(const string &name);
    void setReinforcementPool(int rP);
    void add2ReinforecemntPool(int rP);
    vector<Territory*>& toDefend();    // Returns a list of territories that are to be defended (owned territories)
	vector<Territory*> toAttack();	// Returns a list of territories that are to be attacked
   // void issueOrder(string order_name);
    bool issueOrder();
    bool ownsTerritory(Territory* territory); // Whether player owns a territory in defend list
    bool ownsTerritory(int ID);
    void addOwnedTerritory(Territory*);
    void removeOwnedTerritory(Territory*);
    void setStrategy(PlayerStrategy*);
    void setHasBeenAttacked(bool aBool);

    // ---- Accessor methods ----
    Hand* getPlayerHand() const; // Hand pointer getter
	OrdersList* getPlayerOrdersList() const; // OrderList getter
    string getPlayerName() const; // Name getter
    vector<Territory*>& getPlayerTerritories(); // Territories getter
    int getReinforcementPool() const;
    GameEngine* getGameEngine() const;
    void beginCeasefire(const string&);
    void endCeasefire(const string&);
    PlayerStrategy* getStrategy() const;
    int getNumTerritories();
    bool getHasBeenAttacked();
    vector<string> cannotAttack={};
private:

    string m_PlayerName; // Name of the player 
    vector<Territory*> m_OwnedTerritories; // Pointer to owned territories
    Hand* m_PlayerHand; // Pointer to hand of cards
    OrdersList* m_Playerorderslist; // Pointer to the list of orders
    int m_reinforcementPool; // Number of armies in the reinforcement pool
    bool m_hasBeenAttacked;
    GameEngine* m_gameEngine;
    PlayerStrategy* m_strategy;
};

