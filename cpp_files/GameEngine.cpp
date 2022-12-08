#include "../header_files/GameEngine.h"
#include "../header_files/CommandProcessing.h"
#include "../header_files/Player.h"
#include <random>
#include <math.h>
#include <regex>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

// Members of State Class
State::State() : stateName("none") {}
State::State(string name) : stateName(name) {}
State::State(const State& state) : stateName(state.stateName) {}

State& State::operator=(const State& state)
{
	this->stateName = state.stateName;
	return *this;
}

ostream& operator<<(ostream& out, const State& state)
{
	out << "Current State: " << state.stateName << endl;
	return out;
}

// Members of Transition Class

Transition::Transition() : current(nullptr), next(nullptr), command("none") {}
Transition::Transition(State* current, State* next, string command) : current(current), next(next), command(command) {}
Transition::Transition(const Transition& transition) : current(transition.current), next(transition.next), command(transition.command) {}

Transition& Transition::operator=(const Transition& transition)
{
	// Intentionally making shallow copies to refer to the same states
	this->current = transition.current;
	this->next = transition.next;
	this->command = transition.command;
	return *this;
}

ostream& operator<<(ostream& out, const Transition& transition)
{
	out << "(From: " << transition.current->stateName << ", To: " << transition.next->stateName << ")" << endl;
	return out;
}

// Members of GameEngine Class


GameEngine::GameEngine()
{
	initializeTransitions();
	/*m_currentState = 0;
	m_currentStatePtr = &m_currentState;*/
	this->neutral = new Player("Neutral", new Hand());
	this->deck = new Deck();
}

GameEngine::GameEngine(Observer* _obs) : currentState(nullptr), deck(new Deck()), _observer(_obs), cmd_currentState(nullptr), map(nullptr) {
	//initializeTransitions();
	this->Attach(_obs);
	players.push_back(new Player("NEUTRAL", new Hand()));
}

//copy constructor
GameEngine::GameEngine(const GameEngine& old_obj) {
	m_currentState = old_obj.m_currentState;
	m_currentStatePtr = &m_currentState;
}

//operator
GameEngine& GameEngine::operator =(const GameEngine& GameEngine) {
	m_currentState = GameEngine.m_currentState;
	return *this;

}

void GameEngine::setMap(Map* newMap)
{
	map = newMap;
}

void GameEngine::addPlayer(Player* player)
{
	players.push_back(player);
}

void GameEngine::removePlayer(Player* player)
{
	players.erase(remove(players.begin(), players.end(), player), players.end());
}

// Acessor methods


Deck* GameEngine::getDeck() { return deck; }

Map* GameEngine::getMap() { return map; }

Player* GameEngine::getNeutralPlayer() { return this->neutral; }


