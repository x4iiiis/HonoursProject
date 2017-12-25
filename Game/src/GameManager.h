#pragma once

#include <vector>
#include <iostream>
#include <string>


#include "player.h"
#include "Deck.h"
#include "Ranking.h"

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
Ranking Scoreboard;


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

vector<shared_ptr<player>> GetListOfPlayers()
{
	return ListOfPlayers;
}

void setFirstPlayer()
{
	CurrentPlayer = ListOfPlayers[0];
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
		//Set the previous (current before this method is complete) player's myTurn boolean to false
		CurrentPlayer->myTurn = false;

		if (CurrentPlayer == ListOfPlayers[ListOfPlayers.size()-1])
		{
			CurrentPlayer = ListOfPlayers[0];
			CurrentPlayer->myTurn = true;
		}
		else if (CurrentPlayer == ListOfPlayers[0])
		{
			CurrentPlayer = ListOfPlayers[1];
			CurrentPlayer->myTurn = true;
		}
		else if (CurrentPlayer == ListOfPlayers[1] && ListOfPlayers.size() > 2)
		{
			CurrentPlayer = ListOfPlayers[2];
			CurrentPlayer->myTurn = true;
		}
		else if (CurrentPlayer == ListOfPlayers[2] && ListOfPlayers.size() > 3)
		{
			CurrentPlayer = ListOfPlayers[3];
			CurrentPlayer->myTurn = true;
		}
	}
	else if (DirectionOfPlay == GameDirection::AntiClockwise)
	{
		if (CurrentPlayer == ListOfPlayers[0])
		{
			CurrentPlayer = ListOfPlayers[ListOfPlayers.size()-1];
			CurrentPlayer->myTurn = true;
		}
		else if (CurrentPlayer == ListOfPlayers[1])
		{
			CurrentPlayer = ListOfPlayers[0];
			CurrentPlayer->myTurn = true;
		}
		else if (CurrentPlayer == ListOfPlayers[2])
		{
			CurrentPlayer = ListOfPlayers[1];
			CurrentPlayer->myTurn = true;
		}
		else if (CurrentPlayer == ListOfPlayers[3])
		{
			CurrentPlayer = ListOfPlayers[2];
			CurrentPlayer->myTurn = true;
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

	//Fuck all in here atm bruh
	void play(shared_ptr<card> c, vector<shared_ptr<card>> Hand)
	{
		if (card_is_playable(c))
		{
			DeckOfCards.lastCard.push_back(c);
			DeckOfCards.cardStack.push_back(DeckOfCards.lastCard[0]);
			DeckOfCards.lastCard.erase(DeckOfCards.lastCard.begin());

			cout << GetCurrentPlayer()->name << " played the ";
			DeckOfCards.identify_card(c);
			cout << endl << endl;

			CurrentPlayer->canPlay = false;
			CurrentPlayer->canPickUp = false;

			for (int i = 0; i < Hand.size(); i++)
			{
				if (cards_match(Hand[i], c))
				{
					Hand.erase(Hand.begin() + i);
					NextPlayer();
					//DeckOfCards.UpdatePositionsAndTextures(GetCurrentPlayer()->hand);
					ConsultRules();
					break;
				}
			}

			//Check if any hands are empty (can only possibly be the previous player that's hand has changed since last move), remove the player from the list
			for (int i = 0; i < ListOfPlayers.size(); i++)
			{
				if (ListOfPlayers[i]->hand.empty())
				{
					GameManager::Manager()->Scoreboard.PlayerIsOut(ListOfPlayers[i]);
					ListOfPlayers.erase(ListOfPlayers.begin() + i);
				}
			}
		}
		else
		{
			cout << "You cannot play this card." << endl << "The ";
			DeckOfCards.identify_card(c);
			cout << " cannot be played on top of the ";
			DeckOfCards.identify_cards(DeckOfCards.lastCard);
			cout << "." << endl << endl;

		}
	}
	

	bool can_play_checker(vector<shared_ptr<card>> hand)
	{
		for (auto c : hand)
		{
			if (c->cardSuit == DeckOfCards.lastCard[0]->cardSuit)
			{
				//cout << "Suit match!" << endl;
				CurrentPlayer->canPlay = true;
				CurrentPlayer->canPickUp = false;
				return true;
			}

			if (c->cardType == DeckOfCards.lastCard[0]->cardType)
			{
				//cout << "Type match!" << endl;
				CurrentPlayer->canPlay = true;
				CurrentPlayer->canPickUp = false;
				return true;
			}
		}
		//If the code makes it this far, then it hasn't found any
		//Matches in type or suit throughout the whole hand, so
		//we return false.
		//cout << "No matches!" << endl;
		CurrentPlayer->canPlay = false;
		CurrentPlayer->canPickUp = true;
		return false;
	}


	bool card_is_playable(shared_ptr<card> c)
	{
		if (c->cardSuit == DeckOfCards.lastCard[0]->cardSuit)
		{
			return true;
		}
		else if (c->cardType == DeckOfCards.lastCard[0]->cardType)
		{
			return true;
		}
		return false;
	}


	bool cards_match(shared_ptr<card> c1, shared_ptr<card> c2)
	{
		if ((c1->cardSuit == c2->cardSuit) && c1->cardType == c2->cardType)
		{
			return true;
		}
		return false;
	}













	//Rules
	void ConsultRules()
	{

		//By default, assume player can play and can't pick up.
		//If this isn't the case, the following code will sort that out.
		GetCurrentPlayer()->canPickUp = false;
		GetCurrentPlayer()->canPlay = true;


		switch (DeckOfCards.lastCard[0]->cardType)
		{
			//Need to be able to tell who played it, otherwise that black queen is gonna make everyone pick up 5 until we run out of cards
			//Also it isn't PlayerList[0], it'll be whoever's turn it is once we've got that figured out
			case(card::type::Queen):
			{
				if (DeckOfCards.lastCard[0]->cardColour == card::colour::Black)
				{
					cout << "The last card was a black queen!" << endl;
					cout << "You must now pick up 5 cards." << endl << endl;

					GetCurrentPlayer()->canPickUp = true;
					GetCurrentPlayer()->canPlay = false;

					for (int i = 0; i < 5; i++)
					{
						GetCurrentPlayer()->hand.push_back(DeckOfCards.cardStack[0]);
						DeckOfCards.cardStack.erase(DeckOfCards.cardStack.begin());
					}
					//DeckOfCards.UpdatePositionsAndTextures(GetCurrentPlayer()->hand);

					//Display updated hand
					cout << GetCurrentPlayer()->name << "'s updated hand:" << endl;
					DeckOfCards.identify_cards(GetCurrentPlayer()->hand);

					GetCurrentPlayer()->canPickUp = false;
					GetCurrentPlayer()->canPlay = false;

					NextPlayer();
					can_play_checker(GetCurrentPlayer()->hand);
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

				GetCurrentPlayer()->canPickUp = true;
				GetCurrentPlayer()->canPlay = false;

				for (int i = 0; i < 2; i++)
				{
					GetCurrentPlayer()->hand.push_back(DeckOfCards.cardStack[0]);
					DeckOfCards.cardStack.erase(DeckOfCards.cardStack.begin());
				}
				//DeckOfCards.UpdatePositionsAndTextures(GetCurrentPlayer()->hand);


				//Display PlayerList[0]'s updated hand
				cout << GetCurrentPlayer()->name << "'s updated hand:" << endl;
				DeckOfCards.identify_cards(GetCurrentPlayer()->hand);
				//GameManager::Manager()->DeckOfCards.identify_cards(PlayerList[0]->hand);

				GetCurrentPlayer()->canPickUp = false;
				GetCurrentPlayer()->canPlay = false;

				NextPlayer();
				can_play_checker(GetCurrentPlayer()->hand);
				break;
			}
			//Game management - we need the direction of play to be defined somewhere
			case(card::type::Jack):
			{
				cout << "The last card was a jack!" << endl;
				ChangeDirectionOfPlay();

				GetCurrentPlayer()->canPickUp = false;
				GetCurrentPlayer()->canPlay = false;

				NextPlayer();
				NextPlayer();
				cout << "The direction of play has been reversed." << endl << endl;
				cout << GetCurrentPlayer()->name << ", it's your turn." << endl << endl;

				can_play_checker(GetCurrentPlayer()->hand);
				break;
			}
			//Again, needing game management to know whose turn it is and when the card was played, otherwise
			//everybody's gonna skip their turn forever
			case(card::type::Eight):
			{
				cout << "The last card was an eight!" << endl;
				cout << "You are forced to skip your turn." << endl << endl;

				GetCurrentPlayer()->canPickUp = false;
				GetCurrentPlayer()->canPlay = false;

				NextPlayer();
				cout <<  GetCurrentPlayer()->name << ", it's your turn." << endl << endl;
				
				can_play_checker(GetCurrentPlayer()->hand);
			}

			default:
			{
				can_play_checker(GetCurrentPlayer()->hand);
				break;
			}
		}
		DeckOfCards.UpdatePositionsAndTextures(GetCurrentPlayer()->hand);
	}
};

//Turns out this is SUPER important for the singleton to work
GameManager *GameManager::instance = NULL;