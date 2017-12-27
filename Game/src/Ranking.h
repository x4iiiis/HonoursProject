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
	
	void PlayerIsOut(shared_ptr<player> player, int numberOfPlayers)
	{
		Scoreboard.push_back(player);

		if (Scoreboard.size() < numberOfPlayers)
		{
			cout << endl << player->name << " is out!";

			if (Scoreboard.size() != numberOfPlayers - 1)
			{
				DisplayScoreboard();
				cout << endl << endl;
			}
		}
	}

	void DisplayScoreboard()
	{
		cout << endl << endl << "Scoreboard:" << endl;
		for (int i = 0; i < Scoreboard.size(); i++)
		{
			switch (i)
			{
			case 0:
				cout << "1st:\t" << Scoreboard[i]->name << "\t\t\t" << Scoreboard[i]->getPlaystyle() << endl;
				break;
			case 1:
				cout << "2nd:\t" << Scoreboard[i]->name << "\t\t\t" << Scoreboard[i]->getPlaystyle() << endl;
				break;
			case 2:
				cout << "3rd:\t" << Scoreboard[i]->name << "\t\t\t" << Scoreboard[i]->getPlaystyle() << endl;
				break;
			case 3:
				cout << "4th:\t" << Scoreboard[i]->name << "\t\t\t" << Scoreboard[i]->getPlaystyle() << endl;
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