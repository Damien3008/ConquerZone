#pragma once
#include<vector> // To implement a list containing orders.
#include<iostream> // For input/output.
#include<iomanip> // To format output.
#include<string> // To store the label of an order within the order object itself.
#include<cmath> // for the floor method
#include "../header_files/Map.h"
#include "../header_files/Player.h"
#include "../header_files/Cards.h"
#include "../header_files/GameEngine.h"
#include "../header_files/LoggingObserver.h"
using namespace std;

class Deck;
class Territory;
class GameEngine;

/**
 * This is an abstract class for orders. All functionalities meant to be implemented by subclasses.
 */
class Order : public ILoggable, public Subject
{
public:
    Order();
    Order(const Order&); // copy constructor
    Order& operator = (const Order& order); //Assignment operator
    friend ostream& operator<<(ostream& out, const Order& o);
    friend istream& operator>>(istream& in, Order&);
    
    virtual string getLabel() const = 0;
    virtual bool validate() const = 0;
    virtual void execute() = 0;
    virtual ~Order() = 0; // destructor

    //NEW METHODS
    void setEffect(string eff);
    string getEffect();
    string stringToLog();

private:
    virtual Order* clone() const = 0;
    virtual ostream& printOrder(ostream&) const = 0;
    friend class OrdersList;

    string effect;
};

class deploy : public Order
{
public:
    deploy();
    deploy(Player* player, Territory* territory, const int& reinforcements, GameEngine* game);
    deploy(const deploy&);
    deploy& operator=(const deploy);

    friend ostream& operator<<(ostream& out, const deploy& d);
    friend istream& operator>>(istream& in, deploy&);

    string getLabel() const override;
    bool validate() const override;
    void execute() override;
    ~deploy();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;

    //NEW: Attributes of type Player, Territory and int
    
    Player* player; //Player who issued order
    Territory* target; //Territory being deployed to
    int reinforcements; //Number of reinforcements from the Reinforcement pool
    GameEngine* game;

};

class advanceOrder : public Order
{
public:
    advanceOrder();
    advanceOrder(Player* player, Territory* source, Territory* target, Player* enemy, const int&, GameEngine* game);
    advanceOrder(const advanceOrder&);
    advanceOrder& operator=(const advanceOrder);

    friend ostream& operator<<(ostream& out, const advanceOrder& a);
    friend istream& operator>>(istream& in, advanceOrder&);

    string getLabel() const override;
    bool validate() const override;
    void execute() override;
    ~advanceOrder();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;

    //NEW: Attributes of type Player, Territory and int

    Player* player;       //Player performing the order
    Territory* source;    //Territory owned by the player
    Territory* target;    //Territory owned by the enemy player
    Player* enemy;        //Player who owns the target enemy
    int numberArmies;    //Number of armies to be sent
    GameEngine* game;
};

class bomb : public Order
{
public:
    bomb();
    bomb(Player* player, Territory* territory, Deck* deck, GameEngine* game);
    bomb(const bomb&);
    bomb& operator=(const bomb);

    friend ostream& operator<<(ostream& out, const bomb& b);
    friend istream& operator>>(istream& in, bomb&);

    string getLabel() const override;
    bool validate() const override;
    void execute() override;
    ~bomb();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    //NEW: Attributes of type Player, Territory, and Deck

    Player* player;
    Territory* target;
    Deck* deck;
    GameEngine* game;
};

class blockade : public Order
{
public:
    blockade();
    blockade(Player* player, Territory* territory, Deck* deck, Player* neutral, GameEngine* game);
    blockade(const blockade&);
    blockade& operator=(const blockade);

    friend ostream& operator<<(ostream& out, const blockade& b);
    friend istream& operator>>(istream& in, blockade&);

    string getLabel() const override;
    bool validate() const override;
    void execute() override;
    ~blockade();



private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    GameEngine* game;

    //NEW: Attributes of type Player, Territory, and Deck,

    Player* player;
    Territory* target;
    Deck* deck;
    Player* neutral; //CPU Player who merely exists to protect a player's territory for temporaliry.

};

class airlift : public Order
{
public:
    airlift();
    airlift(Player* player, Territory* source, Territory* target, const int numberOfArmies, Deck* deck, GameEngine* game);
    airlift(const airlift&);
    airlift& operator=(const airlift);

    friend ostream& operator<<(ostream& out, const airlift& a);
    friend istream& operator>>(istream& in, airlift&);

    string getLabel() const override;
    bool validate() const override;
    void execute() override;
    ~airlift();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    GameEngine* game;

    //NEW: Attributes of type int, Player, and Territory

    Player* player; 
    Territory* source; 
    Territory* target; 
    int numberOfArmies; 
    Deck* deck;
};

class negotiate : public Order
{
public:
    negotiate();
    negotiate(Player* player, Player* target, Deck* deck, GameEngine* game);
    negotiate(const negotiate&);
    negotiate& operator=(const negotiate);

    friend ostream& operator<<(ostream& out, const negotiate& n);
    friend istream& operator>>(istream& in, negotiate&);

    string getLabel() const override;
    bool validate() const override;
    void execute() override;
    ~negotiate();

private:
    const static string label;
    Order* clone() const override;
    ostream& printOrder(ostream&) const override;
    GameEngine* game;

    //NEW: Atttributes of Player and Deck type
    Player* player;
    Player* target;
    Deck* deck;

};

/**
 * Should be created at the beginning of the program.
 * Creates an order, the type depending on the user input.
 */
class OrderOperation
{
public:
    OrderOperation();
    OrderOperation(const OrderOperation&);
    OrderOperation& operator=(const OrderOperation);

    ~OrderOperation();

    friend ostream& operator<<(ostream& out, const OrderOperation& o);
    friend istream& operator>>(istream& in, OrderOperation&);

    Order* createOrder(string) const;
};

/**
 * Designed to hold a list of valid orders
 * and carry out basic list functions.
 */
class OrdersList : public ILoggable, Subject
{
public:
    OrdersList();
    OrdersList(Player* ordersListOwner, vector<Order*>& orders);
    ~OrdersList();
    OrdersList(const OrdersList&);
    void addOrder(Order* o);
    string stringToLog() override;
    void remove(int);
    void remove(Order*, int);
    void update();
    void move(int, int);
    void executeOrders(); // Executes orders and empties the list
    vector<Order*>& getOrders();
    OrdersList& operator=(const OrdersList&);

    friend ostream& operator<<(ostream& out, const OrdersList& o);
    friend istream& operator>>(istream& in, OrdersList&);

private:
    Player* ordersListOwner;
    vector<Order*> orders;
};
