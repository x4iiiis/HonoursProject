#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <memory>

#include "player.h"

using namespace std;

class Ranking
{
private:
	vector<shared_ptr<player>> Scoreboard;

public:
	
	void PlayerIsOut(shared_ptr<player> player)
	{
		Scoreboard.push_back(player);
	}

	void DisplayScoreboard()
	{
		cout << "Scoreboard:" << endl;
		for (int i = 0; i < Scoreboard.size(); i++)
		{
			switch (i)
			{
			case 0:
				cout << "1st:\t\t" << Scoreboard[i]->name;
				break;
			case 1:
				cout << "2nd:\t\t" << Scoreboard[i]->name;
				break;
			case 2:
				cout << "3rd:\t\t" << Scoreboard[i]->name;
				break;
			case 3:
				cout << "4th:\t\t" << Scoreboard[i]->name;
				break;
			default:
				break;
			}
		}
	}

	bool Gameover(int InitialNumberOfPlayers)
	{
		if (Scoreboard.size() == InitialNumberOfPlayers - 1)
		{
			return true;
		}
		return false;
	}
};