void GameEngine::run()
{

	std::string cmd = "";
	std::string* cmdptr = &cmd;
	bool end = false;
	bool* endptr = &end;

	std::cout << "Started! enter \"loadmap\" to continue\n";

	while (!end)
	{

		switch (m_currentState)
		{
		case start_game:
			if (cmd != "loadmap" && cmd != "")
				std::cout << "ERROR: invalid input enter \"loadmap\" for next state" << std::endl;
			else if (cmd == "loadmap")
			{
				*m_currentStatePtr = map_loaded;
				std::cout << "Map Loaded enter \"loadmap\" or \"validatemap\" for next state\n";
			}
			break;

		case map_loaded:
			if (cmd != "loadmap" && cmd != "validatemap")
				std::cout << "ERROR: invalid input enter \"loadmap\" to load another map or \"validatemap\" for next state" << std::endl;
			else if (cmd == "loadmap")
				std::cout << "Map Loaded enter \"loadmap\" or \"validatemap\" for next state\n";
			else if (cmd == "validatemap")
			{
				*m_currentStatePtr = map_validated;
				std::cout << "Map Validated enter \"addplayer\" for next state \n";
			}

			break;

		case map_validated:
			if (cmd != "addplayer")
				std::cout << "ERROR: invalid input enter \"addplayer\" to begin adding players" << std::endl;

			else
			{
				std::cout << "Player Added, enter \"addplayer\" to add new player or \"assigncountries\" for next state\n";
				*m_currentStatePtr = players_added;
			}
			break;

		case players_added:
			if (cmd != "addplayer" && cmd != "assigncountries")
				std::cout << "ERROR: invalid input enter \"addplayer\" to add a new player or \"assigncountires\" for next state" << std::endl;
			else if (cmd == "addplayer")
				std::cout << "Player Added enter \"addplayer\" to add a new player or \"assigncountires\" for next state\n";
			else if (cmd == "assigncountries")
			{
				*m_currentStatePtr = assign_reinforcements;
				std::cout << "Assign Reinforcements, enter \"issueorder\" for next state\n";
			}

			break;


		case assign_reinforcements:
			if (cmd != "issueorder")
				std::cout << "ERROR: Invalid input, enter  \"issueorder\" for next state" << std::endl;

			else
			{
				std::cout << "issue orders: enter \"issueorder\" to issue another order or \"endissueorders\" for next state\n";
				*m_currentStatePtr = issue_orders;
			}
			break;

		case issue_orders:
			if (cmd != "issueorder" && cmd != "endissueorders")
				std::cout << "ERROR: Invalid input: enter \"issueorder\" to execute another order or \"endissueorders\" for next state" << std::endl;
			else if (cmd == "issueorder")
				std::cout << "Issue orders: enter \"issueorder\" to execute another order or \"endissueorders\" for next state\n";
			else if (cmd == "endissueorders")
			{
				*m_currentStatePtr = execute_orders;
				std::cout << "execute orders: enter \"execorder\" to execute another order or \"endexecorders\" to return to assign reinforcement or \"win\" to enter win state\n";
			}

			break;

		case execute_orders:
			if (cmd != "execorder" && cmd != "endexecorders" && cmd != "win")
				std::cout << "ERROR: Invalid input enter \"execorder\" to execute another order or \"endexecorders\" to return to assign reinforcement or \"win\" to enter win state " << std::endl;
			else if (cmd == "execorder")
				std::cout << "execute orders: enter \"execorder\" to execute another order or \"endexecorders\" to return to assign reinforcement or \"win\" to enter win state\n";
			else if (cmd == "endexecorders")
			{
				*m_currentStatePtr = assign_reinforcements;
				std::cout << "assign reinforcements: enter \"issueorder\" for next state \n";
			}
			else if (cmd == "win")
			{
				*m_currentStatePtr = win_game;
				std::cout << "win!!! enter \"play\" to play again or \"end\" to end\n";
			}
			break;
		case win_game:
			if (cmd != "play" && cmd != "end")
				std::cout << "ERROR: Invalid input, enter \"play\" to play again or \"end\" to end" << std::endl;

			else if (cmd == "play")
			{
				*m_currentStatePtr = start_game;
				std::cout << "Started! enter \"loadmap\" to continue\n";
			}

			else if (cmd == "end")
			{
				*endptr = !end;
				std::cout << "ending game. Thanks for playing!\n";
			}
			break;

		}


		if (!end)
			std::cin >> *cmdptr;
	}

}

