#include "../header_files/Cards.h"
#include "../header_files/Orders.h"
#include <iostream>


void testCards()
{
	Deck aDeck;
	Hand *aHand = new Hand;
	Player player("John", aHand);

	//load 15 cards into deck
	aDeck.init();

	//print contents
	std::cout << *(aHand)<<std::endl;
	std::cout << aDeck << std::endl;

	//empty deck and fill hand
	for (int i =0; i<5; ++i)
	{
		aDeck.draw(aHand);

		std::cout<<*(aHand) << std::endl;
		std::cout<<aDeck << std::endl;
	}

	//empty hand and fill deck
	while (aHand->getSize() != 0)
	{
		aHand->getCard(0)->play(aHand, &aDeck, &player);

		std::cout << *(aHand) << std::endl;
		std::cout << aDeck << std::endl;
	}

}


