#pragma once

#include <string>
#include <vector>

#include <memory>

#include "card.h"
using namespace std;

class player
{
public:
	string name;
	vector<shared_ptr<card>> hand;
	bool canPlay = false;
};
