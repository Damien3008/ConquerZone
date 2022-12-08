#include "../header_files/PlayerStrategies.h"
#include "../header_files/Orders.h"
#include "../header_files/Player.h"
#include "../header_files/GameEngine.h"

#include <iostream>


//constructors
PlayerStrategy::PlayerStrategy() : m_player(new Player()) {}

PlayerStrategy::PlayerStrategy(Player* player) : m_player(player) {}

HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player) {}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player) {}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player) {}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player) { numTerritories = player->getNumTerritories(); }

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player) {}


//Player strat copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy& s) {
this->m_player = s.m_player;
}

//player strat assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& other) {
this->m_player = other.m_player;
return *this;
}

//Player strat ostream 
ostream& operator<<(ostream &out, const PlayerStrategy& a) {
	out << "Player name: " << a.m_player->getPlayerName() <<  " is Player Strategy" << endl;
	return out;
}

//Human
bool HumanPlayerStrategy::issueOrder()
{
	std::cout << "Human Player " + m_player->getPlayerName() + " issuing Order...\n";

	bool done = false;
	int possibleReinforcement = m_player->getReinforcementPool();
	//out << left << setw(MAX_WIDTH) << setfill(separator) << i + 1 << " | "; // Left formatted
	cout << "Possible Orders: deploy, advance, bomb, blockade, airlift, negotiate, and done" << endl;
	vector<string> advanceTerritories;
	cout << "[" << m_player->getPlayerName() << "] - Your order : ";
	string order;
	std::cin >> order;
	if (order == "done")
		done = true;
	else
	{
		Order* newOrder = nullptr;
		if (order == "deploy")
		{
			if (possibleReinforcement <= 0)
			{
				cout << "No more possible deployment" << endl;
			}
			else
			{
				cout << "List of Territories where it is possible to deploy: " << endl;
				for (int i = 0; i < this->toDefend().size(); i++)
				{
					if ((i % 5) == 0 && i != 0)
						cout << endl;
					cout << (i + 1) << ": " << this->toDefend()[i]->getNameTerritory() << " (" << this->toDefend()[i]->getNumberArmies() << ")";
					if (i != this->toDefend().size() - 1)
						cout << " | ";
				}
				while (possibleReinforcement > 0)
				{
					cout << "\n ID of Territory where to deploy: ";
					int id = 0;
					std::cin >> id;
					id = (id == 0) ? 0 : (id - 1);
					cout << "Number of Available Reinforcement units: " << possibleReinforcement << endl;
					cout << "Number of reinforcement: ";
					int reinforcement;
					std::cin >> reinforcement;
					reinforcement = abs(reinforcement);
					reinforcement = (reinforcement > possibleReinforcement) ? possibleReinforcement : reinforcement;
					possibleReinforcement = (possibleReinforcement - reinforcement);
					deploy* d = new deploy(m_player, this->toDefend()[id], reinforcement, m_player->getGameEngine());
					m_player->getPlayerOrdersList()->addOrder(d);
				}
			}
		}
		else if (order == "advance")
		{
			int choice = 0;
			int origin_id = 0;
			int destination_id = 0;
			int armies = 0;
			cout << "List of Owned Territories: " << endl;
			for (int i = 0; i < this->toDefend().size(); i++)
			{
				if ((i % 5) == 0 && i != 0)
					cout << endl;
				cout << (i + 1) << ": " << this->toDefend()[i]->getNameTerritory() << " (" << this->toDefend()[i]->getNumberArmies() << ")";
				if (i != this->toDefend().size() - 1)
					cout << " | ";
			}
			cout << "\nID of Territory from where to move the army : ";
			std::cin >> origin_id;
			origin_id = abs(origin_id);
			origin_id = (origin_id == 0) ? 0 : (origin_id - 1);
			if (std::find(advanceTerritories.begin(), advanceTerritories.end(), this->toDefend()[origin_id]->getNameTerritory()) != advanceTerritories.end())
				cout << "Advance order already issued from this Territory" << endl;
			else
			{
				while (choice < 1 || choice > 2)
				{
					cout << "\n1: Move Your Army | 2: Attack an Ennemy's Territory: ";
					std::cin >> choice;
				}
				vector<Territory*> territories;
				if (choice == 1)
				{
					cout << "List of Owned neighboring Territories: " << endl;
					territories = this->toDefend();
				}
				if (choice == 2)
				{
					cout << "List of Neighboring Territories to Attack: " << endl;
					territories = this->toAttack();
				}

				for (int i = 0; i < territories.size(); i++)
				{
					if ((i % 5) == 0 && i != 0)
						cout << endl;
					cout << (i + 1) << ": " << territories[i]->getNameTerritory() << " (" << territories[i]->getNumberArmies() << ")";
					if (i != this->toDefend().size() - 1)
						cout << " | ";
				}

				cout << "\nID of Territory into where move the army : ";
				std::cin >> destination_id;
				destination_id = abs(destination_id);
				destination_id = (destination_id == 0) ? 0 : (destination_id - 1);
				cout << "Destination's number of Armies: " << territories[destination_id]->getNumberArmies() << endl;
				cout << "\nNumber of Armies to available to use [0 - " << (this->toDefend()[origin_id]->getNumberArmies() - 2) << "]: ";
				std::cin >> armies;
				armies = abs(armies);
				armies = (armies > this->toDefend()[origin_id]->getNumberArmies()) ? this->toDefend()[origin_id]->getNumberArmies() : armies;
				newOrder = new advanceOrder(m_player, this->toDefend()[origin_id], territories[destination_id], territories[destination_id]->getOwner(), armies, m_player->getGameEngine());
				advanceTerritories.push_back(this->toDefend()[origin_id]->getNameTerritory());
			}
		}
		else if (order == "bomb")
		{
			int destination_id = 0, armies = 0;
			vector<Territory*> territoriesToAttack = this->toAttack();
			cout << "List of Possible Territories to Attack: " << endl;
			for (int i = 0; i < territoriesToAttack.size(); i++)
			{
				if ((i % 5) == 0 && i != 0)
					cout << endl;
				cout << (i + 1) << ": " << territoriesToAttack[i]->getNameTerritory() << " (" << territoriesToAttack[i]->getNumberArmies() << ")";
				if (i != this->toDefend().size() - 1)
					cout << " | ";
			}
			cout << "\nID of Territory to Bomb : ";
			std::cin >> destination_id;
			destination_id = abs(destination_id);
			destination_id = (destination_id == 0) ? 0 : (destination_id - 1);
			cout << "Current Destination's number of Armies: " << territoriesToAttack[destination_id]->getNumberArmies() << endl;
			newOrder = new bomb(m_player, territoriesToAttack[destination_id], m_player->getGameEngine()->deck, m_player->getGameEngine());
		}
		else if (order == "blockade")
		{
			int origin_id = 0;
			cout << "List of Owned Territories: " << endl;
			for (int i = 0; i < this->toDefend().size(); i++) 
			{
				if ((i % 5) == 0 && i != 0)
					cout << endl;
				cout << (i + 1) << ": " << this->toDefend()[i]->getNameTerritory() << " (" << this->toDefend()[i]->getNumberArmies() << ")";
				if (i != this->toDefend().size() - 1)
					cout << " | ";
			}
			cout << "\nID of Territory to blockade: ";
			std::cin >> origin_id;
			origin_id = abs(origin_id);
			origin_id = (origin_id == 0) ? 0 : (origin_id - 1);
			newOrder = new blockade(m_player, this->toDefend()[origin_id], m_player->getGameEngine()->deck, nullptr, m_player->getGameEngine());
		}
		else if (order == "airlift")
		{
			int origin_id = 0;
			int destination_id = 0;
			int armies = 0;
			cout << "List of Owned Territories: " << endl;
			for (int i = 0; i < this->toDefend().size(); i++)
			{
				if ((i % 5) == 0 && i != 0)
					cout << endl;
				cout << (i + 1) << ": " << this->toDefend()[i]->getNameTerritory() << " (" << this->toDefend()[i]->getNumberArmies() << ")";
				if (i != this->toDefend().size() - 1)
					cout << " | ";
			}
			cout << "\nID of Territory from where to move the army : ";
			std::cin >> origin_id;
			origin_id = abs(origin_id);
			origin_id = (origin_id == 0) ? 0 : (origin_id - 1);
			cout << "\nID of Territory into where to move the army : ";
			std::cin >> destination_id;
			destination_id = abs(destination_id);
			destination_id = (destination_id == 0) ? 0 : (destination_id - 1);
			cout << "Destination's number of Armies: " << this->toDefend()[destination_id]->getNumberArmies() << endl;
			cout << "\nNumber of Armies to use [0 - " << this->toDefend()[origin_id]->getNumberArmies() << "]: ";
			std::cin >> armies;
			armies = abs(armies);
			armies = (armies > this->toDefend()[origin_id]->getNumberArmies()) ? this->toDefend()[origin_id]->getNumberArmies() : armies;
			newOrder = new airlift(m_player, this->toDefend()[origin_id], this->toDefend()[destination_id], armies, m_player->getGameEngine()->deck, m_player->getGameEngine());
		}
		else if (order == "negotiate")
		{
			vector<Player*> players = m_player->getGameEngine()->players;
			cout << "list of players: " << endl;
			for (int i = 0; i < players.size(); i++)
			{
				if ((i % 5) == 0 && i != 0)
					cout << endl;
				cout << (i + 1) << ": " << players[i]->getPlayerName();
				if (i != this->toDefend().size() - 1)
					cout << " | ";
			}
			cout << "\nID of Player to negotiate with: ";
			int destination_id = 0;
			std::cin >> destination_id;
			destination_id = abs(destination_id);
			destination_id = (destination_id == 0) ? 0 : (destination_id - 1);
			newOrder = new negotiate(m_player, players[destination_id], m_player->getGameEngine()->deck, m_player->getGameEngine());
		}
		if (newOrder != nullptr)
			m_player->getPlayerOrdersList()->addOrder(newOrder);
	}
	cout << "\nOrders issued: " << endl;
	cout << *m_player->getPlayerOrdersList() << endl;
	return done;
}

