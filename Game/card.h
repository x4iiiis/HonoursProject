#pragma once

class card
{
public:
	enum class suit { Clubs, Diamonds, Hearts, Spades };
	enum class type { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

	suit cardSuit;
	type cardType;
};
