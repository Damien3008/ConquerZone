#pragma once
#include <string>
#include <iostream>
#include "../header_files/LoggingObserver.h"
#include "../header_files/Player.h"
#include "../header_files/Map.h"
#include "../header_files/CommandProcessing.h"
#include "../header_files/Cards.h"

// Forward class definiton
class Player;
class Map;
class Deck;
class CommandProcessor;
class Observer;
class ILoggable;
class Subject;
// A State holds a string
class State
{
public:
	// State's name
	string stateName;
	// Default constructor
	State();
	// Parametrized constructor
	State(string name);
	// Copy constructor
	State(const State& state);
	// = assignment operator
	State& operator=(const State& state);
	// << ostream conversion
	friend ostream& operator<<(ostream& out, const State& state);
};

// Contains pointers from one state to another as well as its required command
class Transition
{
public:
	// current state
	State* current;
	// next state
	State* next;
	// Required command to perform transition
	string command;
	// Default Constructor
	Transition();
	// Parametrized Constructor
	Transition(State* current, State* next, string command);
	// Copy constructor
	Transition(const Transition& transition);
	// = assignment operator
	Transition& operator=(const Transition& transition);
	// << ostream conversion
	friend ostream& operator<<(ostream& out, const Transition& transition);
};


class GameEngine : public ILoggable, public Subject
{
public:
	GameEngine(); //default constructor
	// Observer pattern constructor
	GameEngine(Observer* _obs);
	void run(); //run mathod
	GameEngine(const GameEngine &old_obj); //copy constructor
	GameEngine& operator =(const GameEngine& GameEngine);   // Assignment operator
	// Reinforcement Phase
	void reinforcementPhase();
	//issue orders phase
	void issueOrdersPhase();
	// execute orders phase
	void executeOrdersPhase();
	// Getter for deck
	Deck* getDeck();
	// Getter for map
	Map* getMap();
	// Sets the map
	void setMap(Map*);
	// Adds players to player list
	void addPlayer(Player*);
	// Remove a player from the player list
	void removePlayer(Player*);
	// STRICTLY Checks the states (USED BY COMMAND PROCESSOR)
	bool checkState(string command);
	// Startup
	void startupPhase(CommandProcessor *cp);
	// Main loop
	void mainGameLoop();
	// Creates a new state
	State* newState(string state);
	// Creates a new Transition
	void newTransition(State* current, State* next, string command);
	// Checks and Changes the states
	bool changeState(string command);
	// Ends the game and deletes game object
	void end();
	//Failry distributes the territories amongst ther players
	void distributeTerritories();
	//Check for a winner
	bool checkForWinner();
	// Reset GameEngine's context to start new games
	void resetContext();
	//checking for a neutral player among the list of players and if there isnt one , a pointer to one will be created
    //and added to the list of players
    Player* getNeutralPlayer();
	
public:
	// Vector of pointers to players
	vector<Player*> players; // 2 - 6 Players
	// Pointer to the current map
	Map* map;
	// Deck pointer
	Deck* deck;
	// Vector of pointers to transitions
	vector<Transition*> transitions;
	// Vector of pointers to states
	vector<State*> states;
	// Current State
	State* currentState;
	State* cmd_currentState;
	Observer* _observer = nullptr; // Observer pointer
	bool initial = true;
	//Implementation Missing
	string stringToLog();
	//Boolean which checks if gameEngine is in tournament mode
    bool tournamentMode = false;
	Player* getWinner() { return this->winner; }

private:
	//Pointer to the neutral player
	Player* neutral;
	//Pointer to the Command Processor
	CommandProcessor* cp;
	//enum for state machine
	enum state{start_game, map_loaded, map_validated, players_added, 
		assign_reinforcements, issue_orders, execute_orders, win_game};
	//Initializing all the states and setting the initial state to start
	void initializeTransitions();
	//Shuffle the starting order of the players
	void shuffleOrder();
	//reverse the satrting order of the players
	void reverseorder();
	//check for undistributed territorories and assign them to the neutral player
	void neutralTerritories();
	int m_currentState;
	int* m_currentStatePtr;
	Player* winner;

};