// copied from player toAttack
std::vector<Territory*> HumanPlayerStrategy::toAttack()
{
	vector<Territory*> TerritoriesToAttack {};


	// Double for-loop that adds the attackable territory to the vector
	for (Territory* t : m_player->getPlayerTerritories()) 
	{
		for (Territory* a : t->getNeighbors()) {
			// Excluding owned territories
			if (t->getOwner() != a->getOwner()) {
				// Add territory to attack list
				if (std::find(TerritoriesToAttack.begin(), TerritoriesToAttack.end(), a) == TerritoriesToAttack.end())
					TerritoriesToAttack.push_back(a);
			}
		}

	}
	return TerritoriesToAttack;
}

std::vector<Territory*>& HumanPlayerStrategy::toDefend()
{
	return m_player->getPlayerTerritories();
}

//human player copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& h){
this->m_player = h.m_player;
}

//human player assignment operator
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& h){
	this->m_player= h.m_player;
	return *this;

}

//human player ostream operator 
ostream& operator<<(ostream &out, const HumanPlayerStrategy& a) {
	out << "Player name: " << a.m_player->getPlayerName() << " is Human" << endl;
	return out;
}

// Aggressive
bool AggressivePlayerStrategy::issueOrder()
{
	std::cout << "Agressive Player " + m_player->getPlayerName() + " issuing Order...\n";

	int numberStrongestTerritories = 1;

	// Divide the Reinforcement Pool based on the number of the desired strongest Territories - Default set to 1
	cout << "Player[" + this->m_player->getPlayerName() + "] Reinforcement " << this->m_player->getReinforcementPool() << endl;
	int reinforcement = this->m_player->getReinforcementPool() / numberStrongestTerritories;

	// The Strongest Owned Territory
	Territory* strongest = nullptr;

	//Helper flags
	bool _continue = false;
	bool allOwned = false;
	bool backup = false;

	// If this player still owns some Territories
	if (this->toDefend().size() > 0)
	{
		//Loop while decison is not made on which Territory to use
		while (!_continue)
		{
			// Check in Case the indexAttackingTerritory is bigger than the Territories owned
			if (this->indexAttackingTerritory >= this->toDefend().size())
			{
				cout << "Out of bounds!" << endl;
				this->indexAttackingTerritory = this->indexAttackingTerritory % this->toDefend().size();
			}
			else
				//Assign the strongest of Owned Territories
				strongest = this->toDefend()[this->indexAttackingTerritory];
			//Safety Check
			if (strongest != nullptr)
			{
				//Strongest Territory has Neighbors and not all neighbors are owned by the current player
				if (strongest->getNeighbors().size() > 0 && !allOwned)
				{
					//Loop through the Neighbors' of the strongest Territory
					for (Territory* territoryToAttack : strongest->getNeighbors())
					{
						// If the Territory is not owned by the current Player
						if (territoryToAttack->getOwner()->getPlayerName() != strongest->getOwner()->getPlayerName())
						{
							//Check if the found Territory's army is not 100 times stronger than the strongest owned Territory
							if (territoryToAttack->getNumberArmies() > (strongest->getNumberArmies() - 2) * 100)
							{
								//If it is, then Check if the current Player owns 90% of the Territories
								//If yes, then switch to Advancing into owned Territories until the strongest Territory has enough Armies to attack
								if (this->m_player->getNumTerritories() >= 0.90 * this->m_player->getGameEngine()->getMap()->getSizeofMap())
								{
									_continue = true;
									allOwned = false;
									backup = true;
									break;
								}
								//If the current Player does not own 90% of the Territories then go find the next strongest Territory
								else
								{
									_continue = false;
									allOwned = true;
									break;
								}

							}
							//Use this Territory as the Strongest
							else
							{
								_continue = true;
								allOwned = false;
								break;
							}
						}
						// Neighbor is also Owned by the current Player
						else
							allOwned = true;
					}
				}
				// Either the current Territory has no neighbors or all the neighbors are owned by the current player
				else
				{
					//Pick the next Strongest Territory
					this->indexAttackingTerritory = (this->indexAttackingTerritory + 1) % this->toDefend().size();
					allOwned = false;
				}
			}
			//Safe guard if the Territory is a nullptr, if it is go to the next one
			else
			{
				this->indexAttackingTerritory = (this->indexAttackingTerritory + 1) % this->toDefend().size();
				allOwned = false;
			}
		}
		//Deploy all Available Reinforcement into the strongest Territory
		this->m_player->getPlayerOrdersList()->addOrder(new deploy(this->m_player, strongest, reinforcement, this->m_player->getGameEngine()));
		//Helper flag
		bool attacked = false;
		allOwned = false;

		//Switches to backup mode, deploys Units from neighboring Territories to the strongest Territory
		if (backup)
		{
			//Loop through the strongest Territory's neighbors
			for (Territory* t : strongest->getNeighbors())
			{
				//Issue an AdvanceOrder if the Territory is owned by the current Player
				if (t->getOwner()->getPlayerName() == strongest->getOwner()->getPlayerName())
				{
					this->m_player->getPlayerOrdersList()->addOrder(new advanceOrder(this->m_player, t, strongest, this->m_player, (t->getNumberArmies() - 2), this->m_player->getGameEngine()));
				}
			}
		}
		//Atack Mode
		else
		{
			//Loop Until a decision is made regarding which Territory to attack
			while (!attacked)
			{
				//Loop through the neighboring Territories of the strongest Territory, if a territory is not owned by the current player, attack it!
				for (Territory* territoryToAttack : strongest->getNeighbors())
				{
					// If the neighboring Territory is owned by a different player, attack it!
					if (territoryToAttack->getOwner()->getPlayerName() != strongest->getOwner()->getPlayerName())
					{
						this->m_player->getPlayerOrdersList()->addOrder(new advanceOrder(this->m_player, strongest, territoryToAttack, territoryToAttack->getOwner(), (strongest->getNumberArmies() - 2), this->m_player->getGameEngine()));
						attacked = true;
						break;
					}
				}
			}
		}

		// Check if 
		for (Card* meCard : this->m_player->getPlayerHand()->getCards())
		{
			//If they have a Bomb card, use it
			if (meCard->getType() == "bomb")
			{
				this->m_player->getPlayerOrdersList()->addOrder(new bomb(this->m_player, this->m_player->toAttack()[0], this->m_player->getGameEngine()->getDeck(), this->m_player->getGameEngine()));
			}
		}
	}
	return true;
}

