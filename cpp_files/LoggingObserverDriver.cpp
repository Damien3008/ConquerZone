#include <iostream>


#include "../header_files/GameEngine.h"
#include "../header_files/Map.h"
#include "../header_files/CommandProcessing.h"
#include "../header_files/Orders.h"
#include "../header_files/Cards.h"

/*void testLoggingObserver()
{
    // Instantiate Observer object
    Observer* _obs = new LogObserver();
    // Instatiate CommandProcessor object
    CommandProcessor* commandprocessor = new CommandProcessor(_obs);
    // Instantiate GameEngine object
    GameEngine* game = new GameEngine(_obs);
    // Create a map from file and assign to this game instance
    string fileName = "../USA.map";
    // Create a new deck
    Deck *deck = new Deck();

    // Instantiating states in the GameEngine
    State* start = game->newState("start");
    State* map_loaded = game->newState("map_loaded");
    State* map_validated = game->newState("map_validated");
    State* players_added = game->newState("players_added");
    State* assign_reinforcement = game->newState("assign_reinforcement");
    State* win = game->newState("win");
    State* end_game = game->newState("end_game");

    // Instantiating transitions in the GameEngine
    game->newTransition(start, map_loaded, "loadmap");
    game->newTransition(map_loaded, map_loaded, "loadmap");
    game->newTransition(map_loaded, map_validated, "validatemap");
    game->newTransition(map_validated, players_added, "addplayer");
    game->newTransition(players_added, players_added, "addplayer");
    game->newTransition(players_added, assign_reinforcement, "gamestart");
    game->newTransition(assign_reinforcement, win, "gameend");	//For testing purposes
    game->newTransition(win, start, "replay");
    game->newTransition(win, end_game, "quit");

    // Initializing currentState and cmd_currentState in gameEngine
    game->currentState = start;
    game->cmd_currentState = start;

    string answer;
    string cmd_fileName;

    // Testing the CommandProcessor ILoggable/Subject implementation
    cout << "\nTesting CommandProcessor ILoggable/Subject implementation.." << endl << "***************************************************" << endl;
    cout << "Do you wish to accept commands from the console or read them from a file? " << '\n';

    cin >> answer; // answer for file or console

    // if / else if for user input
    if (answer == "console") {
        cout << "\nPlease enter a command: " << '\n';

        // Testing Notify in commandprocessor
        cout << "Testing command and commandprocessor Notify()..." << endl;
        while (!(commandprocessor->getExitProgram())) {
            commandprocessor->getCommand(game, commandprocessor);
        }
        
        // preventing memory leaks
        delete commandprocessor;
        commandprocessor = NULL;
    }
    else if (answer == "file") {
        cout << "\nWhich file do you wish to open? " << '\n';

        // user in for filename
        cin >> cmd_fileName;

        // read from the file
        FileLineReader* fileReader = new FileLineReader();
        fileReader->readLineFromFile(cmd_fileName);

        // command processor now reads from the file
        FileCommandProcessorAdapter* filecmd = new FileCommandProcessorAdapter(fileReader, _obs);
        // Testing command and commandprocessor Notify()
        cout << "Testing command and commandprocessor Notify()..." << endl;
        while (!(commandprocessor->getExitProgram())) {
            commandprocessor->getCommand(game, filecmd);
        }

        // preventing memory leaks
        delete filecmd;
        delete fileReader;
        filecmd = NULL;
        fileReader = NULL;

    }

    // Testing Orders ILoggable/Subject implementation
    cout << "\nTesting Orders ILoggable/Subject implementation..." << endl << "***************************************************" << endl;
    // Add new players
    Player* p1 = new Player("P1", new Hand(), game);
    Player* p2 = new Player("P2", new Hand(), game);

    // Adding territories
    auto* territory1 = new Territory();
    auto* territory2 = new Territory();

    // Associating territories and armies to players
    p1->addOwnedTerritory(territory1);
    p2->addOwnedTerritory(territory2);
    territory1->setNumberArmies(20);
    territory2->setNumberArmies(20);

    // Testing Order instantiation
    cout << "Testing order instantiation..." << endl;
    Order* Deploy = new deploy(p1, territory1, 10, game);
    Order* Advance = new advanceOrder(p1, territory1, territory2, p2, 20,  game);
    Order* Bomb = new bomb(p2, territory2, deck, game);
    Order* Blockade = new blockade(p1, territory1, deck, p2, game);
    Order* Negotiate = new negotiate(p1, p2, deck, game);
    Order* Airlift = new airlift(p1, territory1, territory2, 20, deck, game);


    // Testing orderList Notify()
    cout << "Testing orderList Notify()..." << endl;
    p1->getPlayerOrdersList()->addOrder(Deploy);
    p1->getPlayerOrdersList()->addOrder(Advance);
    p2->getPlayerOrdersList()->addOrder(Bomb);
    p2->getPlayerOrdersList()->addOrder(Blockade);
    p2->getPlayerOrdersList()->addOrder(Negotiate);
    p2->getPlayerOrdersList()->addOrder(Airlift);
    
    // Testing order execute() Notify()
    cout << "Testing orders execute Notify()..." << endl;
    Deploy->execute();    
    Advance->execute();
    Bomb->execute();
    Blockade->execute();
    Negotiate->execute();
    Airlift->execute();    

    // GameEngine ILoggable/Subject implementation
    cout << "\nTesting GameEngine ILoggable/Subject implementation..." << endl << "***************************************************" << endl;

    // replaying the game
    game->changeState("replay");

    cout << "Artificially changing game states to show Notify()/stringToLog() output.." << endl;
    // artificially changing game states
    // changing state to loadmap
    game->changeState("loadmap");
    // changing state to validatemap
    game->changeState("validatemap");
    // changing state to addplayer
    game->changeState("addplayer");


    // preventing memory leaks
    // end() delete the GameEngine (game) object
    game->end();
    game = nullptr;

    delete commandprocessor;
    commandprocessor = nullptr;

    delete _obs;
    _obs = nullptr;

    delete territory1, territory2;
    territory1, territory2 = nullptr;
}*/
