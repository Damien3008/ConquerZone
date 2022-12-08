#include "../header_files/PlayerStrategies.h"
#include "../header_files/Orders.h"
#include "../header_files/Player.h"
#include<iostream>
#include<vector>
using namespace std;

Map* getMap(string _map);

PlayerStrategy* getStrategy(int type, Player* player)
{
	PlayerStrategy* strategy = nullptr;
	switch (type) {
		//Agressive
	case 2:
		return new AggressivePlayerStrategy(player);
		break;
		//Benevolent
	case 3:
		return new BenevolentPlayerStrategy(player);
		break;
		//Neutral
	case 4:
		return new NeutralPlayerStrategy(player);
		break;
		//Cheater
	case 5:
		return new CheaterPlayerStrategy(player);
		break;
		//Neutral
	default:
		return new NeutralPlayerStrategy(player);
	}
}
string getPlayerName(int type, int _ID)
{
	switch (type) {
		//Agressive
	case 2:
		return "Aggressive " + std::to_string(_ID);
		break;
		//Benevolent
	case 3:
		return "Benevolent " + std::to_string(_ID);
		break;
		//Neutral
	case 4:
		return "Neutral " + std::to_string(_ID);
		break;
		//Cheater
	case 5:
		return "Cheater " + std::to_string(_ID);
		break;
		//Neutral
	default:
		return "Neutral " + std::to_string(_ID);
	}
}

void testTournament(vector<string> maps, vector<int> players, int numberOfGames, int numberOfRounds)
{
	vector<string> stats;
	int counterGames = 1;
	int roundsCounter = 0;
	string result;
	for (string _map : maps)
	{
		result += "\nMap: " + _map + "\n";
		cout << _map << " starting" << endl;
		counterGames = 1;
		while (counterGames <= numberOfGames)
		{
			roundsCounter = 0;
			GameEngine* ge = new GameEngine();
			Subject* s = new Subject();
			LogObserver* lg = new LogObserver();
			s->Attach(lg);
			CommandProcessor* cp = new CommandProcessor(lg);
			Map* theMap = getMap(_map);
			if (theMap != nullptr)
			{
				ge->map = theMap;
				if (ge->map->validate())
				{
					int _ID = 1;

					for (int typeOfPlayer : players)
					{
						Player* player = new Player(getPlayerName(typeOfPlayer, _ID), new Hand(), ge);
						PlayerStrategy* ps = getStrategy(typeOfPlayer, player);
						player->setStrategy(ps);
						ge->players.push_back(player);
						_ID++;
					}


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

					ge->distributeTerritories();

					ge->changeState("gamestart");

					string _continue;

					while (!ge->checkForWinner() && roundsCounter < numberOfRounds)
					{
						ge->reinforcementPhase();
						ge->initial = false;
						ge->issueOrdersPhase();
						ge->executeOrdersPhase();
						roundsCounter++;
					}
					result += "Game: " + to_string(counterGames) + " ";
					if (roundsCounter == numberOfRounds && !ge->checkForWinner())
						result += "Draw";
					else
						result += ge->getWinner()->getPlayerName();

				}
				else
					result += "Map not valid";
			}
			else
				result += "Map not valid";

			result += "\n";
			counterGames++;
		}
	}
	cout << "Results: " << endl;
	cout << result << endl;
	ofstream logfile;
	logfile.open("Tournament_log.txt", ofstream::app); // append setting. If gamelog.txt is not found, it will create it.
	logfile << result << endl; // output the stringToLog to the output file
	logfile.close(); // close the output file stream
}