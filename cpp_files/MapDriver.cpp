#include"../header_files/MapDriver.h"
#include"../header_files/Map.h"
#include"../header_files/Player.h"
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <regex>
using namespace std;

string testLoadMaps()
{
	vector<std::string> maps;
	maps.push_back("Pangaea.map");
	maps.push_back("USA.map");
	maps.push_back("001_I72_Ghtroc 720.map");
	maps.push_back("World 2007.map");
	maps.push_back(	"Eurasia - WWII 1939.map");
	
	for (int i = 0; i < maps.size(); i++)
	{
		cout << "Testing Map: " << maps[i] << endl;
		ifstream mapFile(maps[i]);
		//ifstream mapFile("./USA.map");
		if (mapFile.is_open())
		{
			string line;
			int territoryCounter = 0;
			bool territofyflag = false;
			bool continentflag = false;
			vector<Territory*> territories;
			vector<Continent*> continents;
			vector<string> continentstmps;
			continentstmps.reserve(10);
			std::vector<string> tmps;
			tmps.reserve(1000);
			string temp;
			territories.reserve(100);
			while (getline(mapFile, temp)) {
				if (continentflag)
				{
					if (temp != "" && !(temp.find("[Territories]") != string::npos))
					{
						stringstream ss(temp);
						while (getline(ss, temp, '='))
						{
							continentstmps.push_back(temp);
						}
						continentstmps.push_back("|");
					}
				}
				if (territofyflag)
				{
					if (temp != "")
					{
						stringstream ss(temp);
						while (getline(ss, temp, ','))
						{
							tmps.push_back(temp);
						}
						tmps.push_back("|");
						territoryCounter++;
					}
				}
				if (temp.find("[Continents]") != string::npos)
					continentflag = true;
				if (temp.find("[Territories]") != string::npos)
				{
					territofyflag = true;
					continentflag = false;
				}
			}
			std::vector<string> neighbors;
			neighbors.reserve(100);
			int j = 0;
			string name, continent;
			int index = 0;
			for (int i = 0; i < tmps.size(); i++)
			{
				if (j == 0)
				{
					name = tmps[i];
					neighbors.push_back(tmps[i]);
				}
				if (j == 3)
					continent = tmps[i];
				if (j > 3 && !(tmps[i].find("|") != string::npos))
					neighbors.push_back(tmps[i]);
				j++;
				if (tmps[i].find("|") != string::npos)
				{
					j = 0;
					Player* p = new Player();
					Territory* t = new Territory(name, continent, p, 5, index);
					t->next = nullptr;
					territories.push_back(t);
					neighbors.push_back(tmps[i]);
					index++;
				}
			}
			int z = 0;
			string continentName;
			int powerup = 0;
			for (int i = 0; i < continentstmps.size(); i++)
			{
				if (z == 0 && !(continentstmps[i].find("|") != string::npos))
				{
					continentName = continentstmps[i];
				}
				if (z == 1 && !(continentstmps[i].find("|") != string::npos))
				{
					powerup = stoi(continentstmps[i]);
				}
				z++;
				if (z > 1 && continentstmps[i] == "|")
				{
					z = 0;
					Continent* continent = new Continent(powerup, continentName);
					continents.push_back(continent);
				}
			}
			Map newMap(territories, continents, neighbors);
			neighbors.clear();
			neighbors.shrink_to_fit();
			tmps.clear();
			tmps.shrink_to_fit();
			for (int i = 0; i < continents.size(); i++)
				delete continents[i];
			for (Territory* t : territories)
			{
				delete t;
			}
			continents.clear();
			continents.shrink_to_fit();
			territories.clear();
			territories.shrink_to_fit();
			mapFile.close();
		}
		else {
			std::cout << "File not Found!" << endl;
		}
	}
	
	return "";
}