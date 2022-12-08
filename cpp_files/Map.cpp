#include"../header_files/Map.h"
#include"../header_files/Player.h"
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
using namespace std;


void PrintAdjancencyMatrix(int n, bool** adj) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << adj[i][j] << "|";
		cout << endl;
	}
}
void traverse(int u, bool visited[], bool** adj, int size) {
	visited[u] = true;
	for (int v = 0; v < size; v++) {
		if (adj[u][v]) {
			if (!visited[v])
				traverse(v, visited, adj, size);
		}
	}
}
bool isGraphConnected(int n, bool** arr) {
	bool* vis = new bool[n];
	for (int u = 0; u < n; u++) {
		for (int i = 0; i < n; i++)
			vis[i] = false;
		traverse(u, vis, arr, n);
		for (int i = 0; i < n; i++) {
			if (!vis[i])
				return false;
		}
	}
	return true;
}

/* --- Territory Class --- */
/* --- Constructors, Destructor, & Operators --- */
Territory::Territory() {
	this->name = "Undefined";
	this->continent = "Undefined";
	this->owner = new Player();
	this->numberArmies = 0;
	this->id = 0;
}

Territory::Territory(const string& name)
{
	this->name = name;
	this->continent = "Undefined";
	this->owner = new Player();
	this->numberArmies = 0;
	this->id = 0;
}
Territory::Territory(const string& name, const string& continent, Player* owner, const int& armies, const int& index)
{
	this->name = name;
	this->continent = continent;
	this->owner = owner;
	this->setNumberArmies(armies);
	this->setID(generateID());
	this->index = index;
}
Territory::Territory(const Territory& other)
{
	this->name = other.name;
	this->continent = other.continent;
	this->owner = other.owner;
	this->setNumberArmies(other.getNumberArmies());
	this->setID(generateID());
	this->index = other.index;
}
Territory& Territory::operator=(const Territory other)
{
	if (this != &other)
	{
		//Freeing the existing resource
		delete this->owner;
		this->neighbors.clear();
		this->neighbors.shrink_to_fit();

		//Reserving enough space to avoid pointless resizing while adding new elements
		this->neighbors.reserve(other.neighbors.size());
		std::copy(other.neighbors.begin(), other.neighbors.end(), this->neighbors.begin());

		//Copying the rest of the data
		this->name = other.getNameTerritory();
		this->continent = other.getContinentName();
		this->owner = other.owner;
		this->numberArmies = other.getNumberArmies();
		this->setID(generateID());
		this->next = other.next;
		this->neighbors = other.neighbors;
		this->index = other.index;
	}
	return *this;
}
ostream& operator<<(ostream& out, const Territory& t) {
	out << t.details();
	return out;
}
Territory::~Territory()
{
	this->owner = nullptr;
	this->neighbors.clear();
	this->neighbors.shrink_to_fit();
	this->next = nullptr;

}

/* --- Territory Class --- */
/* --- Methods --- */

void Territory::addNeighbor(Territory* neighbor) {
	this->neighbors.push_back(neighbor);
	Territory* newT = new Territory(*neighbor);
	newT->next = nullptr;
	Territory* curr = this;
	while (curr)
	{
		if (curr->next == nullptr)
		{
			curr->next = newT;
			return;
		}
		curr = curr->next;
	}
}
void Territory::printNeighbors() {
	/*Territory* head = this;
	while (head != nullptr)
	{
		cout << "(" << head->getNameTerritory()
			<< ") ";
		head = head->next;
	}
	cout << endl;*/

	for (Territory* t : this->neighbors)
	{
		cout << "(" + t->getNameTerritory() + "[" + t->getOwner()->getPlayerName() + "])";
	}
	cout << endl;
}
int Territory::generateID() {
	int generatedID = 0;
	if (this->name == "Undefined")
	{
		generatedID = 0;
	}
	else {
		hash<string> hashme;
		generatedID = (hashme(this->name) % 421);
	}
	return generatedID;
}
const string Territory::details() const {
	ostringstream buffer;
	buffer << "ID: " << this->id << " | Territory name: " << this->name << " | Continent: " << this->continent << " | Owner: "
		<< this->owner->getPlayerName() << " | # of Armies: " << this->numberArmies << " index : " << this->index << endl;
	return buffer.str();
}

/* --- Territory Class --- */
/* --- Accessors & Modifiers --- */

string Territory::getNameTerritory() const {
	return this->name;
}
void Territory::setNameTerritory(const string& newName)
{
	name = newName;
}
vector<Territory*>& Territory::getNeighbors(){
	return this->neighbors;
} 
string Territory::getContinentName() const {
	return this->continent;
}
void Territory::setContinentName(const string& newContinent)
{
	continent = newContinent;
}
Player* Territory::getOwner()
{
	return owner;
}
void Territory::setOwner(Player* p)
{
	this->owner = p;
}
int Territory::getNumberArmies() const
{
	return this->numberArmies;
}
void Territory::setNumberArmies(const int& number)
{
	this->numberArmies = number;
}
void Territory::setID(const int& newID)
{
	this->id = newID;
}
int Territory::getID() const
{
	return this->id;
}

