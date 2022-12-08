#pragma once
#include"../header_files/Player.h"
#include<iostream>
#include<vector>
using namespace std;

/**
* Recursively checks the cells of the matrix, that should be connected, if that they have been visited
* @param index u, boolean array, boolean matrix, size of the matrix
*/
void traverse(int, bool[], bool**, int);
/**
* With the help of the function traverse, checks if all the cells that are connected are reachable. If yes, then the graph is connected
* @param n size of the matrix, the matrix itself
*/
bool isGraphConnected(int, bool**);
/**
* Prints an Adjancecy Matrix
* @param n size of the matrix, the matrix itself
*/
void PrintAdjancencyMatrix(int, bool**);


class Player;

class Territory{
  private:
    string name, continent; //Territory name, Contient name to which the Territory belongs
    Player *owner;          //Owner of the Territory
    int id,  numberArmies;  //# of Armies
    vector<Territory*> neighbors; //List of Neighbors
    int generateID(); //Helper Method that generates an ID for the territory based on its name
    void setID(const int&); //Setter for the ID

  public:
    Territory* next; //Pointer to the Adjacent Territory
    int index;       //Pointer to the Adjacent Territory
    Territory();    //Default Constructor
    Territory(const string&); // Constructor 
    Territory(const string&, const string&, Player *, const int&, const int&); //Constructor
    Territory(const Territory&); // Copy Constructor
    Territory& operator=(const Territory); //Assignment Operator
    friend ostream& operator<<(ostream& out, const Territory& t);   //Insertion Operator
    ~Territory(); //Destructor
	 /**
     * Retunrs the name of the Territory.
     * @return name of the Territory.
     */
    string getNameTerritory() const;
    /**
    * Sets the name of the Territory.
    * @param name of the Territory
    */
    void setNameTerritory(const string&);
    /**
    * Retunrs the name of the Continent to which the Territory belongs.
    * @return name of the Continent.
    */
    string getContinentName() const;
    /**
    * Sets the name of the Continent
    * @param name of the Continent
    */
    void setContinentName(const string&);
    /**
    * Retunrs the owner of the Territory
    * @return Owner of the Territory.
    */
    Player *getOwner();
    /**
    * Sets the owner of the Territory
    * @param new Owner of the Territory.
    */
    void setOwner(Player*);
    /**
    * Retunrs the number of Armies of the Territory
    * @return number of Armies
    */
    vector<Territory*>& getNeighbors();
    /**
    * Sets the neighbors of a territory.
    * @param new Neighbors of the territory.
    */
    int getNumberArmies() const;
    /**
    * Sets the number of Armies of the Territory
    * @param new number of Armies of the Territory.
    */
    void setNumberArmies(const int&);
    /**
    * Retunrs the Territory ID
    * @return Territory ID
    */
    int getID() const;
    /**
    * Prints the details of the Territory: ID, name, Contient's name, # Armies, and Owner
    * @return the details as a string
    */
    int getContinent() const;
    const string details() const;
    /**
    * Adds a reference to the Neighboring Territory
    * @param Territory neighbor
    */
    void addNeighbor(Territory*);
    /**
    * Prints a list of all the neighbors of the Territory
    */
    void printNeighbors();
};

class Continent {
private:
    string name;    //Name of the Continent
    int n;          //Number of the Territories that should be part of the Continent
    int powerup;    //Continent's powerup
    bool** adj;     //Adjancency Matrix
    vector<Territory*> vhead; //List of pointers to all the Territories that belong to the Continent
    int armies;

public:
    Continent();    //Default Constructor
    Continent(const int, const string); //Constructor that accepts the powerup number and the name of the Continent
    Continent(const Continent&); //Constructor that accepts the powerup number and the name of the Continent
    Continent& operator=(const Continent) noexcept; //Assignment Operator
    friend ostream& operator<<(ostream& out, const Continent& c);   //Insertion Operator
    ~Continent();   //Destructor
    /**
    * Loops through All the Territories, checks the Territories that have the same continent name, and add them to a list
    * Initialize and fill an Adjancecy Matrix based on the list of Territories that belong to the Continent
    * Prints a message confirming of the graph is connected or not
    */
    void Populate(vector<Territory*>);
    /**
    * Retunrs the name of the Continent
    * @return name of the Continent
    */
    string getName();
    /**
    * Sets the name of the Continent
    * @param new name of the Continent
    */
    void setName(string&);
    /**
    * Retunrs the power up of the Continent
    * @return the power up of the Continent
    */
    int getPowerUP();
    /**
    * Sets the power up of the Continent
    * @param new power up of the Continent
    */
    void setPowerUP(const int);
    /**
    * Prints List of Continent that belong to the Continent
    */
    void printTerritories();
    /**
    * @Return True if the graph is connected, otherwise false
    */
    int getArmies();
    bool isConnected();
    const vector<Territory*>& getTerritories() const;
};


class Map{
  private:
    int n;  //Number of Territories
    bool **adj; //Adjancency Matrix
    vector<Continent*> continents;  //List of the Continents
    vector<Territory*> territories; //List of the Territories
    /**
    * Sets the cell corresponding to two connected territories to true in the Adjacency Matrix
    * @param index of the first Territory, index of the second Territory
    */
    void add_edge(const int, const int);
    /**
    * Sets the cell corresponding to two connected territories to false in the Adjacency Matrix
    * @param index of the first Territory, index of the second Territory
    */
    void remove_edge(const int, const int);
  public:
    Map();  //Default Constructor
    Map(vector<Territory*>&, vector<Continent*>&, vector<string>&); //Main Constructor
    Map(const Map&);    //Copy Constructor
    Map& operator=(const Map) noexcept; //Assignment Operator
    friend ostream& operator<<(ostream& out, const Map& c);   //Insertion Operator
    ~Map(); //Destructor
    /**
    * First Checks if the whole map is connected
    * Second Checks if the continents are connected
    * Third Checks if a Territory belons to more than one Continent
    * @Return index of the first Territory, index of the second Territory
    */
    bool validate();
    /**
    * Uses function isGraphConnected() to check if the graph is connected
    */
    bool isConnected();
    /*
    * @Return the number of Territories
    */
    int getSizeofMap();
    /*
    * @Return The list of Continents
    */
    const vector<Continent*>& getContinents() const;
    /*
    * @Return The list of Territories
    */
    const vector<Territory*>& getTerritories() const;

    vector<Territory*> getTerritoriesByContinent(int continent);

    int calculateContinentBonus(Player* player);
    Territory* getTerritoryByID(int id);

};