//Returns All possible Territories that can be attacked
std::vector<Territory*> AggressivePlayerStrategy::toAttack()
{
	vector<Territory*> TerritoiesToAttack;

	// Double for-loop that adds the attackable territory to the vector
	for (Territory* t : this->m_player->getPlayerTerritories()) {
		for (Territory* a : t->getNeighbors()) {
			// Excluding owned territories
			if (t->getOwner() != a->getOwner()) {
				// Add territory to attack list if it is empty
				if (TerritoiesToAttack.size() == 0)
					TerritoiesToAttack.push_back(a);
				else
					//Add territory if it does not exist already in the list
					if (std::find(TerritoiesToAttack.begin(), TerritoiesToAttack.end(), a) == TerritoiesToAttack.end())
						TerritoiesToAttack.push_back(a);
			}
		}

	}
	return TerritoiesToAttack;
}

//Loop Through the possible Territories that can be attacked
//Check if a neighbor of one of these territories is owned by the current player
//If so, return a reference to the owned Territory
Territory* AggressivePlayerStrategy::nextToAttack()
{
	Territory* _nextToAttack = nullptr;
	vector<Territory*> territoriesToAttack = this->toAttack();
	for (Territory* t : territoriesToAttack)
	{
		for (Territory* neighbor : t->getNeighbors())
		{
			if (neighbor->getOwner()->getPlayerName() == this->m_player->getPlayerName())
			{
				_nextToAttack = neighbor;
				return _nextToAttack;
			}
		}
	}
	return _nextToAttack;
}

