#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class card
{
public:
	enum class suit { Clubs, Diamonds, Hearts, Spades };
	enum class type { Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
	enum class colour { Red, Black };

	suit cardSuit;
	type cardType;
	colour cardColour;
	Sprite sprite;
	Texture texture;

	void setColour()
	{
		if (cardSuit == card::suit::Clubs || cardSuit == card::suit::Spades)
		{
			cardColour = card::colour::Black;
		}

		if (cardSuit == card::suit::Diamonds || cardSuit == card::suit::Hearts)
		{
			cardColour = card::colour::Red;
		}
	}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Hacky debug methods
	void PickYourOwnLastCard(card::type ctype, card::suit csuit)
	{
		cardType = ctype;
		cardSuit = csuit;
	}





};
