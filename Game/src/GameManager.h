#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "player.h"
#include "Deck.h"
#include "Ranking.h"

class GameManager
{
public:
	enum GameDirection { Clockwise, AntiClockwise };
private:
	//Game Manager is a singleton 
	static GameManager *instance;
	GameManager() {}

	int NumberOfPlayers;
	int CardsPerPlayer;

	int MatchCounter = 0;

	vector<shared_ptr<player>> ListOfPlayers;
	vector<shared_ptr<player>> BackupListOfPlayers;

	//Game initially flows clockwise (left of the dealer!)
	GameDirection DirectionOfPlay = GameDirection::Clockwise;

	//Player who played the most recent card
	shared_ptr<player> LastCardPlayer;

	//Player taking the current turn
	shared_ptr<player> CurrentPlayer; 

public:
	//Game Manager is a singleton
	static GameManager *Manager()
	{
		if (instance == NULL)
		{
			instance = new GameManager();
		}
		return instance;
	}

	//Creating instances of Scoreboard and Deck objects for the game manager
	Deck DeckOfCards;
	Ranking Scoreboard;


	//Creation of players
	void PlayerCreation()
	{
		string PlayerName;
	
		//Making sure Number of players is between 2 and 4
		while (!(NumberOfPlayers > 1 && NumberOfPlayers < 5))
		{
			cout << "How many players do you want in the game? (2-4)" << endl;
			cin >> NumberOfPlayers;
			cout << endl;
	
			//If non-numeric characters are input, ignore it and try again
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
			}
		}
	
		//Take in player names and create players with said names
		for (int i = 0; i < NumberOfPlayers; i++)
		{
			cout << "Enter a player name:" << endl;
	
			while (PlayerName == "")
			{
				getline(cin, PlayerName);
			}
			cout << endl;
	
			player newPlayer;
			newPlayer.name = PlayerName;
	
			ListOfPlayers.push_back(make_shared<player>(newPlayer));
			
			PlayerName = "";
		}
	
		//TEMP - setting playstyles
		ListOfPlayers[0]->playstyle = player::Playstyle::Aggressive;	//Change me back to Human
		ListOfPlayers[1]->playstyle = player::Playstyle::Aggressive;	//Change me back to Aggressive
	
		if(ListOfPlayers.size() > 2)
		{
			ListOfPlayers[2]->playstyle = player::Playstyle::Aggressive;	//Change me back to Unaggressive
			
			if(ListOfPlayers.size() > 3)
			{
			ListOfPlayers[3]->playstyle = player::Playstyle::Aggressive;	//Change me back to Random
			}
		}
	

