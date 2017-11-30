#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include <istream>
#include <random> 
/////////////////////////////
//#include "card.h"
//#include "player.h"
#include "GameManager.h"
//#include "Rules.h"
//#include "Deck.h"
#include <vector>
#include <ctime>

#include <memory>

using namespace std;

int main()
{
	//shared_ptr<GameManager> GM;
	//make_shared<GameManager>(GM);

	//GameManager *GM = GameManager::Manager();

	GameManager::Manager()->PlayerCreation();
	GameManager::Manager()->setFirstPlayer();
	GameManager::Manager()->DeckOfCards.SetUpDeck();
	//GameManager::Manager()->DeckOfCards.Deal(GameManager::Manager()->GetListOfPlayers(), GameManager::Manager()->GetCardsPerPlayer());


	//Gonna add one to allcards to see if that fixes push_back
	/* allCards->push_back(ca);
	clubsArray.erase(clubsArray.begin());*/



	//Testing that all 52 cards are in the vector array
	/* cout << allCards.size() << endl;

	for (int i = 0; i < allCards.size(); i++)
	{
	cout << i << endl;
	}*/


	//For all cards in allCards, shout out the suit (testing that populating and shuffling works)
	//For some reason both this and the [i] method are getting a first result but then crashing the program
	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->DeckOfCards.allCards);

	//It's important that we don't get allCards and cardStack mixed up.
	//A reference to all cards is now pushed back onto the card stack.



	//Now that the pack is shuffled, it's time to deal some cards!
	//But first, we need some players to deal to!
	//player Ryan;		Ryan.name = "Ryan";
	//player Nick;		Nick.name = "Nick";
	//player Blair;		Blair.name = "Blair";
	//player Declan;	Declan.name = "Decy";
	//

	//Let's add them to a vector array now								--note that it's of shared pointers
	//vector<shared_ptr<player>> PlayerList;




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
	//int CardsPerPlayer = 7;
	GameManager::Manager()->SetCardsPerPlayer(7);






	


	//testing next player works
	GameManager::Manager()->NextPlayer();
	cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	GameManager::Manager()->NextPlayer();
	cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	GameManager::Manager()->NextPlayer();
	cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	GameManager::Manager()->NextPlayer();
	cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	GameManager::Manager()->NextPlayer();
	cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	cout << endl;
	




	//Let's deal!
	//We need a nested for loop here so that the outside loop deals 7 times
	//but the inside loop makes sure that it doesn't just deal 7 cards to each player
	//sequentially. Cards should be dealt 1 by 1 around the table until everyone has 
	//[CardsPerPlayer] cards.
	//The inner loop decides who is recieving the next card.
	//GameManager::Manager()->DeckOfCards.Deal();
	GameManager::Manager()->DeckOfCards.Deal(GameManager::Manager()->GetListOfPlayers(), GameManager::Manager()->GetCardsPerPlayer());


	//I'm not confident about the * notation so let's get some tests done here
	cout << endl;

	//cout << "Ryan has " << Ryan.hand.size() << " cards." << endl;
	//cout << "Nick has " << Nick.hand.size() << " cards." << endl;
	//cout << "Blair has " << Blair.hand.size() << " cards." << endl;
	//cout << "Declan has " << Declan.hand.size() << " cards." << endl;
	//
	cout << endl;

	cout << "allCards.size() = " << GameManager::Manager()->DeckOfCards.allCards.size() << endl;
	cout << "cardStack.size() = " << GameManager::Manager()->DeckOfCards.cardStack.size() << endl;

	cout << endl;

	cout << "If that worked, each player should have 7 cards." << endl << "allCards should still have 52 cards, and cardstack should have "
		<< 52 - (GameManager::Manager()->GetListOfPlayers().size() * GameManager::Manager()->GetCardsPerPlayer()) << endl << endl;


	//At the point of writing this we're using a hacky get-around for the PlayerList creating copies of players
	//..actually I think I'm just goonna stick with using them straight from PlayerList cause that way
	//have their own names assigned by the user anyway


	//Random thought, we're gonna need a bool or something to say whether the play is going left or right 


	//Right let's turn the top (or bottom in our case) card over and see what we're playing on				--Wait who dealt? We should point that out
	GameManager::Manager()->DeckOfCards.lastCard.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
	GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());

	cout << "The cards have been dealt and our first card to be played on is" << endl;
//****************************************************************************************************************************************************************************************
//1337haxx to make it a jack
	GameManager::Manager()->DeckOfCards.lastCard[0]->PickYourOwnLastCard(card::type::Jack, card::suit::Clubs);
//*****************************************************************************************************************************************************************************************

	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->DeckOfCards.lastCard);
	cout << "which is " << GameManager::Manager()->DeckOfCards.checkColour(GameManager::Manager()->DeckOfCards.lastCard[0]) << endl;

	cout << GameManager::Manager()->GetCurrentPlayer()->name << " will start." << endl;
	cout << GameManager::Manager()->GetCurrentPlayer()->name << ", do you have any cards that match either in suit or in type?" << endl << endl;

	//Display PlayerList[0]'s hand
	cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s hand:" << endl;
	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

	//Function to check whether PlayerList[0] can play
	GameManager::Manager()->GetCurrentPlayer()->canPlay = GameManager::Manager()->can_play_checker(GameManager::Manager()->DeckOfCards.lastCard[0], GameManager::Manager()->GetCurrentPlayer()->hand);

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

	if (GameManager::Manager()->GetListOfPlayers()[0]->canPlay == true)
	{
		cout << GameManager::Manager()->GetListOfPlayers()[0]->name << " can play." << endl << endl;
	}



	//Every time a card is played, call:
	if (GameManager::Manager()->DoesLastCardAffectCurrentPlayer(GameManager::Manager()->WhoPlayedTheLastCard(), GameManager::Manager()->GetCurrentPlayer()) == true)
	{
		GameManager::Manager()->ConsultRules(GameManager::Manager()->DeckOfCards.lastCard, GameManager::Manager()->GetListOfPlayers(), GameManager::Manager()->DeckOfCards.cardStack);
	}
	//This checks the last card against the rules relating to certain cards
	//At the moment, a black queen forces 5 cards, a two forces 2, and
	//eight and jack are there but just produce cout statements at this point.







	//Ranking for when players get out
	vector<shared_ptr<player>> ranking;

	for (int i = 0; i < GameManager::Manager()->GetListOfPlayers().size(); i++)
	{
		if (GameManager::Manager()->GetListOfPlayers()[i]->hand.empty())
		{
			ranking.push_back(GameManager::Manager()->GetListOfPlayers()[i]);
			GameManager::Manager()->GetListOfPlayers().erase(GameManager::Manager()->GetListOfPlayers().begin() + i);
			i--;
		}

		//Thinking this will put last place in but only when real placers have got out
		if (GameManager::Manager()->GetListOfPlayers().size() == 1)
		{
			ranking.push_back(GameManager::Manager()->GetListOfPlayers()[0]);
			GameManager::Manager()->GetListOfPlayers().erase(GameManager::Manager()->GetListOfPlayers().begin());
		}
	}



	//If everyone has placed (obviously last place doesn't get out 
	//and automatically places), display rankings!
	if (ranking.size() == GameManager::Manager()->GetNumberOfPlayers())
	{
		cout << "Ranking:" << endl;

		for (int i = 0; i < ranking.size(); i++)
		{
			cout << i + 1 << ": " << ranking[i]->name << endl;
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