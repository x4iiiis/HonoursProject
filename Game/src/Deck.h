#pragma once

#include <vector>
#include <memory>
#include <ctime>

#include "card.h"
#include "GameManager.h"

using namespace std;

class Deck
{
private:
	//GameManager *GM = GameManager::Manager();

	//Creating all the cards
	//Clubs
	card ca, c2, c3, c4, c5, c6, c7, c8, c9, c10, cj, cq, ck;
	//Diamonds
	card da, d2, d3, d4, d5, d6, d7, d8, d9, d10, dj, dq, dk;
	//Hearts
	card ha, h2, h3, h4, h5, h6, h7, h8, h9, h10, hj, hq, hk;
	//Spades
	card sa, s2, s3, s4, s5, s6, s7, s8, s9, s10, sj, sq, sk;

	//GameManager GM;

public:
	//52 cards, first index = 0
	vector<shared_ptr<card>> allCards;		//All of the cards in the pack
	vector<shared_ptr<card>> cardStack;		//Cards available to be picked up 
	vector<shared_ptr<card>> lastCard;		//Card we're going to play on top of

	void Deal(vector<shared_ptr<player>> PlayersVector, int CardsPerPlayer)
	{
		//for (int i = 0; i < GameManager::Manager()->GetCardsPerPlayer(); i++)
		for (int i = 0; i < CardsPerPlayer; i++)
		{
			//for (int j = 0; j < GameManager::Manager()->GetListOfPlayers().size(); j++)
			for (int j = 0; j < PlayersVector.size(); j++)
			{
				//GameManager::Manager()->GetListOfPlayers()[j]->hand.push_back(cardStack[0]);			//////////////////////////////////////////////////////////////////PROBLEMMMMMMMM
				PlayersVector[j]->hand.push_back(cardStack[0]);
				cardStack.erase(cardStack.begin());
			}
		}
	}