//Sorts the Owned Territories by the number of Armies and returns the list
std::vector<Territory*>& AggressivePlayerStrategy::toDefend()
{

	std::sort(this->m_player->getPlayerTerritories().begin(), this->m_player->getPlayerTerritories().end(),
		[&](Territory* A, Territory* B)
		{
			return A->getNumberArmies() < B->getNumberArmies();
		});
		return this->m_player->getPlayerTerritories();
}

//aggressive player copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& h){
this->m_player = h.m_player;
}

//aggressive player assignment operator
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& h){
	this->m_player= h.m_player;
	return *this;

}

//aggressive player ostream operator 
ostream& operator<<(ostream &out, const AggressivePlayerStrategy& a) {
	out << "Player name: " << a.m_player->getPlayerName() << " is Aggressive" << endl;
	return out;
}

/*

*/
//Benevolent
bool BenevolentPlayerStrategy::issueOrder()
{
	GameEngine* game = m_player->getGameEngine();
	Hand* hand = m_player->getPlayerHand();
	Deck* deck = game->getDeck();
	OrdersList* orders = m_player->getPlayerOrdersList();

		// Introduction message for each player
	cout << "\nIssuing orders for player " << m_player->getPlayerName() << ":" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	cout << "#--- Deploying Phase ---#" << endl;

	// List of territories to defend
	if (this->toDefend().size() > 0)
	{
		cout << "\nTerritories to defend: (Index : Name)" << endl;
		for (auto it : toDefend()) {
			cout << it->getID() << " : " + it->getNameTerritory() << " , Armies: " << it->getNumberArmies() << endl;
		}
		cout << endl;
		int numberOfTerritoriestoDefend = 1;
		int reinforcement = m_player->getReinforcementPool() / numberOfTerritoriestoDefend;
		// Deploy all the reinforcement pool to its weakest country
		for (int i = 0; i < numberOfTerritoriestoDefend; i++)
		{
			cout << "Player " << m_player->getPlayerName() << "'s number of armies left in the reinforcement pool: " << m_player->getReinforcementPool() << endl << endl;
			cout << "Player " << m_player->getPlayerName() << " has chosen territory " << m_player->toDefend().at(0)->getNameTerritory() << " to defend with " << m_player->getReinforcementPool() << " armies." << endl;
			m_player->getPlayerOrdersList()->addOrder(new deploy(m_player, m_player->toDefend().at(0), reinforcement, game));
		}
		cout << "\n#--- Deploying Phase OVER ---#" << endl;
		cout << "/*-------------------------------------------------------------------*/" << endl;

		// Now issuing advance orders
		cout << "\n#--- Advancing Phase ---#" << endl;

		cout << "\nThe Benevolent Player has no advances to make." << endl;

		cout << "\n#--- Advancing Phase OVER ---#" << endl;
		cout << "/*-------------------------------------------------------------------*/" << endl;

		// All advance orders have been issued at this point!

		//Clearing the cannotAttack vector for Negotiate order
		m_player->cannotAttack.clear();

		// Now playing a card, Player plays one card per turn
		cout << "\n#--- Card Playing Phase ---#" << endl << endl;

		// The benevolent player cannot use the bomb card
		if (hand->getSize() > 0)
		{
			int handSize = m_player->getPlayerHand()->getSize();
			Card* currentCard = nullptr;
			for (int i = 0; i < handSize; ++i)
			{
				Card* currentCard = m_player->getPlayerHand()->getCard(i);
				string cardName = currentCard->getType();
				// Cases for each type of card that could be played

				if (cardName == "blockade") {
					cout << "Blockade card selected:" << endl;
					Territory* target = toDefend().at(0);
					//currentCard->play(m_player->getPlayerHand(), deck, m_player);
					this->m_player->getPlayerOrdersList()->addOrder(new blockade(this->m_player, target, deck, game->getNeutralPlayer(), game));
					cout << "Blockade order will be issued on !" << target->getNameTerritory() << endl;
					break;
				}
				else if (cardName == "reinforcement") {
					cout << "Reinforcement card selected: " << endl;
					/*currentCard->play(m_player->getPlayerHand(), deck, m_player);*/
					cout << "5 Units added to the pool of [" + this->m_player->getPlayerName() + "]" << endl;
					this->m_player->add2ReinforecemntPool(5);
					break;
				}
				else if (cardName == "airlift") {
					if (toDefend().size() > 1) {
						cout << "Airlift card selected:" << endl;
						Territory* ownT = toDefend().at(1);
						Territory* otherOwnT = toDefend().at(0);
						//currentCard->play(m_player->getPlayerHand(), deck, m_player);
						//airlift::airlift(Player* player, Territory* source, Territory* target, const int numberOfArmies, Deck* deck, GameEngine* game)
						this->m_player->getPlayerOrdersList()->addOrder(new airlift(this->m_player, toDefend()[1], toDefend()[0], (toDefend()[1]->getNumberArmies() - 2), deck, game));
						cout << "Airlift order will be issued!";
						break;
					}
				}
				else if (cardName == "diplomacy")
				{
					Player* otherP;
					if (game->players.at(0) == m_player)
					{
						otherP = game->players.at(1);
					}
					else
					{
						otherP = game->players.at(0);
					}
					cout << "Diplomacy card selected. " << endl;
					cout << "Diplomacy order will be issued!" << endl;
					//currentCard->play(m_player->getPlayerHand(), deck, m_player);
					//negotiate::negotiate(Player* player, Player* target, Deck* deck, GameEngine* game)
					this->m_player->getPlayerOrdersList()->addOrder(new negotiate(this->m_player, otherP, deck, game));

				}

				// If the player has cards that cannot be played
				if (i == handSize - 1) {
					cout << "Player " << m_player->getPlayerName() << " has no cards in their hand they should play, skipping the card playing phase!" << endl;
				}
			}
		}

		// If the player has no cards whatsoever to play
		else {
			cout << "Player " << m_player->getPlayerName() << " has no cards in their hand, skipping the card playing phase!" << endl;
		}

		cout << "\n#--- Card Playing Phase OVER ---#" << endl;
		cout << "/*-------------------------------------------------------------------*/" << endl;
	}
	else
	{
	cout << "No more Owned Territories" << endl;
	}
	
	return true;
}

