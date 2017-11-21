#pragma once

#include <vector>
#include <iostream>


#include "player.h"
#include "Deck.h"
#include "Rules.h"


class GameManager
{
private:

	static GameManager *instance;

	GameManager() {}

	/////////////////////////////

	int NumberOfPlayers;
	int CardsPerPlayer;

	vector<shared_ptr<player>> ListOfPlayers;

	enum GameDirection { Clockwise, AntiClockwise };
	GameDirection DirectionOfPlay;

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
	Rules Rulebook;


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
		//Move Current Player to be a pointer to the next ListOfPlayers[]
		if (CurrentPlayer == ListOfPlayers[ListOfPlayers.size()])
		{
			CurrentPlayer = ListOfPlayers[0];
		}

		else if (CurrentPlayer == ListOfPlayers[0])
		{
			CurrentPlayer = ListOfPlayers[1];
		}

		else if (CurrentPlayer == ListOfPlayers[1])
		{
			CurrentPlayer = ListOfPlayers[2];
		}

		else if (CurrentPlayer == ListOfPlayers[2])
		{
			CurrentPlayer = ListOfPlayers[3];
		}
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

};

//Turns out this is SUPER important for the singleton to work
GameManager *GameManager::instance = NULL;