#include "../header_files/Cards.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>


//default constructor
Hand::Hand() = default;

//copy constructor
Hand::Hand(const Hand& aHand)
{
	m_cards = aHand.m_cards;
}

//destructor
Hand::~Hand()
{
	for (int i = 0; i < m_cards.size(); i++)
		delete m_cards[i];
}

//assignment operator overload
Hand& Hand::operator=(const Hand& aHand)
{
	m_cards = aHand.m_cards;
	return *this;
}

//stream insertion operator overload
std::ostream& operator<<(std::ostream &out, const Hand& aHand)
{
	std::string contents;
	for (int i = 0; i < aHand.getSize(); i++)
	{
		contents += aHand.m_cards[i]->toString() + '\n';
	}
	return out << "Hand [" <<aHand.getSize() << " cards]\n" + contents;
}

//takes card pointer as input and adds it to the back of the hand
void Hand::add(Card* card)
{
	m_cards.push_back(card);
}

//Removes card from m_cards at a given index from, takes an integer as input
void Hand::remove(int i)
{
	m_cards.erase(m_cards.begin()+i);
}

void Hand::returnCard(Card* card, Deck* deck)
{
	for (int i = 0; i <= m_cards.size() - 1; i++) {

		if (card->getType() == m_cards[i]->getType()) {
			 
			deck->add(card);
			remove(i);
			return;
		}

	}
}

//Return a card pointer at given index from hand, takes integer as input
Card* Hand::getCard(int i) const
{
	return m_cards[i];
}

std::vector<Card*> Hand::getCards() const
{
	return this->m_cards;
}

//Returns the number of cards in the deck/size of m_cards
int Hand::getSize() const
{
	return m_cards.size();
}

//default constructor
Deck::Deck() = default;

//copy constructor
Deck::Deck(const Deck& aDeck)
{
	m_cards = aDeck.m_cards;
}

//destructor
//deletes all objects that are pointed to in by the card pointers in m_cards
Deck::~Deck() 
{
	for (int i = 0; i < m_cards.size(); i++)
		delete m_cards[i];
}

//assignment operator overload
Deck& Deck::operator=(const Deck& aDeck)
{
	m_cards = aDeck.m_cards;
	return *this;
}

//insertion operator overload
std::ostream& operator<<(std::ostream& out, const Deck& aDeck)
{
	std::string contents;
	for (int i = 0; i < aDeck.getSize(); i++)
	{
		contents += aDeck.m_cards[i]->toString() + '\n';
	}
	return out << "Deck [" << aDeck.getSize() << " cards]\n" + contents;
}

//adds Card to back of deck
void Deck::add(Card* card)
{
	m_cards.push_back(card);
}

//takes Hand pointer as input, swaps the index of the first card and another random card
//adds the first Card to the Hand, removes it from the top of the Deck
void Deck::draw(Hand* aHand)
{
	std::random_device rd;
	std::mt19937 rng(rd());

	std::shuffle(m_cards.begin(), m_cards.end(),rng);
	std::cout << "drew " << *m_cards[0] << endl;
	aHand->add(m_cards[0]);
	m_cards.erase(m_cards.begin());
}

//Initializes deck by adding DECK_SIZE cards into the deck
void Deck::init()
{
	for (int i = 0, id = 1; i < DECK_SIZE; ++i, ++id)
	{
		if (id > 5)
			id = 1;
		m_cards.push_back(new Card(id));
	}
}

//returns the number of cards in the Deck
int Deck::getSize() const
{
	return m_cards.size();
}

//Default constructor
//create a card using an int from 1-5 as input
Card::Card(int typeID)
{
	switch (typeID)
	{
	case 1:
		m_type = "bomb";
		break;
	case 2:
		m_type = "blockade";
		break;
	case 3:
		m_type = "airlift";
		break;
	case 4:
		m_type = "diplomacy";
		break;
	case 5:
		m_type = "reinforcement";
		break;
	default:
		m_type = "undeclared";
		break;
	}

}

Card::Card(std::string type) : m_type{ type } {}

//copy constructor
Card::Card(const Card& aCard)
{
	m_type = aCard.m_type;
}

//destructor
Card::~Card() = default;

//assignment operator overload
Card& Card::operator=(const Card& aCard)
{
	m_type = aCard.m_type;
	return *this;
}

//stream insertion operator overload
std::ostream& operator<<(std::ostream& out, const Card& aCard)
{
	return out << "Card [" << aCard.m_type << "]";
}

//takes Hand pointer, Deck pointer and player pointer as input
//if this card is present in Hand, remove it and place it in deck, 
//create order and place it in player's orderList
void Card::play(Hand* hand, Deck* deck, Player* player)
{

	for (int i = 0; i < hand->getSize(); ++i)
	{
		if (this == hand->getCard(i))
		{
		
			std::cout << "playing " << *this <<"\n\n";

			//add order to player's orderlist
			if (m_type == "diplomacy")
				player->issueOrder();
			else if (m_type == "reinforcement")
				std::cout << "Reinforcement card played, no orders created.\n";
			else
				player->issueOrder();

			deck->add(this);		//add card to deck
			hand->remove(i);		//remove card from hand
			return;
		}
	}
}

//returns a string indicating the Class and type
std::string Card::toString() const
{
	return "Card [" + m_type + "]";
}

//returns the type of the card
std::string Card::getType() const
{
	return m_type;
}



