#include "../header_files/Player.h" // Including the header file Player

// ---- Constructor methods ----

// Default constructor
Player::Player()
{
	this->m_PlayerName = "NoName"; // Copy initialization
	this->m_PlayerHand = new Hand(); //deep copy
	//this->m_Playerorderslist = new OrdersList(); //deep copy
	this->m_reinforcementPool = 100; //Default pool for a player

	
}

// Constructor with name only
Player::Player(const string& name)
{
	this->m_PlayerName = name; // Copy initialization
	this->m_PlayerHand = new Hand(); //deep copy
	this->m_Playerorderslist = new OrdersList(); //deep copy
	this->m_reinforcementPool = 100; //Default pool for a player
}

// Constructor with name and hand
Player::Player(const string& name, Hand* hand) : m_PlayerName(name), m_PlayerHand(hand)
{
	this->m_PlayerName = name; // Copy initialization
	this->m_PlayerHand = hand; //deep copy
	this->m_Playerorderslist = new OrdersList(); //deep copy
	this->m_reinforcementPool = 100; //Default pool for a player

}

//Player::Player(const string& name, Hand* hand, GameEngine* game) : m_PlayerName(name), m_PlayerHand(hand), m_gameEngine(game)
//{
//	this->m_PlayerName = name; // Copy initialization
//	this->m_PlayerHand = hand; //deep copy
//	this->m_Playerorderslist = new OrdersList(); //deep copy
//	this->m_reinforcementPool = 100; //Default pool for a player
//
//}

// Constructor with name, hand, and game
Player::Player(const string& name, Hand* hand, GameEngine* game) : m_PlayerName(name), m_PlayerHand(hand), m_reinforcementPool(0), m_gameEngine(game){

	m_Playerorderslist = new OrdersList();
	m_strategy = nullptr; // needs to be initialized using setStrategy.
	m_hasBeenAttacked = false;
	//this->m_Playerorderslist = new OrdersList(this, *new vector<Order*>);
}

// Copy constructor
Player::Player(const Player& player)
{
	this->m_PlayerName = player.m_PlayerName;
	this->m_PlayerHand = new Hand(*(player.m_PlayerHand)); // deep copy 
	this->m_OwnedTerritories = player.m_OwnedTerritories;
	this->m_Playerorderslist = new OrdersList(*(player.m_Playerorderslist)); //deep copy
	this->m_reinforcementPool = player.m_reinforcementPool;
	this->m_gameEngine = player.m_gameEngine;
	this->m_strategy = player.m_strategy;

}


// ---- Assignment operator ----
Player& Player::operator=(const Player& player)
{
	delete this->getPlayerHand();
	this->m_OwnedTerritories.clear();
	delete this->m_Playerorderslist;
	delete this->m_gameEngine;
	delete this->m_strategy;

	this->m_PlayerName = player.m_PlayerName;
	this->m_PlayerHand = new Hand(*(player.m_PlayerHand)); // Deep copy of hand is made by calling new
	this->m_OwnedTerritories = player.m_OwnedTerritories;
	this->m_Playerorderslist = new OrdersList(*(player.m_Playerorderslist)); //deep copy
	this->m_reinforcementPool = player.m_reinforcementPool;
	this->m_gameEngine = player.m_gameEngine;
	this->m_strategy = player.m_strategy;

	return *this;
}

// ---- Destructor ----
Player::~Player()
{
	delete this->m_PlayerHand; // Delete pointer to hand
	this->m_PlayerHand = nullptr; // avoiding dangling pointer
	delete this->m_Playerorderslist; // Delete pointer to ordersList
	this->m_Playerorderslist = nullptr; // avoiding dangling pointer
	this->m_OwnedTerritories.clear(); // empty the owned territories vector
	delete this->m_gameEngine;
	this->m_gameEngine = nullptr;
	delete this->m_strategy;
	this->m_strategy = nullptr;
}
// ---- Mutator methods ----

// add a pointer to territory in the Ownedvector's player
void Player::addTerritory(Territory* territory)
{
	/*if (std::find(m_OwnedTerritories.begin(), m_OwnedTerritories.end(), territory) == m_OwnedTerritories.end())
	{
		m_OwnedTerritories.push_back(territory);
		territory->getOwner()->removeOwnedTerritory(territory);
		territory->setOwner(this);
	}*/

	this->m_OwnedTerritories.push_back(territory);
	territory->setOwner(this);

}

// edit or add the name of player 
void Player::SetName(const string& name)
{
	this->m_PlayerName = name;
}