int Territory::getContinent() const 
{
	return this->id;
}

/* --- Continent Class --- */
/* --- Constructors, Destructor, & Operators --- */


Continent::Continent()
{
	this->name = "Undetermined";
	this->powerup = 0;
}
Continent::Continent(const int power, string name)
{
	this->name = name;
	this->powerup = power;
}
Continent::Continent(const Continent& other)
{
	if (this->adj != nullptr)
	{
		for (int i = 0; i < this->n; i++)
			delete[] adj[i];
		delete[] adj;
	}
	this->adj = other.adj;
	this->n = other.n;
	this->name = other.name;
	this->powerup = other.powerup;
	this->vhead.clear();
	this->vhead.shrink_to_fit();
	this->vhead.reserve(other.vhead.size());
	this->vhead.assign(other.vhead.begin(), other.vhead.end());
}
Continent& Continent::operator=(const Continent other) noexcept
{
	if (this != &other)
	{
		if (this->adj != nullptr)
		{
			for (int i = 0; i < this->n; i++)
				delete[] adj[i];
			delete[] adj;
		}
		this->adj = other.adj;
		this->vhead.clear();
		this->vhead.shrink_to_fit();
		this->vhead.reserve(other.vhead.size());
		this->vhead.assign(other.vhead.begin(), other.vhead.end());
		this->n = other.n;
		this->name = other.name;
		this->powerup = other.powerup;
	}
	return *this;
}
ostream& operator<<(ostream& out, const Continent& c)
{
	out << "Name: " << c.name << " Power up: " << c.powerup << " # of Territories: " << c.n;
	return out;
}
Continent::~Continent() {
	if (this->adj != nullptr)
	{
		for (int i = 0; i < this->n; i++)
			delete[] adj[i];
		delete[] adj;
	}
	this->vhead.clear();
	this->vhead.shrink_to_fit();
}

/* --- Continent Class --- */
/* --- Methods --- */


void Continent::Populate(vector<Territory*> territories)
{
	//Reserve 10 to avoid resizing if possible
	vhead.reserve(10);
	int index = 0;
	//Push all the Territories whose name are the same as this Continent
	for (int i = 0; i < territories.size(); i++)
	{
		Territory* current = territories[i];
		if (current != nullptr)
		{
			if (current->getContinentName() == this->name)
			{
				vhead.push_back(current);
				index++;
			}
		}
	}
	//index is number of Territories whose content has the same name as this continent
	this->n = index;
	//Initialize the adjancency matrix
	this->adj = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		adj[i] = new bool[n];
		for (int j = 0; j < n; j++)
			adj[i][j] = false;
	}
	//Loop Through all the elements of vhead and their neighbors. If the neighbor also belongs to this continent, set their corresponding adjancency cell to true
	for (int i = 0; i < this->n; i++)
	{
		if (vhead[i] != nullptr)
		{
			Territory* current = vhead[i]->next;
			while (current)
			{
				for (int j = 0; j < this->n; j++)
				{
					if (current->getNameTerritory() == vhead[j]->getNameTerritory() && current->getNameTerritory() != vhead[i]->getNameTerritory())
					{
						adj[i][j] = true;
						break;
					}
				}
				current = current->next;
			}
		}
	}
}
void Continent::printTerritories()
{
	for (int i = 0; i < this->n; i++)
	{
		while (this->vhead[i] != nullptr)
		{
			cout << "(" << i << ", " << this->vhead[i]->getNameTerritory()
				<< ") ";
			this->vhead[i] = this->vhead[i]->next;
		}
		cout << endl;
	}
}

bool Continent::isConnected()
{
	return isGraphConnected(this->n, adj);
}




/* --- Continent Class --- */
/* --- Accessors & Modifiers --- */


string Continent::getName() { return this->name; }
void Continent::setName(string& name) { this->name = name; }
int Continent::getPowerUP() { return this->powerup; }
void Continent::setPowerUP(const int powerup) { this->powerup = powerup; }
int Continent::getArmies() {return this->armies;}
const vector<Territory*>& Continent::getTerritories() const {
	return this->vhead;
}


/* --- Map Class --- */
/* --- Constructors, Destructor, & Operators --- */


