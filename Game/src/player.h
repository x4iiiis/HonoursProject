#pragma once

#include <string>
#include <vector>
#include <memory>

#include "card.h"

using namespace std;

class player
{
public:
	enum class Playstyle { Human, Neural, Aggressive, Unaggressive, Random };

	string name;
	Playstyle playstyle;
	vector<shared_ptr<card>> hand;
	bool canPlay;
	bool canPickUp;
	bool myTurn;

	//Return the player's playstyle as a string
	string getPlaystyle()
	{
		switch (playstyle)
		{
		case(Playstyle::Human):
			return "(Human)";
		case(Playstyle::Neural):
			return "(Agent)";
		case(Playstyle::Aggressive):
			return "(Hardcoded - Aggressive)";
		case(Playstyle::Unaggressive):
			return "(Hardcoded - Unaggressive)";
		case(Playstyle::Random):
			return "(Hardcoded - Random)";
		default:
			break;
		}
	}
};