/*
Shuffle the order of the players
*/
void GameEngine::shuffleOrder()
{
	int counter = this->players.size();
	int i = 0, j = 0;
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(0, (this->players.size() - 1));
	if (counter > 0)
	{
		while (counter >= 0)
		{
			i = distribution(rd);
			j = distribution(rd);
			std::swap(this->players[i], this->players[j]);
			counter--;
		}
	}
}
/*
Reverses the order of the players to make it as fair as possible
*/
void GameEngine::reverseorder()
{
	std::reverse(this->players.begin(), this->players.end());
}
/*
Check the current state of the GameEngine if it accepts the command
*/
bool GameEngine::checkState(string command)
{
	for (int i = 0; i < transitions.size(); i++)
	{
		if (currentState->stateName == transitions[i]->current->stateName && command == transitions[i]->command)
		{
			//currentState = transitions[i]->next;
			return true;
		}
		else if (currentState->stateName == "win" && command == "end") return true;
	}
	return false;
}
/*
After checking if the GameEngine is in a state that will accept the input command, it will change its state to the next state based on the command
*/
bool GameEngine::changeState(string command)
{
	for (int i = 0; i < transitions.size(); i++)
	{
		if (currentState->stateName == transitions[i]->current->stateName && command == transitions[i]->command)
		{
			if (transitions[i]->current->stateName == transitions[i]->next->stateName)
				currentState = transitions[i]->current;
			else
				currentState = transitions[i]->next;
			cout << *currentState;
			Notify(this);
			return true;
		}
		else if (currentState->stateName == "win" && command == "end") return true;
	}
	Notify(this);
	return false;
}
/*
Add a new state and add it to the collection of the GameEngine
*/
State* GameEngine::newState(string stateName)
{
	State* state = new State(stateName);
	states.push_back(state);
	return state;
}
/*
Creating a new transition based on two states and a command to link the two states
*/
void GameEngine::newTransition(State* current, State* next, string command)
{
	transitions.push_back(new Transition(current, next, command));
}

// Used when the player enters 'quit'
void GameEngine::end()
{
	delete this;
	cout << "Thank you for playing!" << endl;
}