		//Setup backup list of players for rematches
		for (auto &p : ListOfPlayers)
		{
			BackupListOfPlayers.push_back(p);
		}
	}

	void ClearListOfPlayers()
	{
		for (int i = 0; i < ListOfPlayers.size(); i++)
		{
			ListOfPlayers.erase(ListOfPlayers.begin());
		}
	}

	void RespawnPlayers()
	{
		for (auto &p : BackupListOfPlayers)
		{
			ListOfPlayers.push_back(p);

			//TEMP
			cout << p->name << " respawned." << endl;
		}

		cout << endl << endl << endl;
	}
	
	void NewMatch()
	{
		MatchCounter += 1;
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
		//if (Scoreboard.Gameover(GetNumberOfPlayers()))
		//{
		//	return;  //?? right thing to do? 
		//}
	
		if (DirectionOfPlay == GameDirection::Clockwise)
		{
			//Set the previous (current before this method is complete) player's myTurn boolean to false
			CurrentPlayer->myTurn = false;
	
			if (CurrentPlayer == ListOfPlayers[ListOfPlayers.size() - 1])
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
				CurrentPlayer = ListOfPlayers[ListOfPlayers.size() - 1];
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
	
		//Set canPlay and canPickUp to false by default, can_play_checker will sort it
		CurrentPlayer->canPlay = false;
		CurrentPlayer->canPickUp = false;
	
		//Trying to sort recursive rule enforcement
		DeckOfCards.lastCard[0]->turnsSincePlayed += 1;
	
		DeckOfCards.UpdatePositionsAndTextures(GetCurrentPlayer());
	
		if (Scoreboard.Gameover(GetNumberOfPlayers()))
		{
			Scoreboard.PlayerIsOut(GetCurrentPlayer(), GetNumberOfPlayers());
			return;
		}
	}
	
	
	
	//Returns the direction that play is flowing
	auto getDirectionOfPlay()
	{
		return DirectionOfPlay;
	}

	//Flips the direction of play when a jack is played
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

	void SetLastCardPlayer(shared_ptr<player> lcp)
	{
		LastCardPlayer = lcp;
	}

	bool DoesLastCardAffectCurrentPlayer()
	{
		//For keeping track of what happened each game
		fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
		if (!GameText.is_open())
		{
			cout << "Error opening GameRecords.txt" << endl << endl;
		}

		//printing whether the player is affected by cards that don't bare rules was annoying me 
		if ((DeckOfCards.lastCard[0]->cardType == card::type::Queen && DeckOfCards.lastCard[0]->cardColour == card::colour::Black)
			|| (DeckOfCards.lastCard[0]->cardType == card::type::Two)
			|| (DeckOfCards.lastCard[0]->cardType == card::type::Eight)
			|| (DeckOfCards.lastCard[0]->cardType == card::type::Eight))
		{
			//If the card was played more than 1 turn ago, then it doesn't even matter
			if (DeckOfCards.lastCard[0]->turnsSincePlayed != 1)
			{
				cout << GetCurrentPlayer()->name << " is not affected by last played card" << endl << endl;
				GameText << GetCurrentPlayer()->name << " is not affected by last played card" << endl << endl;
				return false;
			}
			else
			{
				cout << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
				GameText << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
				return true;
			}

			////If the card was played more than 0 turns ago, then it doesn't even matter
			//if (DeckOfCards.lastCard[0]->turnsSincePlayed = 1)
			//{
			//	int LCP = 0;
			//	int CP = 0;

			//	//Find index of current player and the last player to play a card
			//	for (int i = 0; i < ListOfPlayers.size(); i++)
			//	{
			//		if (ListOfPlayers[i] == LastCardPlayer)
			//		{
			//			LCP = i;
			//		}

			//		if (ListOfPlayers[i] == CurrentPlayer)
			//		{
			//			CP = i;
			//		}
			//	}

			//	//Using the indexes to determine whether or not the card was played by the previous player
			//	//Not sure if all of this logic is right yet tbh
			//	if (LCP = (CP - 1) || (LCP = (CP + 1)))
			//	{
			//		cout << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
			//		GameText << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
			//		return true;
			//	}


			//	if ((LCP = (NumberOfPlayers - 1)) && (CP = 0) && (DirectionOfPlay == GameDirection::Clockwise))
			//	{
			//		cout << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
			//		GameText << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
			//		return true;
			//	}

			//	if ((LCP = 0) && (CP = (NumberOfPlayers - 1)) && (DirectionOfPlay == GameDirection::AntiClockwise))
			//	{
			//		cout << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
			//		GameText << "Last played card DOES affect " << GetCurrentPlayer()->name << endl << endl;
			//		return true;
			//	}
			//	cout << GetCurrentPlayer()->name << " is not affected by last played card" << endl << endl;
			//	GameText << GetCurrentPlayer()->name << " is not affected by last played card" << endl << endl;
			//	return false;
			//}
		}
		//Same for Jack but no need for prints
		else if (DeckOfCards.lastCard[0]->cardType == card::type::Jack)
		{
			//If the card was played more than 0 turns ago, then it doesn't even matter
			if (DeckOfCards.lastCard[0]->turnsSincePlayed != 1)
			{
				return false;
			}
			else
			{
				return true;
			}

			//If the card was played more than 0 turns ago, then it doesn't even matter
			//if (DeckOfCards.lastCard[0]->turnsSincePlayed = 1)
			//{
			//	int LCP = 0;
			//	int CP = 0;

			//	//Find index of current player and the last player to play a card
			//	for (int i = 0; i < ListOfPlayers.size(); i++)
			//	{
			//		if (ListOfPlayers[i] == LastCardPlayer)
			//		{
			//			LCP = i;
			//		}

			//		if (ListOfPlayers[i] == CurrentPlayer)
			//		{
			//			CP = i;
			//		}
			//	}

			//	//Using the indexes to determine whether or not the card was played by the previous player
			//	//Not sure if all of this logic is right yet tbh
			//	if (LCP = (CP - 1) || (LCP = (CP + 1)))
			//	{
			//		return true;
			//	}


			//	if ((LCP = (NumberOfPlayers - 1)) && (CP = 0) && (DirectionOfPlay == GameDirection::Clockwise))
			//	{
			//		return true;
			//	}

			//	if ((LCP = 0) && (CP = (NumberOfPlayers - 1)) && (DirectionOfPlay == GameDirection::AntiClockwise))
			//	{
			//		return true;
			//	}
			//	return false;
			//}
		}
		return false;
	}

	//Play your chosen card
	void play(shared_ptr<card> c)
	{
		//For keeping track of what happened each game
		fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
		if (!GameText.is_open())
		{
			cout << "Error opening GameRecords.txt" << endl << endl;
		}

		if (card_is_playable(c))
		{
			//Trying to sort the problem where rules are enforced more than once if the last card remains the same
			NoLongerLastCard(DeckOfCards.lastCard[0]);

			DeckOfCards.lastCard.push_back(c);
			DeckOfCards.cardStack.push_back(DeckOfCards.lastCard[0]);
			DeckOfCards.lastCard.erase(DeckOfCards.lastCard.begin());

			DeckOfCards.lastCard[0]->turnsSincePlayed = 0;

			cout << GetCurrentPlayer()->name << " played the ";
			GameText << GetCurrentPlayer()->name << " played the ";
			GameText.close();
			DeckOfCards.identify_card(c);

			GetCurrentPlayer()->canPlay = false;
			GetCurrentPlayer()->canPickUp = false;

			for (int i = 0; i < GetCurrentPlayer()->hand.size(); i++)
			{
				if (cards_match(GetCurrentPlayer()->hand[i], c))
				{
					GetCurrentPlayer()->hand.erase(GetCurrentPlayer()->hand.begin() + i);
				}
			}
			
			setLastPlayedBy(DeckOfCards.lastCard[0]);

			NextPlayer();

			//Check if any hands are empty (can only possibly be the previous player that's hand has changed since last move), remove the player from the list
			for (int i = 0; i < ListOfPlayers.size(); i++)
			{
				if (ListOfPlayers[i]->hand.empty())
				{
					Scoreboard.PlayerIsOut(ListOfPlayers[i], GetNumberOfPlayers());
					ListOfPlayers.erase(ListOfPlayers.begin() + i);
				}
			}

			ConsultRules();
		}
		else
		{
			cout << "Sorry " << CurrentPlayer->name << ", you cannot play this card. The " << endl;
			GameText << "Sorry " << CurrentPlayer->name << ", you cannot play this card. The " << endl;
			DeckOfCards.identify_card(c);
			cout << "cannot be played on top of the ";
			GameText << "cannot be played on top of the ";
			DeckOfCards.identify_cards(DeckOfCards.lastCard);
			cout << "." << endl << endl;
			GameText << "." << endl << endl;
		}
	}


	void pickup()
	{
		//For keeping track of what happened each game
		fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
		if (!GameText.is_open())
		{
			cout << "Error opening GameRecords.txt" << endl << endl;
		}

		GetCurrentPlayer()->hand.push_back(DeckOfCards.cardStack[0]);
		DeckOfCards.cardStack.erase(DeckOfCards.cardStack.begin());
		DeckOfCards.UpdatePositionsAndTextures(GetCurrentPlayer());

		cout << GetCurrentPlayer()->name << " picked up." << endl;
		cout << GetCurrentPlayer()->name << "'s updated hand:" << endl;

		GameText << GetCurrentPlayer()->name << " picked up." << endl;
		GameText << GetCurrentPlayer()->name << "'s updated hand:" << endl;

		DeckOfCards.identify_cards(GetCurrentPlayer()->hand);

		NextPlayer();
		ConsultRules();
	}


	void setLastPlayedBy(shared_ptr<card> c)
	{
		c->lastPlayedBy = GetCurrentPlayer()->name;
	}

	bool lastCardPlayerIsOut()
	{
		for (auto &p : Scoreboard.getScoreboard())
		{
			if (DeckOfCards.lastCard[0]->lastPlayedBy == p->name)
			{
				return true;
			}
		}
		return false;
	}
	

	bool can_play_checker(vector<shared_ptr<card>> hand)
	{
		for (auto &c : hand)
		{
			if (c->cardSuit == DeckOfCards.lastCard[0]->cardSuit)
			{
				//cout << "Suit match!" << endl;
				GetCurrentPlayer()->canPlay = true;
				GetCurrentPlayer()->canPickUp = false;
				return true;
			}

			if (c->cardType == DeckOfCards.lastCard[0]->cardType)
			{
				//cout << "Type match!" << endl;
				GetCurrentPlayer()->canPlay = true;
				GetCurrentPlayer()->canPickUp = false;
				return true;
			}
		}
		//If the code makes it this far, then it hasn't found any
		//Matches in type or suit throughout the whole hand, so
		//we return false.
		//cout << "No matches!" << endl;
		GetCurrentPlayer()->canPlay = false;
		GetCurrentPlayer()->canPickUp = true;
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

	void GameOver()
	{
		//For keeping track of what happened each game
		fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
		if (!GameText.is_open())
		{
			cout << "Error opening GameRecords.txt" << endl << endl;
		}

		fstream GameRecords("../GameRecords/GameRecords.txt", ios::in | ios::out | ios::app);
		if (!GameRecords.is_open())
		{
			cout << "Error opening GameRecords.txt" << endl << endl;
		}
		else
		{
			//Get current date and time - credit to this: https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
			time_t t = time(0);
			struct tm * now = localtime(&t);

			//Formatting and printing the current date and time
			GameRecords << "Date:\t";

			if (now->tm_mday < 10)
			{
				GameRecords << "0" << now->tm_mday << "/";
			}
			else
			{
				GameRecords << now->tm_mday << "/";
			}

			if ((now->tm_mon + 1) < 10)
			{
				GameRecords << "0" << now->tm_mon + 1 << "/" << now->tm_year + 1900;
			}
			else
			{
				GameRecords << now->tm_mon + 1 << "/" << now->tm_year + 1900;
			}

			GameRecords << "\tTime:\t";

			if (now->tm_hour < 10)
			{
				GameRecords << "0" << now->tm_hour << ":";
			}
			else
			{
				GameRecords << now->tm_hour << ":";
			}

			if (now->tm_min < 10)
			{
				GameRecords << "0" << now->tm_min;
			}
			else
			{
				GameRecords << now->tm_min;
			}

			GameRecords << "\t\t\t\tGame " << MatchCounter;

			GameRecords << endl;

			GameRecords << endl << "Scoreboard:" << endl;
			GameText << endl << "Scoreboard:" << endl;

			//Printing scoreboard to file
			for (int i = 0; i < Scoreboard.getScoreboard().size(); i++)
			{
				switch (i)
				{
				case 0:
					GameRecords << "1st:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					GameText << "1st:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					break;
				case 1:
					GameRecords << "2nd:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					GameText << "2nd:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					break;
				case 2:
					GameRecords << "3rd:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					GameText << "3rd:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					break;
				case 3:
					GameRecords << "4th:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					GameText << "4th:\t" << setw(50) << left << Scoreboard.getScoreboard()[i]->name << Scoreboard.getScoreboard()[i]->getPlaystyle() << endl;
					break;
				default:
					break;
				}
			}
			GameRecords << "------------------------------------------------------------------------------------" << endl << endl;
		}


		cout << endl << endl << endl << "\t\t     GAME OVER \n\n\n\t\tPress enter to quit" << "\n\n\t      or Space for a rematch" <<endl;
		
		//while (!sf::Keyboard::isKeyPressed(Keyboard::Return))
		//{
		//	//Wait for Return to be pressed 
		//}

		while ((!sf::Keyboard::isKeyPressed(Keyboard::Return)) && (!sf::Keyboard::isKeyPressed(Keyboard::Space)))
		{
			//Wait for Return or Space to be pressed 
		}
	}


	void NoLongerLastCard(shared_ptr<card> previousLastCard)
	{
		for (auto &c : DeckOfCards.allCards)
		{
			if (cards_match(c, previousLastCard))
			{
				c->turnsSincePlayed = 0;
				break;
			}
		}
	}








	//Rules
	void ConsultRules()
	{
		//For keeping track of what happened each game
		fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
		if (!GameText.is_open())
		{
			cout << "Error opening GameRecords.txt" << endl << endl;
		}

		if (Scoreboard.Gameover(GetNumberOfPlayers()))
		{
			return;
		}

		//if (DoesLastCardAffectCurrentPlayer() || (DeckOfCards.lastCard[0]->cardType == card::type::Jack))
		if (DoesLastCardAffectCurrentPlayer())
		{
			//By default, assume player can play and can't pick up.
			//If this isn't the case, the following code will sort that out.
			GetCurrentPlayer()->canPickUp = false;
			GetCurrentPlayer()->canPlay = true;


			switch (DeckOfCards.lastCard[0]->cardType)
			{
				case(card::type::Queen):
				{
					if (DeckOfCards.lastCard[0]->cardColour == card::colour::Black)
					{
						cout << "The last card was a black queen!" << endl;
						cout << GetCurrentPlayer()->name << " must now pick up 5 cards." << endl << endl; 
						
						GameText << "The last card was a black queen!" << endl;
						GameText << GetCurrentPlayer()->name << " must now pick up 5 cards." << endl << endl;

						GetCurrentPlayer()->canPickUp = true;
						GetCurrentPlayer()->canPlay = false;

						for (int i = 0; i < 5; i++)
						{
							GetCurrentPlayer()->hand.push_back(DeckOfCards.cardStack[0]);
							DeckOfCards.cardStack.erase(DeckOfCards.cardStack.begin());
						}

						//Display updated hand
						cout << GetCurrentPlayer()->name << "'s updated hand:" << endl;
						GameText << GetCurrentPlayer()->name << "'s updated hand:" << endl;
						DeckOfCards.identify_cards(GetCurrentPlayer()->hand);

						GetCurrentPlayer()->canPickUp = false;
						GetCurrentPlayer()->canPlay = false;

						NextPlayer();
						can_play_checker(GetCurrentPlayer()->hand);
						break;
					}

					can_play_checker(GetCurrentPlayer()->hand);
					break;
				}
				case(card::type::Two):
				{
					cout << "The last card was a two!" << endl;
					cout << GetCurrentPlayer()->name << " must now pick up 2 cards." << endl << endl;

					GameText << "The last card was a two!" << endl;
					GameText << GetCurrentPlayer()->name << " must now pick up 2 cards." << endl << endl;

					GetCurrentPlayer()->canPickUp = true;
					GetCurrentPlayer()->canPlay = false;

					for (int i = 0; i < 2; i++)
					{
						GetCurrentPlayer()->hand.push_back(DeckOfCards.cardStack[0]);
						DeckOfCards.cardStack.erase(DeckOfCards.cardStack.begin());
					}

					cout << GetCurrentPlayer()->name << "'s updated hand:" << endl;
					GameText << GetCurrentPlayer()->name << "'s updated hand:" << endl;
					DeckOfCards.identify_cards(GetCurrentPlayer()->hand);

					GetCurrentPlayer()->canPickUp = false;
					GetCurrentPlayer()->canPlay = false;

					NextPlayer();
					can_play_checker(GetCurrentPlayer()->hand);
					break;
				}
				case(card::type::Jack):
				{
					cout << "The last card was a jack!" << endl;
					GameText << "The last card was a jack!" << endl;
					ChangeDirectionOfPlay();

					GetCurrentPlayer()->canPickUp = false;
					GetCurrentPlayer()->canPlay = false;

					NextPlayer();

					//If the last card is a jack and the player that played it is now out of the game, 
					//only move on one player.
					if (!lastCardPlayerIsOut())
					{
						NextPlayer();
					}

					cout << "The direction of play has been reversed." << endl << endl;
					cout << GetCurrentPlayer()->name << ", it's your turn." << endl << endl;

					GameText << "The direction of play has been reversed." << endl << endl;
					GameText << GetCurrentPlayer()->name << ", it's your turn." << endl << endl;

					can_play_checker(GetCurrentPlayer()->hand);
					break;
				}
				case(card::type::Eight):
				{
					cout << "The last card was an eight!" << endl;
					cout << GetCurrentPlayer()->name << " is forced to skip their turn." << endl << endl;

					GameText << "The last card was an eight!" << endl;
					GameText << GetCurrentPlayer()->name << " is forced to skip their turn." << endl << endl; 

					GetCurrentPlayer()->canPickUp = false;
					GetCurrentPlayer()->canPlay = false;

					NextPlayer();
					cout << GetCurrentPlayer()->name << ", it's your turn." << endl << endl;
					GameText << GetCurrentPlayer()->name << ", it's your turn." << endl << endl;

					can_play_checker(GetCurrentPlayer()->hand);
					break;
				}
				default:
				{
					can_play_checker(GetCurrentPlayer()->hand);
					break;
				}
			}
		}
		DeckOfCards.UpdatePositionsAndTextures(GetCurrentPlayer());
		can_play_checker(GetCurrentPlayer()->hand); //Dunno if this is necessary but it's 4am sooooooooooooooooooooo
	}
};

//Turns out this is SUPER important for the singleton to work
GameManager *GameManager::instance = NULL;