Map::Map() {
	this->n = 0;
	adj = nullptr;
}
Map::Map(vector<Territory*>& territories, vector<Continent*>& continents, vector<string>& neighbors)
{
	this->territories = territories;
	this->continents = continents;
	this->n = this->territories.size();

	adj = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		adj[i] = new bool[n];
		for (int j = 0; j < n; j++)
			adj[i][j] = false;
	}

	string territorytofind;
	Territory* t_origin, * t_destination;
	t_origin = nullptr;
	t_destination = nullptr;
	int o = 0, d = 0, j = 0;
	for (int i = 0; i < neighbors.size(); i++)
	{
		if (j == 0)
		{
			territorytofind = neighbors[i];
			for (int k = 0; k < territories.size(); k++)
			{
				if (territorytofind.compare(territories[k]->getNameTerritory()) == 0)
				{
					o = k;
					t_origin = territories[k];
					break;
				}
			}
		}
		if (j > 0 && !(neighbors[i].find("|") != string::npos))
		{
			for (int k = 0; k < territories.size(); k++)
			{
				if (neighbors[i].compare(territories[k]->getNameTerritory()) == 0)
				{
					d = k;
					add_edge(o, k);
					t_destination = territories[k];
					t_origin->addNeighbor(t_destination);
					break;
				}
			}
		}
		j++;
		if (neighbors[i].find("|") != string::npos)
			j = 0;
	}
	//validate();
}
Map::Map(const Map& other) 
{
	this->continents.clear();
	this->continents.shrink_to_fit();
	this->territories.clear();
	this->territories.shrink_to_fit();
	if (this->adj != nullptr)
	{
		for (int i = 0; i < this->n; i++)
			delete[] adj;
		delete[] adj;
	}
	this->adj = other.adj;
	this->continents.assign(other.continents.begin(), other.continents.end());
	this->territories.assign(other.territories.begin(), other.territories.end());
	validate();
}
Map& Map::operator=(const Map other) noexcept
{
	if (this != &other)
	{
		//Releaing the resources
		this->continents.clear();
		this->continents.shrink_to_fit();
		this->territories.clear();
		this->territories.shrink_to_fit();
		if (this->adj != nullptr)
		{
			for (int i = 0; i < this->n; i++)
				delete[] adj;
			delete[] adj;
		}
		//Copying the data
		this->adj = other.adj;
		//Deep Copy
		this->continents.assign(other.continents.begin(), other.continents.end());
		this->territories.assign(other.territories.begin(), other.territories.end());
		validate();
	}
	return *this;
}
ostream& operator<<(ostream& out, const Map& c)
{
	for (Continent* ct : c.continents)
		out << *ct;
	return out;
}
Map::~Map() {
	for (int i = 0; i < this->n; i++)
		delete[] adj[i];
	delete[] adj;
}


/* --- Map Class --- */
/* --- Accessors & Modifiers --- */


void Map::add_edge(const int o, const int d) {
	if (o > this->n || d > this->n || o < 0 || d < 0)
		cout << "Invalid Edge" << endl;
	else
		adj[o][d] = true;
}
void Map::remove_edge(const int o, const int d) {
	if (o > this->n || d > this->n || o < 0 || d < 0)
		cout << "Invalid Edge" << endl;
	else
		adj[o][d] = false;
}
int Map::getSizeofMap() { return this->n; }
bool Map::isConnected() {
	return isGraphConnected(this->n, this->adj);
}
bool Map::validate()
{
	bool connected = false;
	// Check if the graph is connected using Adjacency Matrix
	connected = isGraphConnected(this->n, this->adj);
	cout << "First Test: " << endl;
	cout << "\t Is map Connected? " << (connected == 0 ? "Non" : "Yes") << endl;
	cout << "Second Test: " << endl;
	// Loops through all the Continents and check if they are connected subgraph
	for (Continent* c : this->continents)
	{
		c->Populate(this->territories);
		cout << "\t Is " << c->getName() << " Connected ? " << (c->isConnected() == 0 ? "Non" : "Yes") << endl;
	}
	for (Territory* t : this->territories)
	{
		for (int i = 0; i < this->territories.size(); i++)
		{
			if (t->getNameTerritory() == this->territories[i]->getNameTerritory())
			{
				if (t->getContinentName() != this->territories[i]->getContinentName())
				{
					cout << "Territory: " << t->getNameTerritory() << " is in more than one Continent: " << t->getContinentName() << " and " << this->territories[i]->getContinentName() << endl;
					connected = false;
				}
			}
		}
	}
	cout << "Third Test: " << endl;
	cout << "\t Duplicate Territories? " << (connected != 0 ? "Non" : "Yes") << endl;
	return connected;
}

vector<Territory*> Map::getTerritoriesByContinent(int continent)
{
	vector<Territory*> continentCountries;
		
	for (Territory* t : this->territories) {
		if (t->getContinent() == continent) {
			continentCountries.push_back(t);
		}
	}

	return continentCountries;
}

int Map::calculateContinentBonus(Player* player)
{
	int continentBonus = 0;
	for (Continent* c : getContinents()) {
		bool pHasAllT = true;
		for (Territory* t : c->getTerritories()) {
			if (player->getPlayerName() != t->getOwner()->getPlayerName()) {
				pHasAllT = false;
			}
		}
		if (pHasAllT)
			continentBonus = continentBonus + c->getPowerUP();
	}
	return continentBonus;
}

//Method for Player class
Territory* Map::getTerritoryByID(int id) {
    for(auto it: getTerritories()){
        if(it->getID() == id){
            return it;
        }
    }
    return nullptr;
}

const vector<Continent*>& Map::getContinents() const
{
	return this->continents;
}

const vector<Territory*>& Map::getTerritories() const
{
	return this->territories;
}