/*
StatupPhase method that ensures that the commands are valid and correct for the current state of the GameEngine
*/
void GameEngine::startupPhase(CommandProcessor* cp)
{
	this->cp = cp;
	bool inStartup = true;
	//Message to show the available maps
	cout << "Available maps: Pangaea, USA, 001_I72_Ghtroc 720, World 2007, Eurasia - WWII 1939" << endl;

	//Loop as long as the GameEngine is still in startup phase
	while (inStartup)
	{
		cout << "\nAvailable Commands in Starting Phase: loadmap, validatemap, addplayer, gamestart, replay, quit" << endl;
		cout << "Awaiting a command: ";
		//get Command from the CommandProcessor
		bool valid = false;//cp->getCommand(this, cp); commenting this to compile and test fix this
		//If the command is valid, execute it
		if (valid)
		{
			Command* command = cp->getValidCommandList().back();
			//Load the map
			if (command->getCommandStr() == "loadmap")
			{
				string MAP = command->getToAdd();
				if (command->getToAdd().find(".map") == std::string::npos)
					MAP += ".map";
				ifstream mapFile(MAP);
				if (mapFile.is_open())
				{
					string line;
					int territoryCounter = 0;
					bool territofyflag = false;
					bool continentflag = false;
					vector<Territory*> territories;
					vector<Continent*> continents;
					vector<string> continentstmps;
					continentstmps.reserve(10);
					std::vector<string> tmps;
					tmps.reserve(1000);
					string temp;
					territories.reserve(100);
					while (getline(mapFile, temp)) {
						if (continentflag)
						{
							if (temp != "" && !(temp.find("[Territories]") != string::npos))
							{
								stringstream ss(temp);
								while (getline(ss, temp, '='))
								{
									continentstmps.push_back(temp);
								}
								continentstmps.push_back("|");
							}
						}
						if (territofyflag)
						{
							if (temp != "")
							{
								stringstream ss(temp);
								while (getline(ss, temp, ','))
								{
									tmps.push_back(temp);
								}
								tmps.push_back("|");
								territoryCounter++;
							}
						}
						if (temp.find("[Continents]") != string::npos)
							continentflag = true;
						if (temp.find("[Territories]") != string::npos)
						{
							territofyflag = true;
							continentflag = false;
						}
					}
					std::vector<string> neighbors;
					neighbors.reserve(100);
					int j = 0;
					string name, continent;
					int index = 0;
					for (int i = 0; i < tmps.size(); i++)
					{
						if (j == 0)
						{
							name = tmps[i];
							neighbors.push_back(tmps[i]);
						}
						if (j == 3)
							continent = tmps[i];
						if (j > 3 && !(tmps[i].find("|") != string::npos))
							neighbors.push_back(tmps[i]);
						j++;
						if (tmps[i].find("|") != string::npos)
						{
							j = 0;
							Player* p = new Player();
							Territory* t = new Territory(name, continent, p, 5, index);
							t->next = nullptr;
							territories.push_back(t);
							neighbors.push_back(tmps[i]);
							index++;
						}
					}
					int z = 0;
					string continentName;
					int powerup = 0;
					for (int i = 0; i < continentstmps.size(); i++)
					{
						if (z == 0 && !(continentstmps[i].find("|") != string::npos))
						{
							continentName = continentstmps[i];
						}
						if (z == 1 && !(continentstmps[i].find("|") != string::npos))
						{
							powerup = stoi(continentstmps[i]);
						}
						z++;
						if (z > 1 && continentstmps[i] == "|")
						{
							z = 0;
							Continent* continent = new Continent(powerup, continentName);
							continents.push_back(continent);
						}
					}
					if (this->map != nullptr)
						delete this->map;
					this->map = nullptr;
					this->map = new Map(territories, continents, neighbors);
					mapFile.close();
					cout << "Map Loaded" << endl;
					changeState(command->getCommandStr());
				}
				else {
					std::cout << "File not Found!" << endl;
				}
			}
			//Validate the map
			if (command->getCommandStr() == "validatemap")
			{
				if (this->map != nullptr)
				{
					if (this->map->validate())
					{
						changeState(command->getCommandStr());
						cout << "There are: " << this->map->getTerritories().size() << " Territories." << endl;
					}
					else
						cout << "Map is not valid" << endl;
				}
				else
					cout << "Please load a map first" << endl;

			}
			//Addplayers
			if (command->getCommandStr() == "addplayer")
			{
			// Add player (This part should loop so as to ensure that we have 2-6 players in the game.)
			string effect = command->getEffect();

			std::regex extractionPattern("Player (.*) has");
			std::smatch match;

			// Check to see if we have 2-6 players in the game
			if (players.size() < 6) {
				if (std::regex_search(effect, match, extractionPattern)) {
					
					if (match[1] == "Aggressive" || match[1] == "aggressive" || match[1] == "AGGRESSIVE") {
						// Create and add aggressive player
						Player* p = nullptr;
						p = new Player("Aggressive", new Hand, this);
						p->setStrategy(new AggressivePlayerStrategy(NULL));
						addPlayer(p);
					}
					
					else if (match[1] == "Cheater" || match[1] == "cheater" || match[1] == "CHEATER") {
						// Create and add cheater player
						Player* p = nullptr;
						p = new Player("Aggressive", new Hand, this);
						p->setStrategy(new CheaterPlayerStrategy(NULL));
						addPlayer(p);
					}
					
					else if (match[1] == "Benevolent" || match[1] == "benevolent" || match[1] == "BENEVOLENT") {
						// Create and add benevolent player
						Player* p = nullptr;
						p = new Player("Aggressive", new Hand, this);
						p->setStrategy(new BenevolentPlayerStrategy(NULL));
						addPlayer(p);
					}

					else if (match[1] == "Neutral" || match[1] == "neutral" || match[1] == "NEUTRAL") {
						// Create and add neutral player
						Player* p = nullptr;
						p = new Player("Aggressive", new Hand, this);
						p->setStrategy(new NeutralPlayerStrategy(NULL));
						addPlayer(p);
					}
					
					else {
						// Create and add human player
						if (!tournamentMode) {
							addPlayer(new Player(match[1], new Hand, this));
						}

						else {
							cout << "Invalid player strategy passed to tournament commands: Human players cannot be added." << endl;
							exit(1);
						}
					}
				}
			}

			else {
				// Let the user know that they cannot add anymore players
				cout << "Limit of players in game has been reached, no new players may be added." << endl;
			}


			if (players.size() >= 2) {
				// Switch states

				// Check if state changed successfully, otherwise handle failure.
				if (!changeState("addplayer")) {
					cout << "ERROR: Could not transition to 'addplayer' from current state " << currentState->stateName << endl;
				}
			}

			else {
				// Let the user know that there needs to be more players for the game to start
				cout << "There must be at least 2 players before the game can start." << endl;
			}
		}
			//Start the game
			if (command->getCommandStr() == "gamestart")
			{
				//Check if there is enough players
				if (this->players.size() > 1)
				{
					distributeTerritories();
					//Change the state to assignreinforcement
					changeState(command->getCommandStr());
					mainGameLoop();
				}
				else
					cout << "Two or more players are needed before starting the game" << endl;
			}
			else if (command->getCommandStr() == "quit") {
				this->end();
			}
		}
		else
			cout << "Invalid Command or GameEngine is not in a state for the command:" << endl;
	}
}

