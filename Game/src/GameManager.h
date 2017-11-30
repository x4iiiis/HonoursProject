#pragma once

#include <vector>
#include <iostream>


#include "player.h"
#include "Deck.h"


class GameManager
{
public:
	enum GameDirection { Clockwise, AntiClockwise };
private:

	static GameManager *instance;

	GameManager() {}

	/////////////////////////////

	int NumberOfPlayers;
	int CardsPerPlayer;

	vector<shared_ptr<player>> ListOfPlayers;

	//enum GameDirection { Clockwise, AntiClockwise };
	GameDirection DirectionOfPlay = GameDirection::Clockwise;

	//Player who played the most recent card
	shared_ptr<player> LastCardPlayer;

	//Will be a part of ListOfPlayers (aka []) and will be set dependant on direction 
	shared_ptr<player> CurrentPlayer;

	//whose turn is it?
	//Maybe players could have a bool IsItMyTurn that we set either here or somewhere else

	//Oh just had a random thought and putting it here
	//In our game loop, we can have 2 different if statements that's like
	//If direction = clockwise, turn ++
	//if direction = anticlockwise, turn --
	//Or maybe it'll just be part of a function I dunno


	//Something to check if last card was played by previous player
	//Maybe have a function that is called every time a card is played that passes the player that played it...
	//Then, at the beginning of every turn, call another function that checks who played the last card.
	//If their index in the vector is more than 1 (or -1?) of a difference then it doesn't effect you
	//Maybe only need to check it if a special card is the last card?

public:

static GameManager *Manager()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}

	return instance;
}



Deck DeckOfCards;


void PlayerCreation()
{
	string PlayerName;

	cout << "How many players do you want in the game? (2-4)" << endl;		//--This will need validation to ensure it's between 2 and 4 later, useful to put 1 for testing the now though
	cin >> NumberOfPlayers;
	cout << endl;

	for (int i = 0; i < NumberOfPlayers; i++)
	{
		cout << "Enter a player name:" << endl;
		cin >> PlayerName;
		cout << endl;

		player newPlayer;
		newPlayer.name = PlayerName;
		ListOfPlayers.push_back(make_shared<player>(newPlayer));
	}
}


void SetNumberOfPlayers(int NumPlayers)
{
	NumberOfPlayers = NumPlayers;
}

int GetNumberOfPlayers()
{
	return NumberOfPlayers;
}

//Think I've already done this with PlayerCreation()?
void AddPlayer(shared_ptr<player> NewPlayer)
{
	ListOfPlayers.push_back(NewPlayer);
}

vector<shared_ptr<player>> GetListOfPlayers()
{
	return ListOfPlayers;
}


void SetCardsPerPlayer(int NumCards)
{
	CardsPerPlayer = NumCards;
}

int GetCardsPerPlayer()
{
	return CardsPerPlayer;
}

shared_ptr<player>GetCurrentPlayer()
{
	return CurrentPlayer;
}

void NextPlayer()
{
	if (DirectionOfPlay == GameDirection::Clockwise)
	{

		if (CurrentPlayer == ListOfPlayers[ListOfPlayers.size()])
		{
			CurrentPlayer = ListOfPlayers[0];
		}
		else
		{
			//Stolen from https://stackoverflow.com/questions/15099707/how-to-get-position-of-a-certain-element-in-strings-vector-to-use-it-as-an-inde
			ptrdiff_t pos = find(ListOfPlayers.begin(), ListOfPlayers.end(), CurrentPlayer) - ListOfPlayers.begin();
			//auto curr = find(ListOfPlayers.begin(), ListOfPlayers.end(), CurrentPlayer);

			if (pos < ListOfPlayers.size())
			{
				CurrentPlayer = ListOfPlayers[pos + 1];
			}
		}
	}
	else if (DirectionOfPlay == GameDirection::AntiClockwise)
	{
		if (CurrentPlayer == ListOfPlayers[0])
		{
			CurrentPlayer = ListOfPlayers[ListOfPlayers.size()];
		}
		else
		{
			//Stolen from https://stackoverflow.com/questions/15099707/how-to-get-position-of-a-certain-element-in-strings-vector-to-use-it-as-an-inde
			ptrdiff_t pos = find(ListOfPlayers.begin(), ListOfPlayers.end(), CurrentPlayer) - ListOfPlayers.begin();
			//auto curr = find(ListOfPlayers.begin(), ListOfPlayers.end(), CurrentPlayer);

			if (pos < ListOfPlayers.size())
			{
				CurrentPlayer = ListOfPlayers[pos - 1];
			}
		}
	}
}

//Don't think you can return enums so I'm passing strings
auto getDirectionOfPlay()
{
	return DirectionOfPlay;
	
	//if (DirectionOfPlay == GameDirection::Clockwise)
	//{
	//	return Direction
	//	//return "Clockwise";
	//}
	//return "Anti-Clockwise";
}

	void ChangeDirectionOfPlay()
	{
		if (DirectionOfPlay == GameDirection::Clockwise)
		{
			DirectionOfPlay = GameDirection::AntiClockwise;
		}
		else
		{
			DirectionOfPlay = GameDirection::Clockwise;
		}
	}

	//Will probably be used as a pass into the next function...
	shared_ptr<player>WhoPlayedTheLastCard()
	{
		return LastCardPlayer;
	}

	bool DoesLastCardAffectCurrentPlayer(shared_ptr<player> LastCardPlayer, shared_ptr<player> CurrentPlayer)
	{
		int LCP = 0;
		int CP = 0;

		//Find index of current player and the last player to play a card
		for (int i = 0; i < ListOfPlayers.size(); i++)
		{
			if (ListOfPlayers[i] == LastCardPlayer)
			{
				LCP = i;
			}

			if (ListOfPlayers[i] == CurrentPlayer)
			{
				CP = i;
			}
		}

		//Using the indexes to determine whether or not the card was played by the previous player
		//Not sure if all of this logic is right yet tbh
		if (LCP = (CP - 1) || (LCP = (CP + 1)))
		{
			cout << "Last played card DOES affect current player" << endl << endl;
			return true;
		}


		if ((LCP = (NumberOfPlayers - 1)) && (CP = 0) && (DirectionOfPlay == GameDirection::Clockwise))
		{
			cout << "Last played card DOES affect current player" << endl << endl;
			return true;
		}

		if ((LCP = 0) && (CP = (NumberOfPlayers - 1)) && (DirectionOfPlay == GameDirection::AntiClockwise))
		{
			cout << "Last played card DOES affect current player" << endl << endl;
			return true;
		}
		cout << "Current Player not affected by last played card" << endl << endl;
		return false;
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















	//Rules
	void ConsultRules(vector<shared_ptr<card>> lastCard, vector<shared_ptr<player>> PlayerList, vector<shared_ptr<card>> cardStack)
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
				DeckOfCards.identify_cards(PlayerList[0]->hand);
				//GameManager::Manager()->DeckOfCards.identify_cards(PlayerList[0]->hand);
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
			DeckOfCards.identify_cards(PlayerList[0]->hand);
			//GameManager::Manager()->DeckOfCards.identify_cards(PlayerList[0]->hand);

			break;
		}
		//Game management - we need the direction of play to be defined somewhere
		case(card::type::Jack):
		{
			cout << "The last card was a jack!" << endl;
			ChangeDirectionOfPlay();
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
};

//Turns out this is SUPER important for the singleton to work
GameManager *GameManager::instance = NULL;