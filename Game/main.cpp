#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include <istream>
#include <random> 
/////////////////////////////
#include "card.h"
#include "player.h"
#include <vector>
#include <ctime>

using namespace std;

void identify_cards(vector<card> unidentifiedCards)
{
	for (auto &c : unidentifiedCards)
	{
		if (c.cardType == card::type::Ace)
		{
			cout << "Ace of ";
		}
		if (c.cardType == card::type::Jack)
		{
			cout << "Jack of ";
		}
		if (c.cardType == card::type::Queen)
		{
			cout << "Queen of ";
		}
		if (c.cardType == card::type::King)
		{
			cout << "King of ";
		}
		if (c.cardType != card::type::Ace && c.cardType != card::type::Jack && c.cardType != card::type::Queen && c.cardType != card::type::King)
		{
			cout << (static_cast<int>(c.cardType) + 1) << " of ";
		}


		if (c.cardSuit == card::suit::Diamonds)
		{
			cout << "Diamonds!" << endl;
		}
		if (c.cardSuit == card::suit::Clubs)
		{
			cout << "Clubs!" << endl;
		}
		if (c.cardSuit == card::suit::Hearts)
		{
			cout << "Hearts!" << endl;
		}
		if (c.cardSuit == card::suit::Spades)
		{
			cout << "Spades!" << endl;
		}
	}
	cout << endl;
}

bool can_play_checker(card lastCard, vector<card>hand)
{
	for (auto &c : hand)
	{
		if (c.cardSuit == lastCard.cardSuit)
		{
			cout << "Suit match!" << endl;
			return true;
		}

		if (c.cardType == lastCard.cardType)
		{
			cout << "Type match!" << endl;
			return true;
		}
	}
	//If the code makes it this far, then it hasn't found any
	//Matches in type or suit throughout the whole hand, so
	//we return false.
	cout << "No matches!" << endl;
	return false;
}