	void SetUpDeck()
	{
		ca.cardSuit = card::suit::Clubs;		ca.cardType = card::type::Ace;
		c2.cardSuit = card::suit::Clubs;		c2.cardType = card::type::Two;
		c3.cardSuit = card::suit::Clubs;		c3.cardType = card::type::Three;
		c4.cardSuit = card::suit::Clubs;		c4.cardType = card::type::Four;
		c5.cardSuit = card::suit::Clubs;		c5.cardType = card::type::Five;
		c6.cardSuit = card::suit::Clubs;		c6.cardType = card::type::Six;
		c7.cardSuit = card::suit::Clubs;		c7.cardType = card::type::Seven;
		c8.cardSuit = card::suit::Clubs;		c8.cardType = card::type::Eight;
		c9.cardSuit = card::suit::Clubs;		c9.cardType = card::type::Nine;
		c10.cardSuit = card::suit::Clubs;		c10.cardType = card::type::Ten;
		cj.cardSuit = card::suit::Clubs;		cj.cardType = card::type::Jack;
		cq.cardSuit = card::suit::Clubs;		cq.cardType = card::type::Queen;
		ck.cardSuit = card::suit::Clubs;		ck.cardType = card::type::King;

		da.cardSuit = card::suit::Diamonds;		da.cardType = card::type::Ace;
		d2.cardSuit = card::suit::Diamonds;		d2.cardType = card::type::Two;
		d3.cardSuit = card::suit::Diamonds;		d3.cardType = card::type::Three;
		d4.cardSuit = card::suit::Diamonds;		d4.cardType = card::type::Four;
		d5.cardSuit = card::suit::Diamonds;		d5.cardType = card::type::Five;
		d6.cardSuit = card::suit::Diamonds;		d6.cardType = card::type::Six;
		d7.cardSuit = card::suit::Diamonds;		d7.cardType = card::type::Seven;
		d8.cardSuit = card::suit::Diamonds;		d8.cardType = card::type::Eight;
		d9.cardSuit = card::suit::Diamonds;		d9.cardType = card::type::Nine;
		d10.cardSuit = card::suit::Diamonds;	d10.cardType = card::type::Ten;
		dj.cardSuit = card::suit::Diamonds;		dj.cardType = card::type::Jack;
		dq.cardSuit = card::suit::Diamonds;		dq.cardType = card::type::Queen;
		dk.cardSuit = card::suit::Diamonds;		dk.cardType = card::type::King;

		ha.cardSuit = card::suit::Hearts;		ha.cardType = card::type::Ace;
		h2.cardSuit = card::suit::Hearts;		h2.cardType = card::type::Two;
		h3.cardSuit = card::suit::Hearts;		h3.cardType = card::type::Three;
		h4.cardSuit = card::suit::Hearts;		h4.cardType = card::type::Four;
		h5.cardSuit = card::suit::Hearts;		h5.cardType = card::type::Five;
		h6.cardSuit = card::suit::Hearts;		h6.cardType = card::type::Six;
		h7.cardSuit = card::suit::Hearts;		h7.cardType = card::type::Seven;
		h8.cardSuit = card::suit::Hearts;		h8.cardType = card::type::Eight;
		h9.cardSuit = card::suit::Hearts;		h9.cardType = card::type::Nine;
		h10.cardSuit = card::suit::Hearts;		h10.cardType = card::type::Ten;
		hj.cardSuit = card::suit::Hearts;		hj.cardType = card::type::Jack;
		hq.cardSuit = card::suit::Hearts;		hq.cardType = card::type::Queen;
		hk.cardSuit = card::suit::Hearts;		hk.cardType = card::type::King;

		sa.cardSuit = card::suit::Spades;		sa.cardType = card::type::Ace;
		s2.cardSuit = card::suit::Spades;		s2.cardType = card::type::Two;
		s3.cardSuit = card::suit::Spades;		s3.cardType = card::type::Three;
		s4.cardSuit = card::suit::Spades;		s4.cardType = card::type::Four;
		s5.cardSuit = card::suit::Spades;		s5.cardType = card::type::Five;
		s6.cardSuit = card::suit::Spades;		s6.cardType = card::type::Six;
		s7.cardSuit = card::suit::Spades;		s7.cardType = card::type::Seven;
		s8.cardSuit = card::suit::Spades;		s8.cardType = card::type::Eight;
		s9.cardSuit = card::suit::Spades;		s9.cardType = card::type::Nine;
		s10.cardSuit = card::suit::Spades;		s10.cardType = card::type::Ten;
		sj.cardSuit = card::suit::Spades;		sj.cardType = card::type::Jack;
		sq.cardSuit = card::suit::Spades;		sq.cardType = card::type::Queen;
		sk.cardSuit = card::suit::Spades;		sk.cardType = card::type::King;

		//All cards into an array of their respected suit
		vector<shared_ptr<card>> clubsArray
		{
			make_shared<card>(ca),
			make_shared<card>(c2),
			make_shared<card>(c3),
			make_shared<card>(c4),
			make_shared<card>(c5),
			make_shared<card>(c6),
			make_shared<card>(c7),
			make_shared<card>(c8),
			make_shared<card>(c9),
			make_shared<card>(c10),
			make_shared<card>(cj),
			make_shared<card>(cq),
			make_shared<card>(ck)
		};
		vector<shared_ptr<card>> diamondsArray
		{
			make_shared<card>(da),
			make_shared<card>(d2),
			make_shared<card>(d3),
			make_shared<card>(d4),
			make_shared<card>(d5),
			make_shared<card>(d6),
			make_shared<card>(d7),
			make_shared<card>(d8),
			make_shared<card>(d9),
			make_shared<card>(d10),
			make_shared<card>(dj),
			make_shared<card>(dq),
			make_shared<card>(dk)
		};
		vector<shared_ptr<card>> heartsArray
		{
			make_shared<card>(ha),
			make_shared<card>(h2),
			make_shared<card>(h3),
			make_shared<card>(h4),
			make_shared<card>(h5),
			make_shared<card>(h6),
			make_shared<card>(h7),
			make_shared<card>(h8),
			make_shared<card>(h9),
			make_shared<card>(h10),
			make_shared<card>(hj),
			make_shared<card>(hq),
			make_shared<card>(hk)
		};
		vector<shared_ptr<card>> spadesArray
		{
			make_shared<card>(sa),
			make_shared<card>(s2),
			make_shared<card>(s3),
			make_shared<card>(s4),
			make_shared<card>(s5),
			make_shared<card>(s6),
			make_shared<card>(s7),
			make_shared<card>(s8),
			make_shared<card>(s9),
			make_shared<card>(s10),
			make_shared<card>(sj),
			make_shared<card>(sq),
			make_shared<card>(sk)
		};

		//Hold on apparently there's a random shuffle for vectors
		std::srand(std::time(0));	//For some reason shuffle doesn't work when you restart the program, it uses the previously shuffled version... this line solves that.Needs <ctime> included 
		std::random_shuffle(clubsArray.begin(), clubsArray.end());
		std::random_shuffle(diamondsArray.begin(), diamondsArray.end());
		std::random_shuffle(heartsArray.begin(), heartsArray.end());
		std::random_shuffle(spadesArray.begin(), spadesArray.end());

		//Add shuffled clubs to allCards
		for (auto c : clubsArray)
		{
			//allCards->push_back(clubsArray);
			allCards.push_back(c);
		}

		//Add shuffled diamonds to allCards
		for (auto c : diamondsArray)
		{
			allCards.push_back(c);
		}

		//Add shuffled hearts to allCards
		for (auto c : heartsArray)
		{
			allCards.push_back(c);
		}

		//Add shuffled spades to allCards
		for (auto c : spadesArray)
		{
			allCards.push_back(c);
		}

		//Set colour of all cards
		defineCardColours(allCards);


		//Shuffle allCards (give it a right good shuffle!)
		std::random_shuffle(allCards.begin(), allCards.end());
		std::random_shuffle(allCards.begin(), allCards.end());
		std::random_shuffle(allCards.begin(), allCards.end());
		std::random_shuffle(allCards.begin(), allCards.end());
		std::random_shuffle(allCards.begin(), allCards.end());

		for (auto c : allCards)
		{
			cardStack.push_back(c);
		}
	}



