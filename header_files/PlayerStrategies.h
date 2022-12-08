#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
/*
* Created stategy pattern and PlayerStategy subclasses,
* added data member player stategy in player class
*/

class Player;
class Territory;

class PlayerStrategy
{
public:
	
	PlayerStrategy();
	PlayerStrategy(Player* player);
	virtual bool issueOrder() = 0;
	virtual std::vector<Territory*>& toDefend() = 0;
	virtual std::vector<Territory*> toAttack() = 0;
	PlayerStrategy(const PlayerStrategy&); // Copy Constructor
    PlayerStrategy& operator=(const PlayerStrategy&); //Assignment Operator
	friend ostream& operator<<(ostream& os, const PlayerStrategy& ps);	//Insertion Operator
protected:
	Player* m_player;
};

class HumanPlayerStrategy : public PlayerStrategy
{
public:
	HumanPlayerStrategy(Player* player);
	bool issueOrder() override;
	virtual std::vector<Territory*>& toDefend() override;
	virtual std::vector<Territory*> toAttack() override;
	HumanPlayerStrategy(const HumanPlayerStrategy&); // Copy Constructor
    HumanPlayerStrategy& operator=(const HumanPlayerStrategy&); //Assignment Operator
    friend ostream& operator<<(ostream& out, const HumanPlayerStrategy& a);   //Insertion Operator
};

class AggressivePlayerStrategy : public PlayerStrategy
{
public:
	AggressivePlayerStrategy(Player* player);
	bool issueOrder() override;
	virtual std::vector<Territory*>& toDefend() override;
	virtual std::vector<Territory*> toAttack() override;
	AggressivePlayerStrategy(const AggressivePlayerStrategy&); // Copy Constructor
    AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy&); //Assignment Operator
    friend ostream& operator<<(ostream& out, const AggressivePlayerStrategy& a);   //Insertion Operator
private:
	//Index of the Territory to use for Attacking
	int indexAttackingTerritory = 0;
	//Returns the next Enemy Territory to Attack
	Territory* nextToAttack();
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
public:
	BenevolentPlayerStrategy(Player* player);
	bool issueOrder() override;
	virtual std::vector<Territory*>& toDefend() override;
	virtual std::vector<Territory*> toAttack() override;
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy&); // Copy Constructor
    BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy&); //Assignment Operator
    friend ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& a);   //Insertion Operator
};

class NeutralPlayerStrategy : public PlayerStrategy
{
public:
	NeutralPlayerStrategy(Player* player);
	bool issueOrder() override;
	virtual std::vector<Territory*>& toDefend() override;
	virtual std::vector<Territory*> toAttack() override;
	NeutralPlayerStrategy(const NeutralPlayerStrategy&); // Copy Constructor
    NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy&); //Assignment Operator
    friend ostream& operator<<(ostream& out, const NeutralPlayerStrategy& a);   //Insertion Operator
private:
	int numTerritories;
};

class CheaterPlayerStrategy : public PlayerStrategy
{
public:
	CheaterPlayerStrategy(Player* player);
	bool issueOrder() override;
	virtual std::vector<Territory*>& toDefend() override;
	virtual std::vector<Territory*> toAttack() override;
	CheaterPlayerStrategy(const CheaterPlayerStrategy&); // Copy Constructor
    CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy&); //Assignment Operator
    friend ostream& operator<<(ostream& out, const CheaterPlayerStrategy& a);   //Insertion Operator
};

int random(int min, int max);