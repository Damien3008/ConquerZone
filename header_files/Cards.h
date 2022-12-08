#pragma once
#include "../header_files/Player.h"
#include <string>
#include <vector>

//stores the number of cards in the deck
const int DECK_SIZE = 15;

class Card;		//declare so the Hand and Deck can use it
class Player;
class Deck;
//Hand Class
class Hand
{
public:
	Hand();
	~Hand();
	Hand(const Hand& aHand);
	Hand& operator = (const Hand& aHand);
	friend std::ostream& operator << (std::ostream& out, const Hand &aHand);
	void add(Card* card);
	void remove(int i);
	void returnCard(Card* card, Deck* deck);
	int getSize() const;
	Card* getCard(int i) const;
	std::vector<Card*> getCards() const;

private:
	std::vector<Card*> m_cards;

};

//Deck class
class Deck
{

public:
	Deck();
	~Deck();
	Deck(const Deck& aDeck);
	Deck& operator = (const Deck& aDeck);
	friend std::ostream& operator << (std::ostream& out, const Deck& aDeck);
	void draw(Hand* aHand);
	void init();
	void add(Card* card);
	int getSize() const;
private:
	std::vector<Card*> m_cards;
};

//Card class
class OrdersList;
class Card
{
public:
	Card(int typeID);
	Card(std::string type);
	~Card();
	Card(const Card& aCard);
	Card& operator = (const Card& aCard);
	friend std::ostream& operator << (std::ostream& out, const Card& aCard);
	void play(Hand* hand, Deck* deck, Player* player);
	std::string toString() const;
	std::string getType() const;
private:
	std::string m_type;
};