// does not attack, returns empty vector
std::vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
	std::vector<Territory*> empty{};
	return empty;
}

// returns the weakest country
std::vector<Territory*>& BenevolentPlayerStrategy::toDefend()
{
	std::sort(this->m_player->getPlayerTerritories().begin(), this->m_player->getPlayerTerritories().end(),
		[&](Territory* A, Territory* B)
		{
			return A->getNumberArmies() > B->getNumberArmies();
		});
	return this->m_player->getPlayerTerritories();
}

//benevolent player copy constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& h){
this->m_player = h.m_player;
}

//benevolent player assignment operator
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& h){
	this->m_player= h.m_player;
	return *this;

}

//benevolent player ostream operator 
ostream& operator<<(ostream &out, const BenevolentPlayerStrategy& a) {
	out << "Player name: " << a.m_player->getPlayerName() << " is Benevolent" << endl;
	return out;
}

//Neutral
//does not issues orders
bool NeutralPlayerStrategy::issueOrder()
{
	std::cout << "Neutral Player " + m_player->getPlayerName() + " issuing Order...\n";
	std::cout << "Neutral Player does not issue Orders. \n";

	if (m_player->getHasBeenAttacked())
	{
		std::cout << "Neutral player " << m_player->getPlayerName() << " has been attacked, turning aggressive\n";
		m_player->setStrategy(new AggressivePlayerStrategy(m_player));
		delete this;
	}
	return true;
}

