#include "../header_files/Orders.h"


 //The labels of the orders, which are constant and static.
 
const string deploy::label = "Deploy";
const string advanceOrder::label = "Advance";
const string bomb::label = "Bomb";
const string blockade::label = "Blockade";
const string airlift::label = "Airlift";
const string negotiate::label = "Negotiate";


/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/

Order::Order() {}
Order::Order(const Order&) {}
Order& Order::operator = (const Order& order) { return *this; }
void Order::setEffect(string eff) {}
string Order::getEffect() { return "Effect"; }
Order::~Order() {}

// Default constructor of OrderList, designed to hold a list of valid orders and carry out basic list functions

/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/
OrdersList::OrdersList()
{
    //this->ordersListOwner = new Player();
    // this->Attach(ordersListOwner->getGameEngine()->_observer);
}

OrdersList::OrdersList(const OrdersList& other)
{
    this->ordersListOwner = other.ordersListOwner;
    this->orders = other.orders;
    this->Attach(ordersListOwner->getGameEngine()->_observer);
}

OrdersList::OrdersList(Player* ordersListOwner, vector<Order*>& orders) {

    this->ordersListOwner = ordersListOwner;
    this->orders = orders;
    this->Attach(ordersListOwner->getGameEngine()->_observer);
}



//OrderList destructor