	void identify_cards(vector<shared_ptr<card>> unidentifiedCards)
	{
		for (auto c : unidentifiedCards)
		{
			if (c->cardType == card::type::Ace)
			{
				cout << "Ace of ";
			}
			if (c->cardType == card::type::Jack)
			{
				cout << "Jack of ";
			}
			if (c->cardType == card::type::Queen)
			{
				cout << "Queen of ";
			}
			if (c->cardType == card::type::King)
			{
				cout << "King of ";
			}
			if (c->cardType != card::type::Ace && c->cardType != card::type::Jack && c->cardType != card::type::Queen && c->cardType != card::type::King)
			{
				cout << (static_cast<int>(c->cardType) + 1) << " of ";
			}


			if (c->cardSuit == card::suit::Diamonds)
			{
				cout << "Diamonds!" << endl;
			}
			if (c->cardSuit == card::suit::Clubs)
			{
				cout << "Clubs!" << endl;
			}
			if (c->cardSuit == card::suit::Hearts)
			{
				cout << "Hearts!" << endl;
			}
			if (c->cardSuit == card::suit::Spades)
			{
				cout << "Spades!" << endl;
			}
		}
		cout << endl;
	}

	void defineCardColours(vector<shared_ptr<card>> allCards)
	{
		for (auto c : allCards)
		{
			c->setColour();
		}
	}

	string checkColour(shared_ptr<card> Card)
	{
		if (Card->cardColour == card::colour::Black)
		{
			return "Black";
		}
		//If it's not black it must be red
		return "Red";
	}
};