// returns empty
std::vector<Territory*> NeutralPlayerStrategy::toAttack()
{
	std::vector<Territory*> empty {};
	return empty;
}

// returns empty
std::vector<Territory*>& NeutralPlayerStrategy::toDefend()
{
	std::vector<Territory*> empty{};
	return empty;
}

//Neutral player copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& h){
this->m_player = h.m_player;
}

//neutral player assignment operator
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& h){
	this->m_player= h.m_player;
	return *this;

}

//neutral player ostream operator 
ostream& operator<<(ostream &out, const NeutralPlayerStrategy& a) {
	out << "Player name: " << a.m_player->getPlayerName() <<" is Neutral" << endl;
	return out;
}

// Cheater
bool CheaterPlayerStrategy::issueOrder()
{
	std::cout << "Cheater Player " + m_player->getPlayerName() + " issuing Order...\n";
	//List of the Territories to be added
	vector<Territory*> newOwnedTerritories;

	//Loop through all the Owned territories
	for (Territory* t : this->toDefend())
	{
		std::vector<Territory*>::iterator it = std::find(newOwnedTerritories.begin(), newOwnedTerritories.end(), t);
		if (it == newOwnedTerritories.end())
		{
			for (Territory* neighbor : t->getNeighbors())
			{
					if (neighbor->getOwner()->getPlayerName() != this->m_player->getPlayerName())
					{
						newOwnedTerritories.push_back(neighbor);
					}
			}
		}
	}

	//Loop through the new Territories and added to the Owned List
	for (Territory* t : newOwnedTerritories)
	{
		if (t != nullptr)
		{
			t->getOwner()->removeOwnedTerritory(t);
			m_player->addOwnedTerritory(t);
		}
			
	}


	return true;
}

