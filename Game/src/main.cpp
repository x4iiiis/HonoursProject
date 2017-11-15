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

#include <memory>

using namespace std;

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

bool can_play_checker(shared_ptr<card> lastCard, vector<shared_ptr<card>> hand)
{
	for (auto c : hand)
	{
		if (c->cardSuit == lastCard->cardSuit)
		{
			cout << "Suit match!" << endl;
			return true;
		}

		if (c->cardType == lastCard->cardType)
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


void consultRules(vector<shared_ptr<card>> lastCard, vector<shared_ptr<player>> PlayerList, vector<shared_ptr<card>> cardStack)
{
	switch (lastCard[0]->cardType)
	{
		//Need to be able to tell who played it, otherwise that black queen is gonna make everyone pick up 5 until we run out of cards
		//Also it isn't PlayerList[0], it'll be whoever's turn it is once we've got that figured out
	case(card::type::Queen):
	{
		if (lastCard[0]->cardColour == card::colour::Black)
		{
			cout << "The last card was a black queen!" << endl;
			cout << "You must now pick up 5 cards." << endl << endl;

			for (int i = 0; i < 5; i++)
			{
				PlayerList[0]->hand.push_back(cardStack[0]);
				cardStack.erase(cardStack.begin());
			}
			//Display PlayerList[0]'s updated hand
			cout << PlayerList[0]->name << "'s updated hand:" << endl;
			identify_cards(PlayerList[0]->hand);
		}
		break;
	}
	//Need to be able to tell who played it, otherwise that 2 is gonna make everyone pick up 2 until we run out of cards
	//Also it isn't PlayerList[0], it'll be whoever's turn it is once we've got that figured out
	case(card::type::Two):
	{
		cout << "The last card was a two!" << endl;
		cout << "You must now pick 2 cards." << endl << endl;

		for (int i = 0; i < 2; i++)
		{
			PlayerList[0]->hand.push_back(cardStack[0]);
			cardStack.erase(cardStack.begin());
		}

		//Display PlayerList[0]'s updated hand
		cout << PlayerList[0]->name << "'s updated hand:" << endl;
		identify_cards(PlayerList[0]->hand);

		break;
	}
	//Game management - we need the direction of play to be defined somewhere
	case(card::type::Jack):
	{
		cout << "The last card was a jack!" << endl;
		cout << "The direction of play has been reversed." << endl << endl;
		cout << "*Previous Player*, it's your turn." << endl << endl;

		break;
	}
	//Again, needing game management to know whose turn it is and when the card was played, otherwise
	//everybody's gonna skip their turn forever
	case(card::type::Eight):
	{
		cout << "The last card was an eight!" << endl;
		cout << "You are forced to skip your turn." << endl << endl;

		cout << "*Next player*, it's your turn." << endl << endl;
	}

	default:
	{
		break;
	}
	}
}


int main()
{
	//52 cards, first index = 0
	vector<shared_ptr<card>> allCards;		//All of the cards in the pack
	vector<shared_ptr<card>> cardStack;		//Cards available to be picked up 
	vector<shared_ptr<card>> lastCard;		//Card we're going to play on top of


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
	for (auto c : allCards)
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

	//Let's add them to a vector array now								--note that it's of shared pointers
	vector<shared_ptr<player>> PlayerList;

	int AmountOfPlayers;
	string PlayerName;

	cout << "How many players do you want in the game? (2-4)" << endl;		//--This will need validation to ensure it's between 2 and 4 later, useful to put 1 for testing the now though
	cin >> AmountOfPlayers;
	cout << endl;

	for (int i = 0; i < AmountOfPlayers; i++)
	{
		cout << "Enter a player name:" << endl;
		cin >> PlayerName;
		cout << endl;

		player newPlayer;
		newPlayer.name = PlayerName;
		PlayerList.push_back(make_shared<player>(newPlayer));
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
			PlayerList[j]->hand.push_back(cardStack[0]);			//////////////////////////////////////////////////////////////////PROBLEMMMMMMMM
			cardStack.erase(cardStack.begin());
		}
	}


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
	cout << "which is " << checkColour(lastCard[0]) << endl;

	cout << PlayerList[0]->name << " will start." << endl;
	cout << PlayerList[0]->name << ", do you have any cards that match either in suit or in type?" << endl << endl;

	//Display PlayerList[0]'s hand
	cout << PlayerList[0]->name << "'s hand:" << endl;
	identify_cards(PlayerList[0]->hand);

	//Function to check whether PlayerList[0] can play
	PlayerList[0]->canPlay = can_play_checker(lastCard[0], PlayerList[0]->hand);

	//if (PlayerList[0]->canPlay == false)
	//{
	//	cout << PlayerList[0]->name << " has to take a card from the deck." << endl << endl;
	//
	//	PlayerList[0]->hand.push_back(cardStack[0]);			//////////////////////////////////////////////////////////////////PROBLEMMMMMMMM
	//	cardStack.erase(cardStack.begin());
	//
	//	//Display PlayerList[0]'s updated hand
	//	cout << PlayerList[0]->name << "'s updated hand:" << endl;
	//	identify_cards(PlayerList[0]->hand);
	//}

	if (PlayerList[0]->canPlay == true)
	{
		cout << PlayerList[0]->name << " can play." << endl << endl;
	}



	//Every time a card is played, call:
	consultRules(lastCard, PlayerList, cardStack);
	//This checks the last card against the rules relating to certain cards
	//At the moment, a black queen forces 5 cards, a two forces 2, and
	//eight and jack are there but just produce cout statements at this point.

	





	//Ranking for when players get out
	vector<shared_ptr<player>> ranking;

	for (int i = 0; i < PlayerList.size(); i++)
	{
		if (PlayerList[i]->hand.empty())
		{
			ranking.push_back(PlayerList[i]);
			PlayerList.erase(PlayerList.begin() + i); 
			i--;
		}

		//Thinking this will put last place in but only when real placers have got out
		if (PlayerList.size() == 1)
		{
			ranking.push_back(PlayerList[0]);
			PlayerList.erase(PlayerList.begin());
		}
	}



	//If everyone has placed (obviously last place doesn't get out 
	//and automatically places), display rankings!
	if (ranking.size() == AmountOfPlayers)
	{
		cout << "Ranking:" << endl;

		for (int i = 0; i < ranking.size(); i++)
		{
			cout << i+1 << ": " << ranking[i]->name << endl;
		}
		cout << endl;
	}


	/*if (player gets out) [pseudocode]
	{
		ranking.push_back(player);
	}*/

	return 0;
}


//Simon's comments:
//Rules like forcing to play a certain card could be difficult to implement,
//so start with just the black queen and jack rules for now and potentially
//add others later if things are going well

//Thing what he meant by that was forcing it to pick up will be okay but forcing
//certain cards maybe not. Perhaps pickup would have to be something we
//do automatically, skipping out the agent's turn. 
//Realistically this is probably something we should do anyway as it would be 
//pointless to give it a turn when it can't play anything. 
//Could also implement 8 or wait (without the 8) and just force the wait


//Need to work out a game manager or a way to decide whose turn it is 
//and what direction the play is going in.
//Also going to need something to tell us whether or not something has just been played
//For example, if someone plays a black queen, the next player has to pick up 5
//(unless they have a red queen but probably leaving that rule out for now)
//but the person after that doesn't have to pick up five, despite the last played
//card being a black queen. 

//Might be unwise but constant check to see if last card is a rule-bearing card?
//Switch Case statements maybe? 


//Check/define colours isn't working because we're not referencing cards... :( 

//shared_ptr sounds a shout 
//Indeed they were!