int main()
{
	//52 cards, first index = 0
	vector<card> allCards;		//All of the cards in the pack
	vector<card> cardStack;		//Cards available to be picked up 
	vector<card> lastCard;		//Card we're going to play on top of


	//Making all the cards, mingin'
	//Clubs
	card ca;		ca.cardSuit = card::suit::Clubs;		ca.cardType = card::type::Ace;
	card c2;		c2.cardSuit = card::suit::Clubs;		c2.cardType = card::type::Two;
	card c3;		c3.cardSuit = card::suit::Clubs;		c3.cardType = card::type::Three;
	card c4;		c4.cardSuit = card::suit::Clubs;		c4.cardType = card::type::Four;
	card c5;		c5.cardSuit = card::suit::Clubs;		c5.cardType = card::type::Five;
	card c6;		c6.cardSuit = card::suit::Clubs;		c6.cardType = card::type::Six;
	card c7;		c7.cardSuit = card::suit::Clubs;		c7.cardType = card::type::Seven;
	card c8;		c8.cardSuit = card::suit::Clubs;		c8.cardType = card::type::Eight;
	card c9;		c9.cardSuit = card::suit::Clubs;		c9.cardType = card::type::Nine;
	card c10;		c10.cardSuit = card::suit::Clubs;		c10.cardType = card::type::Ten;
	card cj;		cj.cardSuit = card::suit::Clubs;		cj.cardType = card::type::Jack;
	card cq;		cq.cardSuit = card::suit::Clubs;		cq.cardType = card::type::Queen;
	card ck;		ck.cardSuit = card::suit::Clubs;		ck.cardType = card::type::King;
	//Diamonds
	card da;		da.cardSuit = card::suit::Diamonds;		da.cardType = card::type::Ace;
	card d2;		d2.cardSuit = card::suit::Diamonds;		d2.cardType = card::type::Two;
	card d3;		d3.cardSuit = card::suit::Diamonds;		d3.cardType = card::type::Three;
	card d4;		d4.cardSuit = card::suit::Diamonds;		d4.cardType = card::type::Four;
	card d5;		d5.cardSuit = card::suit::Diamonds;		d5.cardType = card::type::Five;
	card d6;		d6.cardSuit = card::suit::Diamonds;		d6.cardType = card::type::Six;
	card d7;		d7.cardSuit = card::suit::Diamonds;		d7.cardType = card::type::Seven;
	card d8;		d8.cardSuit = card::suit::Diamonds;		d8.cardType = card::type::Eight;
	card d9;		d9.cardSuit = card::suit::Diamonds;		d9.cardType = card::type::Nine;
	card d10;		d10.cardSuit = card::suit::Diamonds;	d10.cardType = card::type::Ten;
	card dj;		dj.cardSuit = card::suit::Diamonds;		dj.cardType = card::type::Jack;
	card dq;		dq.cardSuit = card::suit::Diamonds;		dq.cardType = card::type::Queen;
	card dk;		dk.cardSuit = card::suit::Diamonds;		dk.cardType = card::type::King;
	//Hearts
	card ha;		ha.cardSuit = card::suit::Hearts;		ha.cardType = card::type::Ace;
	card h2;		h2.cardSuit = card::suit::Hearts;		h2.cardType = card::type::Two;
	card h3;		h3.cardSuit = card::suit::Hearts;		h3.cardType = card::type::Three;
	card h4;		h4.cardSuit = card::suit::Hearts;		h4.cardType = card::type::Four;
	card h5;		h5.cardSuit = card::suit::Hearts;		h5.cardType = card::type::Five;
	card h6;		h6.cardSuit = card::suit::Hearts;		h6.cardType = card::type::Six;
	card h7;		h7.cardSuit = card::suit::Hearts;		h7.cardType = card::type::Seven;
	card h8;		h8.cardSuit = card::suit::Hearts;		h8.cardType = card::type::Eight;
	card h9;		h9.cardSuit = card::suit::Hearts;		h9.cardType = card::type::Nine;
	card h10;		h10.cardSuit = card::suit::Hearts;		h10.cardType = card::type::Ten;
	card hj;		hj.cardSuit = card::suit::Hearts;		hj.cardType = card::type::Jack;
	card hq;		hq.cardSuit = card::suit::Hearts;		hq.cardType = card::type::Queen;
	card hk;		hk.cardSuit = card::suit::Hearts;		hk.cardType = card::type::King;
	//Spades
	card sa;		sa.cardSuit = card::suit::Spades;		sa.cardType = card::type::Ace;
	card s2;		s2.cardSuit = card::suit::Spades;		s2.cardType = card::type::Two;
	card s3;		s3.cardSuit = card::suit::Spades;		s3.cardType = card::type::Three;
	card s4;		s4.cardSuit = card::suit::Spades;		s4.cardType = card::type::Four;
	card s5;		s5.cardSuit = card::suit::Spades;		s5.cardType = card::type::Five;
	card s6;		s6.cardSuit = card::suit::Spades;		s6.cardType = card::type::Six;
	card s7;		s7.cardSuit = card::suit::Spades;		s7.cardType = card::type::Seven;
	card s8;		s8.cardSuit = card::suit::Spades;		s8.cardType = card::type::Eight;
	card s9;		s9.cardSuit = card::suit::Spades;		s9.cardType = card::type::Nine;
	card s10;		s10.cardSuit = card::suit::Spades;		s10.cardType = card::type::Ten;
	card sj;		sj.cardSuit = card::suit::Spades;		sj.cardType = card::type::Jack;
	card sq;		sq.cardSuit = card::suit::Spades;		sq.cardType = card::type::Queen;
	card sk;		sk.cardSuit = card::suit::Spades;		sk.cardType = card::type::King;

	//All cards into an array of their respected suit
	vector<card> clubsArray{ ca, c2, c3, c4, c5, c6, c7, c8, c9, c10, cj, cq, ck };
	vector<card> diamondsArray{ da, d2, d3, d4, d5, d6, d7, d8, d9, d10, dj, dq, dk };
	vector<card> heartsArray{ ha, h2, h3, h4, h5, h6, h7, h8, h9, h10, hj, hq, hk };
	vector<card> spadesArray{ sa, s2, s3, s4, s5, s6, s7, s8, s9, s10, sj, sq, sk };



	//Gonna add one to allcards to see if that fixes push_back
   /* allCards->push_back(ca);
	clubsArray.erase(clubsArray.begin());*/


	//Hold on apparently there's a random shuffle for vectors
	std::srand(std::time(0));	//For some reason shuffle doesn't work when you restart the program, it uses the previously shuffled version... this line solves that.Needs <ctime> included 
	std::random_shuffle(clubsArray.begin(), clubsArray.end());
	std::random_shuffle(diamondsArray.begin(), diamondsArray.end());
	std::random_shuffle(heartsArray.begin(), heartsArray.end());
	std::random_shuffle(spadesArray.begin(), spadesArray.end());




	//Add shuffled clubs to allCards
	for (auto &c : clubsArray)
	{
		//allCards->push_back(clubsArray);
		allCards.push_back(c);
	}

	//Add shuffled diamonds to allCards
	for (auto &c : diamondsArray)
	{
		allCards.push_back(c);
	}

	//Add shuffled hearts to allCards
	for (auto &c : heartsArray)
	{
		allCards.push_back(c);
	}

	//Add shuffled spades to allCards
	for (auto &c : spadesArray)
	{
		allCards.push_back(c);
	}

	//Shuffle allCards (give it a right good shuffle!)
	std::random_shuffle(allCards.begin(), allCards.end());
	std::random_shuffle(allCards.begin(), allCards.end());
	std::random_shuffle(allCards.begin(), allCards.end());
	std::random_shuffle(allCards.begin(), allCards.end());
	std::random_shuffle(allCards.begin(), allCards.end());



	//Testing that all 52 cards are in the vector array
   /* cout << allCards.size() << endl;

	for (int i = 0; i < allCards.size(); i++)
	{
		cout << i << endl;
	}*/


	//For all cards in allCards, shout out the suit (testing that populating and shuffling works)
	//For some reason both this and the [i] method are getting a first result but then crashing the program
	identify_cards(allCards);

	//It's important that we don't get allCards and cardStack mixed up.
	//A reference to all cards is now pushed back onto the card stack.
	for (auto &c : allCards)
	{
		cardStack.push_back(c);
	}


	//Now that the pack is shuffled, it's time to deal some cards!
	//But first, we need some players to deal to!
	//player Ryan;		Ryan.name = "Ryan";
	//player Nick;		Nick.name = "Nick";
	//player Blair;		Blair.name = "Blair";
	//player Declan;	Declan.name = "Decy";
	//

	//Let's add them to a vector array now - ///note that it's of pointers/references
	vector<player> PlayerList;

	int AmountOfPlayers;
	string PlayerName;

	cout << "How many players do you want in the game? (2-4)" << endl;
	cin >> AmountOfPlayers;
	cout << endl;

	for (int i = 0; i < AmountOfPlayers; i++)
	{
		cout << "Enter a player name:" << endl;
		cin >> PlayerName;
		cout << endl;

		player newPlayer;
		newPlayer.name = PlayerName;

		PlayerList.push_back(newPlayer);
	}


	//This is just hardcoded now, but we'll need to think of a strategy for
	//adding all of the players later, as I imagine we'll be letting the user
	//decide how many players there are, and what their names are.
	//They could just be created via a button or something and added directly to
	//the vector array I suppose.
	//PlayerList.push_back(Nick);
	//PlayerList.push_back(Blair);
	//PlayerList.push_back(Ryan);
	//PlayerList.push_back(Declan);
	//

	//We need to know how many cards each player is going to be dealt.
	//This could be something we let the user decide...
	//But for now let's make it 7.
	int CardsPerPlayer = 7;

	//Let's deal!
	//We need a nested for loop here so that the outside loop deals 7 times
	//but the inside loop makes sure that it doesn't just deal 7 cards to each player
	//sequentially. Cards should be dealt 1 by 1 around the table until everyone has 
	//[CardsPerPlayer] cards.
	//The inner loop decides who is recieving the next card.
	for (int i = 0; i < CardsPerPlayer; i++)
	{
		for (int j = 0; j < PlayerList.size(); j++)
		{
			PlayerList[j].hand.push_back(cardStack[0]);			//////////////////////////////////////////////////////////////////PROBLEMMMMMMMM
			cardStack.erase(cardStack.begin());
		}
	}

	//Hacky solution to the problem
	//Think playerlist is creating a copy of each player, but I can't figure out
	//how to fix that. So for now we'll just hack our way around it
	//Ryan.update_hand(PlayerList[0].hand);
	//Nick.update_hand(PlayerList[1].hand);
	//Blair.update_hand(PlayerList[2].hand);
	//Declan.update_hand(PlayerList[3].hand);
	//


	//I'm not confident about the * notation so let's get some tests done here
	cout << endl;

	//cout << "Ryan has " << Ryan.hand.size() << " cards." << endl;
	//cout << "Nick has " << Nick.hand.size() << " cards." << endl;
	//cout << "Blair has " << Blair.hand.size() << " cards." << endl;
	//cout << "Declan has " << Declan.hand.size() << " cards." << endl;
	//
	cout << endl;

	cout << "allCards.size() = " << allCards.size() << endl;
	cout << "cardStack.size() = " << cardStack.size() << endl;

	cout << endl;

	cout << "If that worked, each player should have 7 cards." << endl << "allCards should still have 52 cards, and cardstack should have "
		<< 52 - (PlayerList.size() * CardsPerPlayer) << endl << endl;


	//At the point of writing this we're using a hacky get-around for the PlayerList creating copies of players
	//..actually I think I'm just goonna stick with using them straight from PlayerList cause that way
	//have their own names assigned by the user anyway


	//Random thought, we're gonna need a bool or something to say whether the play is going left or right 


	//Right let's turn the top (or bottom in our case) card over and see what we're playing on				--Wait who dealt? We should point that out
	lastCard.push_back(cardStack[0]);
	cardStack.erase(cardStack.begin());

	cout << "The cards have been dealt and our first card to be played on is" << endl;
	identify_cards(lastCard);

	cout << PlayerList[0].name << " will start." << endl;
	cout << PlayerList[0].name << ", do you have any cards that match either in suit or in type?" << endl << endl;

	//Display PlayerList[0]'s hand
	cout << PlayerList[0].name << "'s hand:" << endl;
	identify_cards(PlayerList[0].hand);

	//Function to check whether PlayerList[0] can play
	PlayerList[0].canPlay = can_play_checker(lastCard[0], PlayerList[0].hand);

	if (PlayerList[0].canPlay == false)
	{
		cout << PlayerList[0].name << " has to take a card from the deck." << endl << endl;

		PlayerList[0].hand.push_back(cardStack[0]);			//////////////////////////////////////////////////////////////////PROBLEMMMMMMMM
		cardStack.erase(cardStack.begin());
	}

	if (PlayerList[0].canPlay == true)
	{
		cout << PlayerList[0].name << " can play." << endl << endl;
	}







	//Ranking for when players get out
	vector<player> ranking;

	for (int i = 0; i < PlayerList.size(); i++)
	{
		if (PlayerList[i].hand.empty())
		{
			ranking.push_back(PlayerList[i]);
			PlayerList.erase(PlayerList.begin() + i); 
		}
	}


	/*if (player gets out) [pseudocode]
	{
		ranking.push_back(player);
	}*/

	return 0;
}