std::vector<Territory*> CheaterPlayerStrategy::toAttack()
{
	vector<Territory*> TerritoiesToAttack;

	// Double for-loop that adds the attackable territory to the vector
	for (Territory* t : this->m_player->getPlayerTerritories()) {
		for (Territory* a : t->getNeighbors()) {
			// Excluding owned territories
			if (t->getOwner() != a->getOwner()) {
				// Add territory to attack list
				if (TerritoiesToAttack.size() == 0)
					TerritoiesToAttack.push_back(a);
				else
					if (std::find(TerritoiesToAttack.begin(), TerritoiesToAttack.end(), a) == TerritoiesToAttack.end())
						TerritoiesToAttack.push_back(a);
			}
		}

	}
	return TerritoiesToAttack;
}

std::vector<Territory*>& CheaterPlayerStrategy::toDefend()
{
	return this->m_player->getPlayerTerritories();
}

//Cheater player copy constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& h){
this->m_player = h.m_player;
}

//Cheater player assignment operator
CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& h){
	this->m_player= h.m_player;
	return *this;

}

//Cheater player ostream operator 
ostream& operator<<(ostream &out, const CheaterPlayerStrategy& a) {
	out << "Player name: " << a.m_player->getPlayerName() <<" is Cheater" << endl;
	return out;
}


int random(int min, int max)
{
	return min + (rand() % (max - min + 1));
}