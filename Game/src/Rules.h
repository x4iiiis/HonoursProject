#pragma once

#include <vector>
#include <iostream>

//#include "player.h"
//#include "GameManager.h"
//#include "Deck.h"

using namespace std;

class Rules
{
private:
	//GameManager *GM = GameManager::Manager();

public:

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
					//DeckOfCards->identify_cards(PlayerList[0]->hand);
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
				//DeckOfCards->identify_cards(PlayerList[0]->hand);
				//GameManager::Manager()->DeckOfCards.identify_cards(PlayerList[0]->hand);

				break;
			}
			//Game management - we need the direction of play to be defined somewhere
			case(card::type::Jack):
			{
				cout << "The last card was a jack!" << endl;
				//GameManager::Manager()->ChangeDirectionOfPlay();
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