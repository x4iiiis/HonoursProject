#pragma once

#include <string>
#include <vector>

#include "card.h"
using namespace std;

class player
{
public:
	string name;
	vector<card> hand;
	bool canPlay = false;

	//Shouldn't need this method, it's just here as a hacky getaround
	//for PlayerList creating a copy of players rather than referencing them
	void update_hand(vector<card>& newHand)
	{
		hand = newHand;
	}


};