/*
Distributing the Territories fairly amongst all the players
*/
void GameEngine::distributeTerritories()
{
	cout << "Let the fun begin" << endl;
	int _territoriesNumber = this->map->getSizeofMap() / this->players.size();
	int totalnumberTerritories = this->map->getSizeofMap();
	int numberDistributableTerritories = (_territoriesNumber * this->players.size());
	//Printing statistics regarding the Territories in the map
	cout << "Total number of Territories: " << totalnumberTerritories << endl;
	cout << "Number of Territories per Player: " << _territoriesNumber << endl;
	cout << "Number of Neutral Territories: " << (totalnumberTerritories - numberDistributableTerritories) << endl;
	int counter = 0;
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(0, (totalnumberTerritories - 1));
	vector<Territory*> territories = this->map->getTerritories();
	int p_index = 0;

	//shuffle the order of the players
	shuffleOrder();

	//Distribute the territories in a round-robin fashion
	//Repeat the process until all possible distributable territories have been ditributed fairly
	while (counter < numberDistributableTerritories)
	{
		//while There is still undistributed territories
		bool found = false;
		while (!found)
		{
			//Randomly get an index of a Territory
			int index = distribution(rd);
			//Making sure not to give a player more Territories than the rest of the players
			if (this->players[p_index]->getPlayerTerritories().size() < _territoriesNumber)
			{
				//Check that the selected Territory does not belong to anyone
				if (territories[index]->getOwner()->getPlayerName() != this->players[p_index]->getPlayerName() && territories[index]->getOwner()->getPlayerName() == "NoName")
				{
					this->players[p_index]->addTerritory(territories[index]);
					counter++;
					found = true;
				}
			}
			else
				found = true;
		}
		p_index = (p_index + 1) % this->players.size();
	}
	//Reverse the starting order to make it as fair as possible
	reverseorder();

	//Make the undistributed Territories neutral to make the game fair
	if ((totalnumberTerritories - numberDistributableTerritories) > 0)
		neutralTerritories();
	//Initialize the deck used for the game
	this->deck->init();
	counter = 0;
	//Show the Territories owned by the players
	for (Player* player : this->players) {
		cout << "Player: " << player->getPlayerName() << " has: " << player->getPlayerTerritories().size() << endl;
		counter = 0;
		for (int i = 0; i < this->map->getTerritories().size(); i++)
		{
			if (this->map->getTerritories()[i]->getOwner()->getPlayerName() == player->getPlayerName())
			{
				if ((counter % 5) == 0 && counter != 0)
					cout << endl;
				cout << this->map->getTerritories()[i]->getNameTerritory() << " (" << this->map->getTerritories()[i]->getNumberArmies() << ")";
				if (counter != this->map->getTerritories().size() - 1)
					cout << " | ";
				counter++;
			}
		}
		cout << endl;
		//Draw 2 cards for each player
		Hand* hand = new Hand();
		player->SetHand(hand);
		this->deck->draw(hand);
		this->deck->draw(hand);
		//Set the players' Reinforcement Pool to 50
		player->setReinforcementPool(50);
		//A message to indicate that a player has joined the game
		cout << "Player [" << player->getPlayerName() << "] joined \n" << endl;
	}
	//start the main Game Loop
	this->initial = true;
}

