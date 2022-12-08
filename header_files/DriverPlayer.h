#pragma once // preprocessing directive for avoiding to add this file twice.

// Declaration of the libraries and headers needed.
#include "Player.h" 
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

#include <iostream>
    using std::cout;
    using std::endl;

// testPlayer function to show the different methods of the Player part.
void testPlayers()
{
	// Create new player, territory, order, and hand objects
	// Using pointers as they are user-created classes
	Card *c1 = new Card(1), *c2 = new Card(2), *c3 = new Card(3), *c4 = new Card(4);
	Hand *h1 = new Hand(), *h2 = new Hand();
	Player *p1 = new Player("player1", h1), *p2 = new Player("player2", h2);
	Territory *t1 = new Territory("territory1"), *t2 = new Territory("territory2"), *t3 = new Territory("territory3"), *t4 = new Territory("territory4");
	// Add cards to hand of each player
	h1->add(c1); h1->add(c2);
	h2->add(c3); h2->add(c4);
	// Add territories to player 1 and 2
	p1->addTerritory(t1); p1->addTerritory(t2); 
	p2->addTerritory(t3); p2->addTerritory(t4); 

    // Print out players
    cout << *p1 << endl;
    cout << *p2 << endl;

	
	// Printing out the territories to defend for Player 1 and 2
	cout << endl << "Territories for player 1 to defend:" << endl;
	for (Territory* t : p1->toDefend()) {
		cout << t->details() << endl;
	}

    cout << endl << "Territories for player 2 to defend:" << endl;
	for (Territory* t : p2->toDefend()) {
		cout << t->details() << endl;
	}

	// Printing out the territories to attack for Player 1 and 2
	cout << endl << "Territories for player 1 to attack:" << endl;
	for (Territory* t : p1->toAttack()) {
		cout << t->details() << endl;
	}

    cout << endl << "Territories for player 2 to attack:" << endl;
	for (Territory* t : p2->toAttack()) {
		cout << t->details() << endl;
	}
	
	// Issuing and printing out orders given to Player 1 and 2
	p1->issueOrder("deploy");
	p2->issueOrder("bomb");

	// Delete all pointers that a "new" assignment on the right-hand side
	delete p1; delete p2;
	// Avoid dangling pointers by assigning NULL to deleted pointers
	p1 = nullptr; p2 = nullptr;
}