void Player::setReinforcementPool(int rP)
{
	m_reinforcementPool = rP;
}

void Player::add2ReinforecemntPool(int rP)
{
	m_reinforcementPool += rP;
}

// set the hand of a player
void Player::SetHand(Hand* hand)
{
	this->m_PlayerHand = hand;
}

//Sets the strategy to any of the strategy types given
void Player::setStrategy(PlayerStrategy* strategy)
{
	this->m_strategy = strategy;
}


vector<Territory*> Player::toAttack()
{
	return this->m_strategy->toAttack();
}

// Defend method that returns a vector of all the territories owned by the player
//These territories have to be defended from other players.
vector<Territory*>& Player::toDefend() {
	return this->m_strategy->toDefend();
}



// Create a new order and add to order list


//void Player::issueOrder(string order_name)
//{
//	OrderOperation* op = new OrderOperation;
//	Order* o = op->createOrder(order_name);
//	this->m_Playerorderslist->addOrder(o);
//	delete op;
//}


bool Player::issueOrder()
{
	return this->m_strategy->issueOrder();
}


bool Player::ownsTerritory(Territory* territory) {
	for (Territory* t : m_OwnedTerritories) {
		if (t->getNameTerritory() == territory->getNameTerritory())
			return true;
	}
	return false;
}

bool Player::ownsTerritory(int ID) {
	for (Territory* t : m_OwnedTerritories) {
		if (t->getID() == ID)
			return true;
	}
	return false;
}
// Add territory to own
void Player::addOwnedTerritory(Territory* territory) {
	m_OwnedTerritories.push_back(territory);
	territory->setOwner(this);
}

void Player::removeOwnedTerritory(Territory* territory) {
	std::vector<Territory*>::iterator it = std::find(m_OwnedTerritories.begin(), m_OwnedTerritories.end(), territory);
	if (it != m_OwnedTerritories.end())
		m_OwnedTerritories.erase(it);
}


// Stream insertion operator, returns player's name, territories that he ownes and his hand of cards.
ostream& operator<<(ostream& out, const Player& player) {
	out << "-> Player's name: " << player.getPlayerName() << ": owned territories are: " << endl;
	for (Territory* t : player.m_OwnedTerritories)
	{
		out << t->details();
		out << endl;
	}
	out << "His/Her hand: " << endl;
	std::cout << *(player.getPlayerHand()) << std::endl;
	return out;

}

// ---- Accessor methods ----

string Player::getPlayerName() const { return this->m_PlayerName; }

vector<Territory*>& Player::getPlayerTerritories() { return this->m_OwnedTerritories; }

Hand* Player::getPlayerHand() const { return this->m_PlayerHand; }

OrdersList* Player::getPlayerOrdersList() const { return this->m_Playerorderslist; }

int Player::getReinforcementPool() const { return m_reinforcementPool; }

GameEngine* Player::getGameEngine() const { return m_gameEngine; }

//Returns a player strategy
PlayerStrategy* Player::getStrategy() const{ return this->m_strategy; }

int Player::getNumTerritories()
{
	return m_OwnedTerritories.size();
}


//Used to add the name of a player to a list of players that cannot be attacked
void Player::beginCeasefire(const string& name)
{
	for (int i = 0; i < cannotAttack.size(); i++) {
		if (name == cannotAttack[i]) {

			cout << "There is currently a ceasefire with " << name << endl;
			return;
		}
	}

	cannotAttack.push_back(name);
	cout << "The ceasefire begins" << endl;
}

//Used to remove the name of a player from a list of players that cannot be attacked
void Player::endCeasefire(const string& name)
{
	for (int i = 0; i < cannotAttack.size(); i++) {
		if (name == cannotAttack[i]) {
			cannotAttack.erase(cannotAttack.begin() + i);
			cout << "The ceasefire has ended" << endl;
			return;
		}
	}
	cout << "There was no such ceasefire with " << name << endl;
}



// implemeting stategy pattern
// ---- A3 -- PART 1 -----

//bool Player::issueOrder()
//{
//	return m_strategy->issueOrder();
//}
//
//vector<Territory*> Player::toAttack()
//{
//	
//	return m_strategy->toAttack();
//}
//
//vector<Territory*> Player::toDefend() {
//
//	return m_strategy->toDefend();
//}



bool Player::getHasBeenAttacked()
{
	return m_hasBeenAttacked;
}

void Player::setHasBeenAttacked(bool aBool)
{
	m_hasBeenAttacked = aBool;
}