/*
Check for a winner by looping through the players list and checking how many territories they own. If a player has no Territory then they are removed from the game.
If there is one player left, and all the territories belong to them, then we found a winner.
*/
bool GameEngine::checkForWinner()
{
	bool winner = false;
	//Loop through the list of the players and check if a player has no territories, if it is the case then remove it from the list
	for (int i = 0; i < this->players.size(); i++)
	{
		if (this->players[i]->getPlayerTerritories().size() == 0)
		{
			cout << "Player [" << this->players[i]->getPlayerName() << "] has 0 Territories" << endl;
			cout << "Player [" << this->players[i]->getPlayerName() << "] is out of the game" << endl;
			this->players[i] = nullptr;
		}
	}
	//Remove the nullptrs from the list, i.e the players with no territories
	this->players.erase(remove(this->players.begin(), this->players.end(), nullptr), this->players.end());
	//Check if there is still one player left
	if (this->players.size() == 1)
	{
		winner = true;
		//Check if indeed all the territories are controlled by the final player
		for (Territory* t : this->map->getTerritories())
		{
			if (this->players[0]->getPlayerName() != t->getOwner()->getPlayerName())
				winner = false;
		}
	}
	this->winner = this->players[0];
	return winner;

}

/*
The main Game loop
*/
void GameEngine::mainGameLoop()
{
	//Repeat the Main Game loop as long as the GameEngine is in the assignreinforcement phase
	while (this->currentState->stateName == "assignreinforcement")
	{
		//Check for a winner
		if (checkForWinner())
		{
			//Change Current state to win
			changeState("win");
			//Ask user for input
			cout << "Game is finished! replay or quit?: ";
			string input;
			cin >> input;
			if (input == "replay")
				this->startupPhase(this->cp);
			else
				this->end();
		}
		else
		{
			//Reinforcement Phase
			reinforcementPhase();
			//Start counting the Reinforcement unit number
			this->initial = false;
			//Issueing Orders Phase
			issueOrdersPhase();
			//Executing Orders Phase
			executeOrdersPhase();
		}

	}
}

/*
The Method that initializes all the possible transitions of the gameEngine, and it sets its initial state to "start"
*/
void GameEngine::initializeTransitions()
{
	State* start = new State("start");
	State* maploaded = new State("maploaded");
	State* mapvalidated = new State("mapvalidated");
	State* playersadded = new State("playersadded");
	State* assignreinforcement = new State("assignreinforcement");
	State* win = new State("win");
	State* exit = new State("exit");

	Transition* loadmap = new Transition(start, maploaded, "loadmap");
	Transition* loadmap2 = new Transition(maploaded, maploaded, "loadmap");
	Transition* validatemap = new Transition(maploaded, mapvalidated, "validatemap");
	Transition* addplayer = new Transition(mapvalidated, playersadded, "addplayer");
	Transition* addplayer2 = new Transition(playersadded, playersadded, "addplayer");
	Transition* gamestart = new Transition(playersadded, assignreinforcement, "gamestart");
	Transition* replay = new Transition(win, start, "replay");
	Transition* quit = new Transition(win, exit, "quit");

	transitions.push_back(loadmap);
	transitions.push_back(loadmap2);
	transitions.push_back(validatemap);
	transitions.push_back(addplayer);
	transitions.push_back(addplayer2);
	transitions.push_back(gamestart);
	transitions.push_back(replay);
	transitions.push_back(quit);

	this->currentState = start;
}

