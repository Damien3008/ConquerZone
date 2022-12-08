#include "../header_files/GameEngineDriver.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Map* getMap(string _mapName);

Map* getMap()
{
	return getMap("USA.map");
	/*Map* map;
	ifstream mapFile("USA.map");
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
		map = nullptr;
		map = new Map(territories, continents, neighbors);
		mapFile.close();
		return map;
	}*/
}

Map* getMap(string _mapName)
{
	Map* map = nullptr;
	if (_mapName.find(".map") == std::string::npos)
		_mapName += ".map";
	ifstream mapFile(_mapName);
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
		map = nullptr;
		map = new Map(territories, continents, neighbors);
		mapFile.close();
		
	}
	return map;
}



void testgamestate() {
	/*GameEngine ge;
	ge.run();*/
}

void testStartupPhase()
{
	GameEngine ge;
	Subject* s = new Subject();
	LogObserver* lg = new LogObserver();
	s->Attach(lg);
	CommandProcessor* cp = new CommandProcessor(lg);
	ge.startupPhase(cp);
}

/*void testMainGameLoop()
{
	GameEngine* ge = new GameEngine();
	Subject* s = new Subject();
	LogObserver* lg = new LogObserver();
	s->Attach(lg);
	CommandProcessor* cp = new CommandProcessor(lg);
	cout << "---\t\t\tLoading Map\t\t\t---" << endl;
	ge->map = getMap();
	cout << "---\t\t\tValidating Map\t\t\t---" << endl;
	ge->map->validate();

	for (int i = 0; i < ge->map->getTerritories().size(); i++)
	{
		if ((i % 5) == 0 && i != 0)
			cout << endl;
		cout << ge->map->getTerritories()[i]->getNameTerritory() << " (" << ge->map->getTerritories()[i]->getNumberArmies() << ")";
		if (i != ge->map->getTerritories().size() - 1)
			cout << " | ";
	}

	//new Player(command->getToAdd(), new Hand, this)

	cout << "\n\n---\t\t\tAdding Two Players\t\t\t---" << endl;

	Player* player1 = new Player("A", new Hand(), ge);
	Player* player2 = new Player("B", new Hand(), ge);
	ge->players.push_back(player1);
	ge->players.push_back(player2);

	for (Player* player : ge->players)
		cout << player->getPlayerName() << endl;

	// Creating the states for the game engine
	State* start = ge->newState("start");
	State* map_loaded = ge->newState("map_loaded");
	State* map_validated = ge->newState("map_validated");
	State* players_added = ge->newState("players_added");
	State* assign_reinforcement = ge->newState("assign_reinforcement");
	State* win = ge->newState("win");
	State* end_game = ge->newState("end_game");

	// Creating the transitions for the game engine
	ge->newTransition(start, map_loaded, "loadmap");
	ge->newTransition(map_loaded, map_loaded, "loadmap");
	ge->newTransition(map_loaded, map_validated, "validatemap");
	ge->newTransition(map_validated, players_added, "addplayer");
	ge->newTransition(players_added, players_added, "addplayer");
	ge->newTransition(players_added, assign_reinforcement, "gamestart");
	ge->newTransition(assign_reinforcement, win, "gameend");	//For testing purposes
	ge->newTransition(win, start, "replay");
	ge->newTransition(win, end_game, "quit");

	// The game's pointer is set to start
	ge->currentState = start;

	cout << "\n\n---\t\t\tDistributing Territories\t\t\t---" << endl;

	ge->distributeTerritories();

	ge->changeState("gamestart");
	ge->reinforcementPhase();
	ge->initial = false;
	ge->issueOrdersPhase();
	ge->executeOrdersPhase();

	cout << "\n\n---\t\t\tGiving a Player[" << ge->players[0]->getPlayerName() << "] Control over an entire continent\t\t\t-- - " << endl;
	cout << "Continent in question: " << ge->map->getContinents()[0]->getName() << " bonus: " << ge->map->getContinents()[0]->getPowerUP() << endl;
	for (Territory* t : ge->map->getContinents()[0]->getTerritories())
	{
		ge->players[0]->addTerritory(t);
	}

	cout << "Number of Territories for Player [" << ge->players[0]->getPlayerName() << "] is : " << ge->players[0]->getPlayerTerritories().size() << endl;
	cout << "Number of Territories for Player [" << ge->players[1]->getPlayerName() << "] is : " << ge->players[1]->getPlayerTerritories().size() << endl;

	ge->reinforcementPhase();
	ge->issueOrdersPhase();
	ge->executeOrdersPhase();

	cout << "\n\n---\t\t\tGiving a Player[" << ge->players[1]->getPlayerName() << "] Control over all the continents\t\t\t-- - " << endl;
	for (Continent* c : ge->map->getContinents())
	{
		for (Territory* t : c->getTerritories())
		{
			ge->players[1]->addTerritory(t);
		}
	}

	cout << "Number of Territories for Player [" << ge->players[0]->getPlayerName() << "] is : " << ge->players[0]->getPlayerTerritories().size() << endl;
	cout << "Number of Territories for Player [" << ge->players[1]->getPlayerName() << "] is : " << ge->players[1]->getPlayerTerritories().size() << endl;

	cout << ge->checkForWinner() << endl;
	if (ge->checkForWinner())
	{
		ge->changeState("win");
		cout << "Game is finished! replay or quit?: ";
		string input;
		cin >> input;
		if (input == "replay")
			ge->startupPhase(cp);
		else
			ge->end();
	}

}*/

