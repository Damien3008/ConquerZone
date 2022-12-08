//include the necessary headers

#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;
//forward declariations

extern int testCommandProcessor();
extern void testStartupPhase();
extern void testPlayerStrategies();
extern void testTournament(vector<string> maps, vector<int> players, int numberOfGames, int numberOfRounds);
//extern void testMainGameLoop();
//extern void testOrderExecution();
//extern void testLoggingObserver();

void tournamentMode(int size, char** arguments)
{
	vector<string> maps;
	vector<int> players;
	int numberOfGames = 0;
	int numberOfRounds = 0;
	//tournament -M <USA.map> -P <2,3,4> -G <1> -D <5>
	for (int i = 2; arguments[i] != NULL; ++i)
	{
		//cout << arguments[i] << endl;
		if (strcmp(arguments[i], "-M") == 0)
		{
			int j = i + 1;
			while (strcmp(arguments[j], "-P") != 0)
			{
				if (maps.size() <=5)
					maps.push_back(arguments[j]);
				j++;
			}
		}
		if (strcmp(arguments[i], "-P") == 0)
		{
			int j = i + 1;
			while (strcmp(arguments[j], "-G") != 0)
			{
				int player = *arguments[j] - '0';
				if (player < 2)
					player = 2;
				if (player > 5)
					player = 5;
				players.push_back(player);
				j++;
			}
			
		}
		if (strcmp(arguments[i], "-G") == 0)
		{
			int j = i + 1;
			numberOfGames = *arguments[j] - '0';
		}
		if (strcmp(arguments[i], "-D") == 0)
		{
			int j = i + 1;
			numberOfRounds = *arguments[j] - '0';
			if (numberOfRounds < 10)
				numberOfRounds = 10;
			if (numberOfRounds > 50)
				numberOfRounds = 50;
		}
	}

	testTournament(maps, players, numberOfGames, numberOfRounds);
}

int main(int argc, char** argv)
{
	//Format
	//tournament -M Map1.map Map2.map -P 2 2 2 3 -G 1 -D 5
	if (strcmp(argv[1], "tournament") == 0)
	{
		tournamentMode(argc, argv);
	}
	else
		testPlayerStrategies();

  return 0;
}
