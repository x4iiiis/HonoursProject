#pragma once

#include <vector>
#include <memory>
#include <ctime>

#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>



#include "card.h"
#include "GameManager.h"

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Deck
{
private:
	//GameManager *GM = GameManager::Manager();

	//Creating all the cards
	card ca, c2, c3, c4, c5, c6, c7, c8, c9, c10, cj, cq, ck;	//Clubs
	card da, d2, d3, d4, d5, d6, d7, d8, d9, d10, dj, dq, dk;	//Diamonds
	card ha, h2, h3, h4, h5, h6, h7, h8, h9, h10, hj, hq, hk;	//Hearts
	card sa, s2, s3, s4, s5, s6, s7, s8, s9, s10, sj, sq, sk;	//Spades


	//Creating card Textures
	Texture caTex, c2Tex, c3Tex, c4Tex, c5Tex, c6Tex, c7Tex, c8Tex, c9Tex, c10Tex, cjTex, cqTex, ckTex;	//Clubs
	Texture	daTex, d2Tex, d3Tex, d4Tex, d5Tex, d6Tex, d7Tex, d8Tex, d9Tex, d10Tex, djTex, dqTex, dkTex;	//Diamonds
	Texture	haTex, h2Tex, h3Tex, h4Tex, h5Tex, h6Tex, h7Tex, h8Tex, h9Tex, h10Tex, hjTex, hqTex, hkTex;	//Hearts
	Texture	saTex, s2Tex, s3Tex, s4Tex, s5Tex, s6Tex, s7Tex, s8Tex, s9Tex, s10Tex, sjTex, sqTex, skTex;	//Spades

	Texture FaceDownTex;

	//Load image files for card textures
	void LoadTextures()
	{
		//Cards that are face down
		if (!FaceDownTex.loadFromFile("Cards/cardBack_green5.png")) { throw std::invalid_argument("FaceDownTex is fucked!"); }

		//Clubs
		if (!caTex.loadFromFile("Cards/cardClubsA.png")) { throw std::invalid_argument("caTex is fucked!"); }
		if (!c2Tex.loadFromFile("Cards/cardClubs2.png")) { throw std::invalid_argument("c2Tex is fucked!"); }
		if (!c3Tex.loadFromFile("Cards/cardClubs3.png")) { throw std::invalid_argument("c3Tex is fucked!"); }
		if (!c4Tex.loadFromFile("Cards/cardClubs4.png")) { throw std::invalid_argument("c4Tex is fucked!"); }
		if (!c5Tex.loadFromFile("Cards/cardClubs5.png")) { throw std::invalid_argument("c5Tex is fucked!"); }
		if (!c6Tex.loadFromFile("Cards/cardClubs6.png")) { throw std::invalid_argument("c6Tex is fucked!"); }
		if (!c7Tex.loadFromFile("Cards/cardClubs7.png")) { throw std::invalid_argument("c7Tex is fucked!"); }
		if (!c8Tex.loadFromFile("Cards/cardClubs8.png")) { throw std::invalid_argument("c8Tex is fucked!"); }
		if (!c9Tex.loadFromFile("Cards/cardClubs9.png")) { throw std::invalid_argument("c9Tex is fucked!"); }
		if (!c10Tex.loadFromFile("Cards/cardClubs10.png")) { throw std::invalid_argument("c10Tex is fucked!"); }
		if (!cjTex.loadFromFile("Cards/cardClubsJ.png")) { throw std::invalid_argument("cjTex is fucked!"); }
		if (!cqTex.loadFromFile("Cards/cardClubsQ.png")) { throw std::invalid_argument("cqTex is fucked!"); }
		if (!ckTex.loadFromFile("Cards/cardClubsK.png")) { throw std::invalid_argument("ckTex is fucked!"); }
		//Diamonds
		if (!daTex.loadFromFile("Cards/cardDiamondsA.png")) { throw std::invalid_argument("daTex is fucked!"); }
		if (!d2Tex.loadFromFile("Cards/cardDiamonds2.png")) { throw std::invalid_argument("d2Tex is fucked!"); }
		if (!d3Tex.loadFromFile("Cards/cardDiamonds3.png")) { throw std::invalid_argument("d3Tex is fucked!"); }
		if (!d4Tex.loadFromFile("Cards/cardDiamonds4.png")) { throw std::invalid_argument("d4Tex is fucked!"); }
		if (!d5Tex.loadFromFile("Cards/cardDiamonds5.png")) { throw std::invalid_argument("d5Tex is fucked!"); }
		if (!d6Tex.loadFromFile("Cards/cardDiamonds6.png")) { throw std::invalid_argument("d6Tex is fucked!"); }
		if (!d7Tex.loadFromFile("Cards/cardDiamonds7.png")) { throw std::invalid_argument("d7Tex is fucked!"); }
		if (!d8Tex.loadFromFile("Cards/cardDiamonds8.png")) { throw std::invalid_argument("d8Tex is fucked!"); }
		if (!d9Tex.loadFromFile("Cards/cardDiamonds9.png")) { throw std::invalid_argument("d9Tex is fucked!"); }
		if (!d10Tex.loadFromFile("Cards/cardDiamonds10.png")) { throw std::invalid_argument("d10Tex is fucked!"); }
		if (!djTex.loadFromFile("Cards/cardDiamondsJ.png")) { throw std::invalid_argument("djTex is fucked!"); }
		if (!dqTex.loadFromFile("Cards/cardDiamondsQ.png")) { throw std::invalid_argument("dqTex is fucked!"); }
		if (!dkTex.loadFromFile("Cards/cardDiamondsK.png")) { throw std::invalid_argument("dkTex is fucked!"); }
		//Hearts
		if (!haTex.loadFromFile("Cards/cardHeartsA.png")) { throw std::invalid_argument("haTex is fucked!"); }
		if (!h2Tex.loadFromFile("Cards/cardHearts2.png")) { throw std::invalid_argument("h2Tex is fucked!"); }
		if (!h3Tex.loadFromFile("Cards/cardHearts3.png")) { throw std::invalid_argument("h3Tex is fucked!"); }
		if (!h4Tex.loadFromFile("Cards/cardHearts4.png")) { throw std::invalid_argument("h4Tex is fucked!"); }
		if (!h5Tex.loadFromFile("Cards/cardHearts5.png")) { throw std::invalid_argument("h5Tex is fucked!"); }
		if (!h6Tex.loadFromFile("Cards/cardHearts6.png")) { throw std::invalid_argument("h6Tex is fucked!"); }
		if (!h7Tex.loadFromFile("Cards/cardHearts7.png")) { throw std::invalid_argument("h7Tex is fucked!"); }
		if (!h8Tex.loadFromFile("Cards/cardHearts8.png")) { throw std::invalid_argument("h8Tex is fucked!"); }
		if (!h9Tex.loadFromFile("Cards/cardHearts9.png")) { throw std::invalid_argument("h9Tex is fucked!"); }
		if (!h10Tex.loadFromFile("Cards/cardHearts10.png")) { throw std::invalid_argument("h10Tex is fucked!"); }
		if (!hjTex.loadFromFile("Cards/cardHeartsJ.png")) { throw std::invalid_argument("hjTex is fucked!"); }
		if (!hqTex.loadFromFile("Cards/cardHeartsQ.png")) { throw std::invalid_argument("hqTex is fucked!"); }
		if (!hkTex.loadFromFile("Cards/cardHeartsK.png")) { throw std::invalid_argument("hkTex is fucked!"); }
		//Spades
		if (!saTex.loadFromFile("Cards/cardSpadesA.png")) { throw std::invalid_argument("saTex is fucked!"); }
		if (!s2Tex.loadFromFile("Cards/cardSpades2.png")) { throw std::invalid_argument("s2Tex is fucked!"); }
		if (!s3Tex.loadFromFile("Cards/cardSpades3.png")) { throw std::invalid_argument("s3Tex is fucked!"); }
		if (!s4Tex.loadFromFile("Cards/cardSpades4.png")) { throw std::invalid_argument("s4Tex is fucked!"); }
		if (!s5Tex.loadFromFile("Cards/cardSpades5.png")) { throw std::invalid_argument("s5Tex is fucked!"); }
		if (!s6Tex.loadFromFile("Cards/cardSpades6.png")) { throw std::invalid_argument("s6Tex is fucked!"); }
		if (!s7Tex.loadFromFile("Cards/cardSpades7.png")) { throw std::invalid_argument("s7Tex is fucked!"); }
		if (!s8Tex.loadFromFile("Cards/cardSpades8.png")) { throw std::invalid_argument("s8Tex is fucked!"); }
		if (!s9Tex.loadFromFile("Cards/cardSpades9.png")) { throw std::invalid_argument("s9Tex is fucked!"); }
		if (!s10Tex.loadFromFile("Cards/cardSpades10.png")) { throw std::invalid_argument("s10Tex is fucked!"); }
		if (!sjTex.loadFromFile("Cards/cardSpadesJ.png")) { throw std::invalid_argument("sjTex is fucked!"); }
		if (!sqTex.loadFromFile("Cards/cardSpadesQ.png")) { throw std::invalid_argument("sqTex is fucked!"); }
		if (!skTex.loadFromFile("Cards/cardSpadesK.png")) { throw std::invalid_argument("skTex is fucked!"); }
	}

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

	//Temp (probably)
	card Draw()
	{
		return d7;
	}


	void SetUpDeck()
	{
		LoadTextures();

		ca.cardSuit = card::suit::Clubs;		ca.cardType = card::type::Ace;			ca.sprite.setTexture(caTex);
		c2.cardSuit = card::suit::Clubs;		c2.cardType = card::type::Two;			c2.sprite.setTexture(c2Tex);
		c3.cardSuit = card::suit::Clubs;		c3.cardType = card::type::Three;		c3.sprite.setTexture(c3Tex);
		c4.cardSuit = card::suit::Clubs;		c4.cardType = card::type::Four;			c4.sprite.setTexture(c4Tex);
		c5.cardSuit = card::suit::Clubs;		c5.cardType = card::type::Five;			c5.sprite.setTexture(c5Tex);
		c6.cardSuit = card::suit::Clubs;		c6.cardType = card::type::Six;			c6.sprite.setTexture(c6Tex);
		c7.cardSuit = card::suit::Clubs;		c7.cardType = card::type::Seven;		c7.sprite.setTexture(c7Tex);
		c8.cardSuit = card::suit::Clubs;		c8.cardType = card::type::Eight;		c8.sprite.setTexture(c8Tex);
		c9.cardSuit = card::suit::Clubs;		c9.cardType = card::type::Nine;			c9.sprite.setTexture(c9Tex);
		c10.cardSuit = card::suit::Clubs;		c10.cardType = card::type::Ten;			c10.sprite.setTexture(c10Tex);
		cj.cardSuit = card::suit::Clubs;		cj.cardType = card::type::Jack;			cj.sprite.setTexture(cjTex);
		cq.cardSuit = card::suit::Clubs;		cq.cardType = card::type::Queen;		cq.sprite.setTexture(cqTex);
		ck.cardSuit = card::suit::Clubs;		ck.cardType = card::type::King;			ck.sprite.setTexture(ckTex);

		da.cardSuit = card::suit::Diamonds;		da.cardType = card::type::Ace;			da.sprite.setTexture(daTex);
		d2.cardSuit = card::suit::Diamonds;		d2.cardType = card::type::Two;			d2.sprite.setTexture(d2Tex);
		d3.cardSuit = card::suit::Diamonds;		d3.cardType = card::type::Three;		d3.sprite.setTexture(d3Tex);
		d4.cardSuit = card::suit::Diamonds;		d4.cardType = card::type::Four;			d4.sprite.setTexture(d4Tex);
		d5.cardSuit = card::suit::Diamonds;		d5.cardType = card::type::Five;			d5.sprite.setTexture(d5Tex);
		d6.cardSuit = card::suit::Diamonds;		d6.cardType = card::type::Six;			d6.sprite.setTexture(d6Tex);
		d7.cardSuit = card::suit::Diamonds;		d7.cardType = card::type::Seven;		d7.sprite.setTexture(d7Tex);
		d8.cardSuit = card::suit::Diamonds;		d8.cardType = card::type::Eight;		d8.sprite.setTexture(d8Tex);
		d9.cardSuit = card::suit::Diamonds;		d9.cardType = card::type::Nine;			d9.sprite.setTexture(d9Tex);
		d10.cardSuit = card::suit::Diamonds;	d10.cardType = card::type::Ten;			d10.sprite.setTexture(d10Tex);
		dj.cardSuit = card::suit::Diamonds;		dj.cardType = card::type::Jack;			dj.sprite.setTexture(djTex);
		dq.cardSuit = card::suit::Diamonds;		dq.cardType = card::type::Queen;		dq.sprite.setTexture(dqTex);
		dk.cardSuit = card::suit::Diamonds;		dk.cardType = card::type::King;			dk.sprite.setTexture(dkTex);

		ha.cardSuit = card::suit::Hearts;		ha.cardType = card::type::Ace;			ha.sprite.setTexture(haTex);
		h2.cardSuit = card::suit::Hearts;		h2.cardType = card::type::Two;			h2.sprite.setTexture(h2Tex);
		h3.cardSuit = card::suit::Hearts;		h3.cardType = card::type::Three;		h3.sprite.setTexture(h3Tex);
		h4.cardSuit = card::suit::Hearts;		h4.cardType = card::type::Four;			h4.sprite.setTexture(h4Tex);
		h5.cardSuit = card::suit::Hearts;		h5.cardType = card::type::Five;			h5.sprite.setTexture(h5Tex);
		h6.cardSuit = card::suit::Hearts;		h6.cardType = card::type::Six;			h6.sprite.setTexture(h6Tex);
		h7.cardSuit = card::suit::Hearts;		h7.cardType = card::type::Seven;		h7.sprite.setTexture(h7Tex);
		h8.cardSuit = card::suit::Hearts;		h8.cardType = card::type::Eight;		h8.sprite.setTexture(h8Tex);
		h9.cardSuit = card::suit::Hearts;		h9.cardType = card::type::Nine;			h9.sprite.setTexture(h9Tex);
		h10.cardSuit = card::suit::Hearts;		h10.cardType = card::type::Ten;			h10.sprite.setTexture(h10Tex);
		hj.cardSuit = card::suit::Hearts;		hj.cardType = card::type::Jack;			hj.sprite.setTexture(hjTex);
		hq.cardSuit = card::suit::Hearts;		hq.cardType = card::type::Queen;		hq.sprite.setTexture(hqTex);
		hk.cardSuit = card::suit::Hearts;		hk.cardType = card::type::King;			hk.sprite.setTexture(hkTex);

		sa.cardSuit = card::suit::Spades;		sa.cardType = card::type::Ace;			sa.sprite.setTexture(saTex);
		s2.cardSuit = card::suit::Spades;		s2.cardType = card::type::Two;			s2.sprite.setTexture(s2Tex);
		s3.cardSuit = card::suit::Spades;		s3.cardType = card::type::Three;		s3.sprite.setTexture(s3Tex);
		s4.cardSuit = card::suit::Spades;		s4.cardType = card::type::Four;			s4.sprite.setTexture(s4Tex);
		s5.cardSuit = card::suit::Spades;		s5.cardType = card::type::Five;			s5.sprite.setTexture(s5Tex);
		s6.cardSuit = card::suit::Spades;		s6.cardType = card::type::Six;			s6.sprite.setTexture(s6Tex);
		s7.cardSuit = card::suit::Spades;		s7.cardType = card::type::Seven;		s7.sprite.setTexture(s7Tex);
		s8.cardSuit = card::suit::Spades;		s8.cardType = card::type::Eight;		s8.sprite.setTexture(s8Tex);
		s9.cardSuit = card::suit::Spades;		s9.cardType = card::type::Nine;			s9.sprite.setTexture(s9Tex);
		s10.cardSuit = card::suit::Spades;		s10.cardType = card::type::Ten;			s10.sprite.setTexture(s10Tex);
		sj.cardSuit = card::suit::Spades;		sj.cardType = card::type::Jack;			sj.sprite.setTexture(sjTex);
		sq.cardSuit = card::suit::Spades;		sq.cardType = card::type::Queen;		sq.sprite.setTexture(sqTex);
		sk.cardSuit = card::suit::Spades;		sk.cardType = card::type::King;			sk.sprite.setTexture(skTex);

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
