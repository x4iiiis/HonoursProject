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
	//When a player is out, add them to the scoreboard
	void PlayerIsOut(shared_ptr<player> player, int numberOfPlayers)
	{
		//For keeping track of what happened each game
		fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
		if (!GameText.is_open())
		{
			cout << "Error opening GameRecords.txt" << endl << endl;
		}

		Scoreboard.push_back(player);

		if (Scoreboard.size() < numberOfPlayers)
		{
			cout << endl << player->name << " is out!";
			GameText << endl << player->name << " is out!" << endl << endl;;

			if (Scoreboard.size() != numberOfPlayers - 1)
			{
				DisplayScoreboard();
				cout << endl << endl;
			}
		}
	}

	//Print the scoreboard
	void DisplayScoreboard()
	{
		cout << endl << endl << "Scoreboard:" << endl;
		for (int i = 0; i < Scoreboard.size(); i++)
		{
			switch (i)
			{
			case 0:
				cout << "1st:\t" << setw(50) << left << Scoreboard[i]->name << Scoreboard[i]->getPlaystyle() << endl;
				break;
			case 1:
				cout << "2nd:\t" << setw(50) << left << Scoreboard[i]->name << Scoreboard[i]->getPlaystyle() << endl;
				break;
			case 2:
				cout << "3rd:\t" << setw(50) << left << Scoreboard[i]->name << Scoreboard[i]->getPlaystyle() << endl;
				break;
			case 3:
				cout << "4th:\t" << setw(50) << left << Scoreboard[i]->name << Scoreboard[i]->getPlaystyle() << endl;
				break;
			default:
				break;
			}
		}
	}

	//If there 1 less player in the scoreboard than the total number of players, it's gameover
	bool Gameover(int InitialNumberOfPlayers)
	{
		if (Scoreboard.size() == InitialNumberOfPlayers - 1)
		{
			return true;
		}
		return false;
	}

	//For accessing the scoreboard elsewhere
	vector<shared_ptr<player>> getScoreboard()
	{
		return Scoreboard;
	}

	void clear()
	{
		Scoreboard.clear();
	}
};