OrdersList::~OrdersList()
{
    delete this->ordersListOwner;

    int listSize = orders.size();

    for (int i = 0; i < listSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete this->orders[i];
}

/**
 * Copy constructor: makes a deep copy of a list
 * @param oldList
 
OrdersList::OrdersList(const OrdersList& oldList)
{
    int listSize = oldList.orders.size();
    orders = vector<Order*>(listSize);

    for (int i = 0; i < listSize; i++) // Same objects, but in different memory locations.
        orders[i] = oldList.orders[i]->clone();

    cout << "The list has been copied!" << endl;
}


// Order Constructors
Order::Order() = default;

Order& Order::operator= (const Order& order)= default; //Assignment operator overload

Order::Order(const Order&)
{
}

void Order::setEffect(string eff) {

    this->effect = std::move(eff);
}

string Order::getEffect() {

    return this->effect;
}

string Order::stringToLog()
{
    return "Order: " + getLabel() + ", Effect: " + getEffect();
}
 //Destructors

OrdersList::~OrdersList()
{
    
}

Order::~Order()
{
}

deploy::~deploy()
{
    delete this->player;
    delete this->target;
}

advanceOrder::~advanceOrder()
{
    delete this->player;
    delete this->source;
    delete this->target;
    delete this->enemy;
}

bomb::~bomb()
{
    delete this->player;
    delete this->target;
    delete this->deck;
}

blockade::~blockade()
{
    delete this->player;
    delete this->target;
    delete this->deck;
    delete this->neutral;
}

airlift::~airlift()
{
    delete this->player;
    delete this->source;
    delete this->target;
    delete this->deck;
}

negotiate::~negotiate()
{
    delete this->player;
    delete this->target;
    delete this->deck;
}

// @param o Method that adds an order to the orders vector

void OrdersList::addOrder(Order* o)
{
    if (o == nullptr) // See OrderOperation.
        cout << "This is a null pointer! Adding operation failed!" << endl;
    else
    {
        orders.push_back(o);
        cout << "Order has been added to the list! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that deletes an order
 * @param pos
 */

void OrdersList::addOrder(Order* o)
{
    if (o == nullptr) // See OrderOperation.
        cout << "This is a null pointer! Adding operation failed!" << endl;
    else
    {
        orders.push_back(o);
        cout << "Order has been added to the list! Your list now looks like: \n";
        cout << *this << endl;
    }

    Notify(this);
}

string OrdersList::stringToLog()
{    
    return "Command: " + orders.back()->getLabel();
}


void OrdersList::remove(int pos)
{
    int listSize = orders.size();

    if (listSize == 0) // Empty list so nothing to be done.
        cout << "Nothing to erase!" << endl;
    else if (pos > listSize || pos < 1) // Bounds check.
        cout << "Please select a valid position!" << endl;
    else
    {
        delete orders[pos - 1]; // Order objects are dynamically allocated, so frees memory.
        orders.erase(orders.begin() + pos - 1); // Once memory freed, delete actual pointer from list.
        cout << "Erase at position " << pos << " successful! Your list now looks like: \n";
        cout << *this << endl;
    }
}

void OrdersList::remove(Order* order, int index)
{
    if (this->orders.size() == 0)
        cout << "Nothing to delete" << endl;
    else if (index > this->orders.size() || index < 0)
        cout << "Out of bound index" << endl;
    else
    {
        //this->orders.erase((this->orders.begin() + index));
        this->orders[index] = nullptr;
        cout << "Order Deleted" << endl;
    }
}

void OrdersList::update()
{
    this->orders.erase(std::remove(begin(this->orders), end(this->orders), nullptr),end(this->orders));
}

/**
 * Method that moves an order
 * @param pos1
 * @param pos2
 */
void OrdersList::move(int pos1, int pos2)
{
    int listSize = orders.size(); // Compute size to check if a move can be performed.

    if (listSize == 0) // Empty list so nothing to be done.
        cout << "There is nothing to move!" << endl;
    else if (listSize == 1) // Only 1 item in the list, so nothing to be done.
        cout << "You need at least two orders to perform a swap!" << endl;
    else if (pos1 > listSize || pos2 > listSize || pos1 < 1 || pos2 < 1) // Bounds check.
        cout << "One or both of your positions are invalid!" << endl;
    else
    {
        Order* temp = orders[pos1 - 1]; // Swap pointers. Address of actual object unchanged.
        orders[pos1 - 1] = orders[pos2 - 1];
        orders[pos2 - 1] = temp;
        cout << "Order " << pos1 << " and Order " << pos2 << " have been swapped! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that executes an order
 */
void OrdersList::executeOrders()
{
    int listSize = orders.size();

    if (listSize == 0)
        cout << "Nothing to execute!" << endl;
    else
    {
        for (int i = 0; i < listSize; i++)
        {
            orders[i]->execute();
            delete orders[i];
        }

        orders.clear();
        cout << "Orders have been executed!" << endl;
    }
}

vector<Order*>& OrdersList::getOrders()
{
    return this->orders;
}




/**
 * Assignment operator
 * @param rhsList
 * @return
 */
OrdersList& OrdersList::operator=(const OrdersList& rhsList) // Releases resources by LHS and deep-copy
{                                                            // to RHS
    delete this->ordersListOwner;

    if (&rhsList == this) // Checks for self assignment
        return *this;

    int lhsListSize = orders.size();
    int rhsListSize = rhsList.orders.size();

    for (int i = 0; i < lhsListSize; i++)
        delete this->orders[i];

    orders = vector<Order*>(rhsListSize); // Reallocate memory for vector of size RHS

    for(int i = 0; i < rhsListSize; i++)
        orders[i] = rhsList.orders[i]->clone(); // Clone RHS element into LHS

    this->ordersListOwner = rhsList.ordersListOwner;
    this->Attach(ordersListOwner->getGameEngine()->_observer);

    return *this;
}

/**
 * Prints the list using cout.
 * @param strm
 * @param ol
 * @return
 */
ostream& operator<<(ostream& out, const OrdersList& ol)
{
    int listSize = ol.orders.size(); // For iteration
    const int MAX_WIDTH = 9; // To force the amount of space a string takes.
    const char separator = ' '; // If string.length() < 9, fill with empty spaces.

    for (int i = 0; i < listSize; i++)
        out << left << setw(MAX_WIDTH) << setfill(separator) << i + 1 << " | "; // Left formatted

    out << "\n";

    for (int i = 0; i < listSize; i++)
        out << left << setw(MAX_WIDTH) << setfill(separator) << ol.orders[i]->getLabel() << " | ";

    out << "\n";

    return out;
}

//OrdersList input stream operator
istream& operator>>(istream& in, OrdersList&)
{
    return in;
}

//deploy constructors
deploy::deploy()
{
    this->player = new Player();
    this->target = new Territory();
    this->reinforcements = 0;
    //this->game = new GameEngine();
    //this->Attach(game->_observer);

}

/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/

deploy::~deploy() {

    delete this->player;
    delete this->target;
    delete this->game;
}

deploy::deploy(Player* player, Territory* target, const int& reinforcements, GameEngine* game)
{
    
    this->player =player;
    this->target =target;
    this->reinforcements = reinforcements;
    this->game = game;
    this->Attach(game->_observer);
}

deploy::deploy(const deploy& other)
{
    this->player = other.player;
    this->target = other.target;
    this->reinforcements = other.reinforcements;
    this->game = other.game;
    this->Attach(game->_observer);
}

//deploy class operator
deploy& deploy::operator=(const deploy other)
{
    if (this != &other) {

        //Freeing existing resources
        delete this->player;
        delete this->target;
        delete this->game;

        //Copying the data
        this->player = other.player;
        this->target = other.target;
        this->reinforcements = other.reinforcements;
        this->game = other.game;
        this->Attach(game->_observer);

    }
    
    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string deploy::getLabel() const
{
    return label;
}



//advance constructors
advanceOrder::advanceOrder()
{
    this->player = new Player();
    this->source = new Territory();
    this->target = new Territory();
    this->enemy = new Player();
    this->numberArmies = 0;
    //this->game = new GameEngine();
    //this->Attach(game->_observer);

}

advanceOrder::advanceOrder(Player* player, Territory* source, Territory* target, Player* enemy, const int& numberArmies, GameEngine* game)
{
    
    this->player = player;
    this->source = source;
    this->target = target;
    this->enemy = enemy;
    this->numberArmies = numberArmies;
    this->game = game;
    this->Attach(game->_observer);

}

advanceOrder::advanceOrder(const advanceOrder& other)
{
    this->player = other.player;
    this->source = other.source;
    this->target = other.target;
    this->enemy = other.enemy;
    this->numberArmies = other.numberArmies;
    this->game = other.game;
    this->Attach(game->_observer);
}
//advance class operator
advanceOrder& advanceOrder::operator=(const advanceOrder other)
{
    //Freeing existing resources
    delete this->player;
    delete this->source;
    delete this->target;
    delete this->enemy;
    delete this->game;

    //Copying the data
    this->player = other.player;
    this->source = other.source;
    this->target = other.target;
    this->enemy = other.enemy;
    this->numberArmies = other.numberArmies;
    this->game = other.game;
    this->Attach(game->_observer);

    return *this;
}

/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/

advanceOrder::~advanceOrder() {

    delete this->player;
    delete this->source;
    delete this->target;
    delete this->enemy;
    delete this->game;

}

/**
 * Returns the label of the order.
 * @return
 */
string advanceOrder::getLabel() const
{
    return label;
}

//bomb constructors
bomb::bomb()
{
    this->player = new Player();
    this->target = new Territory();
    this->deck = new Deck();
    //this->game = new GameEngine();
    //this->Attach(game->_observer);
}

/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/

bomb::~bomb() {

    delete this->player;
    delete this->target;
    delete this->deck;
    delete this->game;
}

bomb::bomb(Player* player, Territory* target, Deck* deck, GameEngine* game)
{
    
    this->player = player;
    this->target = target;
    this->deck = deck;
    this->game = game;
    this->Attach(game->_observer);

}

bomb::bomb(const bomb& other)
{
    this->player = other.player;
    this->target = other.target;
    this->deck = other.deck;
    this->game = other.game;
    this->Attach(game->_observer);
}

//bomb class operator
bomb& bomb::operator=(const bomb other)
{
    //Freeing existing resources
    delete this->player;
    delete this->target;
    delete this->deck;
    delete this->game;

    //Copying the data
    this->player = other.player;
    this->target = other.target;
    this->deck = other.deck;
    this->game = other.game;
    this->Attach(game->_observer);

    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string bomb::getLabel() const
{
    return label;
}

//blockade constructors
blockade::blockade()
{
    this->player = new Player();
    this->target = new Territory();
    this->deck = new Deck();
    this->neutral = new Player();
    //this->game = new GameEngine();
    //this->Attach(game->_observer);
}

/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/

blockade::~blockade() {

    delete this->player;
    delete this->target;
    delete this->deck;
    delete this->neutral;
    delete this->game;

}

blockade::blockade(Player* player, Territory* target, Deck* deck, Player* neutral, GameEngine* game)
{
    this->game = game;
    this->player = player;
    this->target = target;
    this->deck = deck;
    this->neutral = neutral;
    this->Attach(game->_observer);
}

blockade::blockade(const blockade& copy)
{
    this->player = copy.player;
    this->target = copy.target;
    this->deck = copy.deck;
    this->neutral = copy.neutral;
    this->game = copy.game;
    this->Attach(game->_observer);
}

//blockade class operator
blockade& blockade::operator=(const blockade copy)
{
    //Freeing existing resources
    delete this->player;
    delete this->target;
    delete this->deck;
    delete this->neutral;
    delete this->game;

    //Copying the data
    this->player = copy.player;
    this->target = copy.target;
    this->deck = copy.deck;
    this->neutral = copy.neutral;
    this->game = copy.game;
    this->Attach(game->_observer);

    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string blockade::getLabel() const
{
    return label;
}

//airlift constructors
airlift::airlift()
{
    this->player = new Player();
    this->source = new Territory();
    this->target = new Territory();
    this->numberOfArmies = 0;
    this->deck = new Deck();
    //this->game = new GameEngine();
    //this->Attach(game->_observer);
    
}

/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/

airlift::~airlift() {

    delete this->player;
    delete this->source;
    delete this->target;
    delete this->deck;
    delete this->game;
}

airlift::airlift(Player* player, Territory* source, Territory* target, const int numberOfArmies, Deck* deck, GameEngine* game)
{
    this->game = game;
    this->Attach(game->_observer);
    this->player = player;
    this->source = source;
    this->target = target;
    this->numberOfArmies = numberOfArmies;
    this->deck = deck;
}

airlift::airlift(const airlift& copy)
{
    this->player = copy.player;
    this->source = copy.source;
    this->target = copy.target;
    this->numberOfArmies = copy.numberOfArmies;
    this->deck = copy.deck;
    this->game = copy.game;
    this->Attach(game->_observer);
}

//airlift class operator
airlift& airlift::operator=(const airlift copy)
{

    //Freeing existing resources
    delete this->player;
    delete this->source;
    delete this->target;
    delete this->deck;
    delete this->game;

    this->player = copy.player;
    this->source = copy.source;
    this->target = copy.target;
    this->numberOfArmies = copy.numberOfArmies;
    this->deck = copy.deck;
    this->game = copy.game;
    this->Attach(game->_observer);

    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string airlift::getLabel() const
{
    return label;
}

//negotiate constructors
negotiate::negotiate()
{
    this->player = new Player();
    this->target = new Player();
    this->deck = new Deck();
    //this->game = new GameEngine();
    //this->Attach(game->_observer);
}

/*NOT THE ACTUAL IMPLEMENTATION; PLACEHOLDER TO NOT GET UNRESOLVED ERRORS*/

negotiate::~negotiate() {

    delete this->player;
    delete this->target;
    delete this->deck;
    delete this->game;
}

negotiate::negotiate(Player* player, Player* target, Deck* deck, GameEngine* game)
{
    this->game = game;
    this->Attach(game->_observer);
    this->player = player;
    this->target = target;
    this->deck = deck;
}

negotiate::negotiate(const negotiate& copy)
{
    this->player = copy.player;
    this->target = copy.target;
    this->deck = copy.deck;
    this->game = copy.game;
    this->Attach(game->_observer);
}

//negotiate class operator
negotiate& negotiate::operator=(const negotiate copy)
{
    //Freeing existing resources
    delete this->player;
    delete this->target;
    delete this->deck;
    delete this->game;

    //Copying the data
    this->player = copy.player;
    this->target = copy.target;
    this->deck = copy.deck;
    this->game = copy.game;
    this->Attach(game->_observer);

    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string negotiate::getLabel() const
{
    return label;
}

/**
 * Works in conjunction with printOrder() from subclasses to polymorphically
 * give information about a specific order using cout.
 * @param strm
 * @param o
 * @return
 */
ostream& operator<<(ostream& out, const Order& o)
{
    return o.printOrder(out);
}

istream& operator>>(istream& in, Order&)
{
    return in;
}

ostream& operator<<(ostream& out, const deploy& d)
{
    return d.printOrder(out);
}

istream& operator>>(istream& in, deploy&)
{
    return in;
}

ostream& operator<<(ostream& out, const advanceOrder& a)
{
    return a.printOrder(out);
}

istream& operator>>(istream& in, advanceOrder&)
{
    return in;
}

ostream& operator<<(ostream& out, const bomb& b)
{
    return b.printOrder(out);
}

istream& operator>>(istream& in, bomb&)
{
    return in;
}

ostream& operator<<(ostream& out, const blockade& b)
{
    return b.printOrder(out);
}

istream& operator>>(istream& in, blockade&)
{
    return in;
}

ostream& operator<<(ostream& out, const airlift& a)
{
    return a.printOrder(out);
}

istream& operator>>(istream& in, airlift&)
{
    return in;
}

ostream& operator<<(ostream& out, const negotiate& n)
{
    return n.printOrder(out);
}

istream& operator>>(istream& in, negotiate&)
{
    return in;
}

ostream& operator<<(ostream& out, const OrderOperation& o)
{
    return out;
}

istream& operator>>(istream& in, OrderOperation&)
{
    return in;
}




/**
 * Does not print anything useful for this assignment.
 * @param out
 * @return
 */
ostream& deploy::printOrder(ostream& out) const
{
    return out << "deploy order!";
}

ostream& advanceOrder::printOrder(ostream& out) const
{
    return out << "advance order!";
}

ostream& bomb::printOrder(ostream& out) const
{
    return out << "bomb order!";
}

ostream& blockade::printOrder(ostream& out) const
{
    return out << "blockade order!";
}

ostream& airlift::printOrder(ostream& out) const
{
    return out << "airlift order!";
}

ostream& negotiate::printOrder(ostream& out) const
{
    return out << "negotiate order!";
}

/**
 * For this assignment, validation is not defined.
 * @return
 */
bool deploy::validate() const
{

    cout << "Validating Deploy...\n";

    bool owned=false;
    bool enoughArmies=false;
    for (auto territory : player->getPlayerTerritories()) {
        if (target->getOwner() == territory->getOwner()) {
            owned = true;
            break;
        }
    }
    if (!owned) {
        cout << "Territory" << *target << " is not owned by Player " << player->getPlayerName() << endl;
    }
    if (reinforcements <= player->getReinforcementPool()) {
        enoughArmies = true;
    }
    else {
        cout << "Player " << player->getPlayerName() << " does not have enough reinforcements to deploy " 
             << reinforcements << " armies" << endl;
    }
   
    return owned && enoughArmies;

}

bool advanceOrder::validate() const
{
    cout << "Validating Advance...\n";

    bool owned = false;
    bool is_neighbour = false;
    bool enough_units = false;

    for (auto territory : player->getPlayerTerritories()) {
        if (source->getID() == territory->getID()) {
            owned = true;
            break;
        }
    }
    if (!owned) {
        cout << "Source " << *source << " is not owned by " << *player << endl;
    }
    // must check that target territory is a neightbour
    for (auto neighbour : source->getNeighbors()) {
        if (target->getID() == neighbour->getID()) {
            is_neighbour = true;
            break;
        }
    }
    if (!is_neighbour) {
        cout << "Target " << *target << " is not a neighbour of source " << *source << endl;
    }
    // must check if player has enough units on source territory
    if (numberArmies <= source->getNumberArmies() - 2) {
        enough_units = true;
    }
    else {
        cout << "Source " << *source << " does not have the sufficient armies requested " << endl;
    }

    return owned && is_neighbour && enough_units;

}

bool bomb::validate() const
{
    cout << "Validating Bomb...\n";
    
    bool target_owned = false;
    bool has_card = false;
    bool is_neighbour = false;

    Card* bomb= new Card(1);
    
    //Must check that the target is not owned by the player issuing the order
    for (auto territory : player->getPlayerTerritories()) {
        if (target->getOwner() == territory->getOwner()) {
            target_owned = true;
            break;
        }
    }
    if (target_owned) {

        cout << "Territory " << *target << " is owned by Player " << player->getPlayerName() << endl;
    }

    //NOTE: Accessor for list of cards at hand probably needed
    for (auto card : player->getPlayerHand()->getCards()) {
        if (bomb->getType()==card->getType()){
            has_card = true;
            break;
        }

    }

    if (!has_card) {

        cout << "Player " << *player << " does not have the card of bomb type in their hand" << endl;
    }
        
    
    while (!is_neighbour) {
        for (auto territory : player->getPlayerTerritories()) {
            for (auto neighbour : territory->getNeighbors()) {
                if (target->getID() == neighbour->getID()) {
                    is_neighbour = true;
                }
            }
        }
        break;
    }

    if (!is_neighbour) {

        cout << "Territory " << *target << " is not a neighbour of any of player" << *player << "'s territories" << endl;
    }

    return !target_owned && has_card && is_neighbour;
}

bool blockade::validate() const
{
    cout << "Validating Blockade...\n";

    bool target_owned = false;
    bool has_card = false;

    //Must check that the target is owned  by the player issuing the order
    for (auto territory : player->getPlayerTerritories()){
        if (target->getOwner()==player){
            target_owned = true;
            break;
        }
    }
    if (!target_owned) {

        cout << "Territory " << *target << " is not owned by player " << *player << endl;
    }

    Card* blockade = new Card(2); //Blockade card
    for (auto card : player->getPlayerHand()->getCards()){
        if (blockade->getType()==card->getType()){

            has_card = true;
            break;
        }
    }

    if (!has_card) {

        cout << "Player " << *player << " does not have the blockade card in his hand" << endl;
    }


    return target_owned && has_card;
    
}

bool airlift::validate() const
{
    cout << "Validating Airlift...\n";

    bool source_owned = false;
    bool target_owned = false;
    bool has_card = false;
    bool enoughArmies = false;

    for (auto territory : player->getPlayerTerritories()) {

        if (source->getOwner() == territory->getOwner()) {

            source_owned = true;
        }

        if (target->getOwner() == territory->getOwner()) {

            target_owned = true;
        }

        if (source_owned == true && target_owned == true) {

            break;
        }
    }

    if (!source_owned) {

        cout << "Territory " << *source << " is not owned by player " << *player << endl;
    }

    if (!target_owned) {

        cout << "Territory " << *target << " is not owned by player " << *player << endl;
    }

    Card* airlift = new Card(3); //airlift card
    for (auto card : player->getPlayerHand()->getCards()) {
        if (airlift->getType() == card->getType()) {

            has_card = true;
            break;
        }
    }

    if (!has_card) {

        cout << "Player " << *player << " does not have the airlift card in his hand" << endl;
    }

    if (numberOfArmies <= source->getNumberArmies() - 2) {

        enoughArmies = true;
    }
    else {
        cout << "Source " << *source << " does not have the sufficient armies requested " << endl;
    }

    return source_owned && target_owned && has_card && enoughArmies;
}

bool negotiate::validate() const
{
    bool target_is_yourself=true;
    bool has_card = false;


    cout << "Validating Negotiate...\n";

    if (player->getPlayerName() != target->getPlayerName()) {

        target_is_yourself = false;
    }
    else {

        cout << "Player " << *player << " cannot negotiate with themselves" << endl;
    }

    Card* diplomacy = new Card(4); //Diplomacy card
    for (auto card : player->getPlayerHand()->getCards()) {

        if (diplomacy->getType() == card->getType()) {

            has_card = true;
        }
    }

    if (!has_card) {

        cout << "Player " << *player << " does not have the diplomacy card" << endl;
    }

    return !target_is_yourself && has_card;
}


string Order::stringToLog()
{
    return "Effect: " + effect;
}

/**
 * Validates an order and proceeds accordingly. For this assignment, execution is not defined.
 */
void deploy::execute()
{
    if (!validate()) {
        cout << "Deploy order cannot be executed" << endl;
        return;
    }
    cout << "Performing " << *this << endl;

    // transfer units from reinforcement pool
    cout << reinforcements << " Units deployed to [" << target->getNameTerritory() << "]" << endl;
    cout << "Old Nunber of Units: " << target->getNumberArmies() << endl;
    target->setNumberArmies(target->getNumberArmies() + reinforcements);
    cout << "New Nunber of Units: " << target->getNumberArmies() << endl;
    player->setReinforcementPool(player->getReinforcementPool() - reinforcements);
    
    Notify(this);
}

void advanceOrder::execute()
{
    cout << "Attacking Territory [" + this->source->getNameTerritory() + "] Owned by [" + this->source->getOwner()->getPlayerName() + "] with " + std::to_string((this->source->getNumberArmies() - 2)) + " Units" << endl;
    source->printNeighbors();
    cout << "Defending Territory [" + this->target->getNameTerritory() + "] Owned by [" + this->target->getOwner()->getPlayerName() + "] with " + std::to_string(this->target->getNumberArmies()) + " Units" << endl;
    target->printNeighbors();
    if (!validate()) {
        cout << "Advance order cannot be executed" << endl;
        return;
    }
    cout << "Performing " << *this << endl;
    
    /*
    Seeing if target territory belongs to player issuing the order. 
    Execution stops if they match
    */
    for (auto territory : player->getPlayerTerritories()) {
        if (target->getID() == territory->getID()) {
            target->setNumberArmies(target->getNumberArmies() + numberArmies);
            source->setNumberArmies(source->getNumberArmies() - numberArmies);
            return;
        }
    }
    // We now know the target is an enemy
    //rand(time(NULL)); we dont need to seed it has to be done in main.
    // Continue attacks until one territory is out of armies
    
    while (source->getNumberArmies() - numberArmies > 2 && target->getNumberArmies() > 0) {
        int attack_chance = rand() % 100 + 1;
        if (attack_chance < 60) {  // 60% chance
            target->setNumberArmies(target->getNumberArmies() - 1);
        }
        int defend_chance = rand() % 100 + 1;
        if (defend_chance < 70) {  // 70% chance
            source->setNumberArmies(source->getNumberArmies() - 1);
        }
    }
    // tells the target owner it has been attacked
    target->getOwner()->setHasBeenAttacked(true);
    /*
    Ownership of territory is transferred to the attacking player,
    surviving soldiers from the attacking side are transferred to the gained territoty,
    and the attacker is given 1 of 4 available cards
    */
    if (target->getNumberArmies() <= 0) {

        target->setOwner(player);
        target->setNumberArmies(source->getNumberArmies() - numberArmies);
        player->addTerritory(target);
        enemy->removeOwnedTerritory(target);
        /*for (int i = 0; 0 < enemy->getPlayerTerritories().size(); i++) {

            if (enemy->getPlayerTerritories()[i]->getNameTerritory() == target->getNameTerritory()) {
                cout << "Size of Territories before Removal: " + std::to_string(enemy->getPlayerTerritories().size()) << endl;
                enemy->getPlayerTerritories().erase(enemy->getPlayerTerritories().begin()+i);
                cout << "Size of Territories After Removal: " + std::to_string(enemy->getPlayerTerritories().size()) << endl;
                player->addTerritory(target);
                break;
            }

        }*/
        /*
        Cards are represented by digits. There are 4 cards, each tied to a specific order:

        '1'="Bomb"
        '2'="Blockade"
        '3'="Airlift"
        '4'="Negotiate"
        */
        player->getPlayerHand()->add(new Card((rand() % 4) + 1));
    }
    cout << "Result" << endl;
    cout << "Attacking Territory [" + this->source->getNameTerritory() + "] Owned by [" + this->source->getOwner()->getPlayerName() + "] with " + std::to_string((this->source->getNumberArmies())) + " Units" << endl;
    cout << "Defending Territory [" + this->target->getNameTerritory() + "] Owned by [" + this->target->getOwner()->getPlayerName() + "] with " + std::to_string(this->target->getNumberArmies()) + " Units" << endl;

    Notify(this);
}

void bomb::execute()
{
    if (!validate())
    {
        cout << "Bomb order cannot be executed!\n";
        return;
    }
    cout << "Performing " << *this << endl;

    // Playing card from hand
    Card* card = new Card(1); //Bomb card
    player->getPlayerHand()->returnCard(card, deck);

    //Bombs terrritory. Number of armies reduced to half
    target->setNumberArmies(floor(target->getNumberArmies() / 2));
    // tells the target owner it has been attacked
    target->getOwner()->setHasBeenAttacked(true);
    Notify(this);
}

void blockade::execute()
{
    if (!validate()) {

        cout << "Blockade order cannot be executed!\n";
        return;
    }

    cout << "Performing " << *this << endl;

    // Playing card from hand
    Card* card = new Card(2);

    player->getPlayerHand()->returnCard(card, deck);

    // create blockade
    if (neutral==nullptr){
      
        neutral = new Player();
        neutral->setStrategy(new NeutralPlayerStrategy(neutral));
    }

    target->setOwner(neutral);
    target->setNumberArmies(target->getNumberArmies() * 2);
    //for (int i = 0; 0 < player->getPlayerTerritories().size(); i++) {

    //    if (player->getPlayerTerritories().at(i)->getNameTerritory() == target->getNameTerritory()) {
    //        player->removeOwnedTerritory(player->getPlayerTerritories().at(i));
    //        neutral->addTerritory(target);
    //    }
    //}    

    player->removeOwnedTerritory(target);
    neutral->addTerritory(target);

    Notify(this);
}

void airlift::execute()
{
    if (!validate()){
    
       cout << "Airlift order cannot be executed!\n";
       return;
    }
        
    cout << "Performing " << *this << endl;

    // Playing card from hand
    Card* card = new Card(3);
    player->getPlayerHand()->returnCard(card, deck);

    //Transfer of armies to friendly territory
    source->setNumberArmies(source->getNumberArmies() - numberOfArmies);
    target->setNumberArmies(source->getNumberArmies() + numberOfArmies);

    Notify(this);
}

void negotiate::execute()
{
    if (!validate()) {

        cout << "Negotiate order cannopt be executed!\n";
        return;
    }

    cout << "Performing " << *this << endl;

    Card* card = new Card(4);
    player->getPlayerHand()->returnCard(card, deck);

    // disable attacks between players
    player->beginCeasefire(target->getPlayerName());
    target->beginCeasefire(player->getPlayerName());

    Notify(this);
        
}

/**
 * Since we have a list of pointers to an abstract class,
 * we need a way to polymorphically clone the objects in the
 * list if we ever decide to deep-copy the list. Calls the
 * compiler-generated copy constructor, which is OK since
 * these subclasses don't have object specific data members.
 * @return
 */
Order* deploy::clone() const
{
    return new deploy(*this);
}

Order* advanceOrder::clone() const
{
    return new advanceOrder(*this);
}

Order* bomb::clone() const
{
    return new bomb(*this);
}

Order* blockade::clone() const
{
    return new blockade(*this);
}

Order* airlift::clone() const
{
    return new airlift(*this);
}

Order* negotiate::clone() const
{
    return new negotiate(*this);
}

//OrderOperation constructors
OrderOperation::OrderOperation()
{
}

OrderOperation::OrderOperation(const OrderOperation&)
{
}

//OrderOperation class operator
OrderOperation& OrderOperation::operator=(const OrderOperation)
{
    return *this;
}

//OrderOperation destructor
OrderOperation::~OrderOperation()
{
}

/**
 * Creates an order based on user input. Only the strings below
 * are the possible orders in this game. If the user inputs a
 * string different than those listed, it returns a null pointer,
 * which is meant to be handled in OrdersList::addOrder().
 * 
 * Based on the instruction, valid orders for this game are mentioned below 'strings' (user input) 
 * If else it will return null pointer and handled in OrderList::addOrder().
 * @param orderType
 * @return
 */
Order* OrderOperation::createOrder(string orderType) const
{
    if (orderType == "deploy")
        return new deploy;
    else if (orderType == "advance")
        return new advanceOrder;
    else if (orderType == "bomb")
        return new bomb;
    else if (orderType == "blockade")
        return new blockade;
    else if (orderType == "airlift")
        return new airlift;
    else if (orderType == "negotiate")
        return new negotiate;
    else
        return nullptr;
}
