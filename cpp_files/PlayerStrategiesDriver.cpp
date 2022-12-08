#include "../header_files/PlayerStrategies.h"
#include "../header_files/Orders.h"
#include "../header_files/Player.h"

#include <iostream>


Map* getMap();


void testPlayerStrategies()
{
	GameEngine* ge = new GameEngine();
	Subject* s = new Subject();
	LogObserver* lg = new LogObserver();
	s->Attach(lg);
	CommandProcessor* cp = new CommandProcessor(lg);
	cout << "---\t\t\tLoading Map\t\t\t---" << endl;
	ge->map = getMap();
	cout << *ge->map << endl;
	cout << "---\t\t\tValidating Map\t\t\t---" << endl;
	ge->map->validate();


	cout << "\n\n---\t\t\tAdding Two Players\t\t\t---" << endl;

	

	Player* player0 = new Player("H1", new Hand(), ge);
	Player* player1 = new Player("A1", new Hand(), ge);
	Player* player2 = new Player("C1", new Hand(), ge);
	Player* player3 = new Player("A2", new Hand(), ge);
	Player* player4 = new Player("N3", new Hand(), ge);
	Player* player5 = new Player("B1", new Hand(), ge);

	HumanPlayerStrategy* aps0 = new HumanPlayerStrategy(player0);
	AggressivePlayerStrategy* aps = new AggressivePlayerStrategy(player1);
	CheaterPlayerStrategy* aps2 = new CheaterPlayerStrategy(player2);
	AggressivePlayerStrategy* aps3 = new AggressivePlayerStrategy(player3);
	NeutralPlayerStrategy* aps4 = new NeutralPlayerStrategy(player4);
	BenevolentPlayerStrategy* aps5 = new BenevolentPlayerStrategy(player5);

	player0->setStrategy(aps0);
	player1->setStrategy(aps);
	player2->setStrategy(aps2);
	player3->setStrategy(aps3);
	player4->setStrategy(aps4);
	player5->setStrategy(aps5);
	
	//ge->players.push_back(player0);
	ge->players.push_back(player1);
	ge->players.push_back(player2);
	ge->players.push_back(player3);
	ge->players.push_back(player4);
	ge->players.push_back(player5);

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

	int numberOfRounds = 0;

	string _continue;

	while (!ge->checkForWinner())
	{
		cout << "______________________________________" << endl;
		cout << "Round: " << (++numberOfRounds) << endl;
		cout << "______________________________________" << endl;
		for (Player* player : ge->players)
		{
			cout << "Player [" + player->getPlayerName() + "] has: " + std::to_string(player->getPlayerTerritories().size()) << endl;
		}
		ge->reinforcementPhase();
		ge->initial = false;
		ge->issueOrdersPhase();
		ge->executeOrdersPhase();
		cout << "Press Enter to Continue";
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	}

	ge->end();

}