string GameEngine::stringToLog()
{
	return "";
}

/*
Distributes reinforcement units based on the number of Territories owned by each player
*/
void GameEngine::reinforcementPhase()
{
	for (Player* player : this->players)
	{
		//Reinforcement units based on the number of Territories / 3; Minimum 3
		int numberofArmies = ((player->getPlayerTerritories().size() / 3) > 3) ? (player->getPlayerTerritories().size() / 3) : 3;
		//Check if the player owns an entire continent
		numberofArmies += this->map->calculateContinentBonus(player);
		//Check if it is the first time the reinforcement phase is executed
		if (!this->initial)
			player->add2ReinforecemntPool(numberofArmies);
		else
			player->setReinforcementPool(50);
		cout << player->getPlayerName() << ", Reinforcement Pool: " << player->getReinforcementPool() << endl;
	}
}

/*
Loop through all the Territories and check if no one owns a Territory then make assign it to the neutral player
*/
void GameEngine::neutralTerritories()
{
	for (Territory* t : this->map->getTerritories())
	{
		if (t->getOwner()->getPlayerName() == "NoName")
			this->neutral->addOwnedTerritory(t);
	}
}

/*
Issueing orders phase: nunmber of rounds is random each time. Each player issues one order per round.
*/
void GameEngine::issueOrdersPhase()
{
	vector<int> rounds;
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(1, 5);
	bool done = false;
	//Randomly asign a number of Rounds
	int numberOfRounds = distribution(rd);
	cout << "Randomly generated number of rounds: " << numberOfRounds << endl;
	for (int i = 0; i < this->players.size(); i++)
		rounds.push_back(numberOfRounds);
	int p_index = 0;
	//Loop as long as a player still can issue an order
	while (!done)
	{
		//Message to show how many rounds remain
		cout << "Number of rounds left for player [" << this->players[p_index]->getPlayerName() << "]: " << rounds[p_index] << endl;
		if (rounds[p_index] == 0)
			done = true;
		else {
			//Check if the player decided to end their turn prematurly
			if (this->players[p_index]->issueOrder())
			{
				rounds[p_index] = 0;
				done = true;
			}
			else
			{
				rounds[p_index]--;
				done = false;
			}
		}
		//next player
		p_index = (p_index + 1) % this->players.size();
		//Check if everyone ended their turn
		for (int i = 0; i < rounds.size(); i++)
		{
			if (rounds[i] != 0)
			{
				done = false;
				break;
			}
		}
	}
}

/*
Execution phase: Get the list of Orders from all the players. Loop through the orders and execute the deploy ones first.
*/
void GameEngine::executeOrdersPhase()
{
	vector< OrdersList*> listOfOrders;
	//Get the list of orders from all the players
	for (int i = 0; i < this->players.size(); i++)
	{
		listOfOrders.push_back(this->players[i]->getPlayerOrdersList());
	}
	int index = 0;
	//Executing the odeploy orders first
	cout << "Executing Deploy Orders first " << endl;
	for (OrdersList* list : listOfOrders)
	{
		index = 0;
		for (Order* order : list->getOrders())
		{
			//Using dynamic cast to check if the order is of type deploy
			if (dynamic_cast<deploy*>(order) != nullptr)
			{
				//execute the order
				order->execute();
				cout << order->getEffect() << endl;
				//remove the order from the list
				list->remove(order, index);
			}
			index++;
		}
	}
	//Check if there still other types of orders. If yes, execute them
	for (OrdersList* list : listOfOrders)
	{
		//Updates the list to remove the executed orders
		list->update();
		index = 0;
		for (Order* order : list->getOrders())
		{
			order->execute();
			cout << order->getEffect() << endl;
			list->remove(order, index);
			index++;
		}
		list->update();
	}
}