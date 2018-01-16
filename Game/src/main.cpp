#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include <istream>
#include <random> 
#include <vector>
#include <ctime>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "card.h"
#include "player.h"
#include "GameManager.h"

using namespace sf;
using namespace std;

int main()
{
	//Wipe GameText.txt when a new game starts
	if (remove("../GameRecords/GameText.txt") != 0)
	{
		cout << "Error deleting GameText.txt";
	}

	//For keeping track of what happened each game
	fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
	if (!GameText.is_open())
	{
		cout << "Error opening GameRecords.txt" << endl << endl;
	}

	//Get the game initialised
	GameManager::Manager()->DeckOfCards.LoadTextures();
	GameManager::Manager()->PlayerCreation();
	GameManager::Manager()->setFirstPlayer();
	GameManager::Manager()->DeckOfCards.SetUpDeck();
	GameManager::Manager()->SetCardsPerPlayer(2);


RestartPoint:
	//Display player names in GameText.txt
	GameText << "Players:" << endl;
	for (auto &p : GameManager::Manager()->GetListOfPlayers())
	{
		GameText << p->name << endl;
	}
	GameText << endl << endl;

	//Deal the cards
	GameManager::Manager()->DeckOfCards.Deal(GameManager::Manager()->GetListOfPlayers(), GameManager::Manager()->GetCardsPerPlayer());


	//Let's turn the top card over and see what we're playing on
	GameManager::Manager()->DeckOfCards.lastCard.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
	GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());

	cout << "The cards have been dealt by " << GameManager::Manager()->GetCurrentPlayer()->name << " and our first card to be played on is the" << endl;
	GameText << "The cards have been dealt by " << GameManager::Manager()->GetCurrentPlayer()->name << " and our first card to be played on is the" << endl;
	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->DeckOfCards.lastCard);

	GameManager::Manager()->DeckOfCards.lastCard[0]->turnsSincePlayed = 0;
	GameManager::Manager()->SetLastCardPlayer(GameManager::Manager()->GetCurrentPlayer());

	//Left of the dealer starts, unless the first card to be played on is a jack 
	if (GameManager::Manager()->DeckOfCards.lastCard[0]->cardType != card::type::Jack)
	{
		cout << "The player left of the dealer will start." << endl << endl;
		GameText << "The player left of the dealer will start." << endl << endl;
		
		//Player left of the dealer starts, so we need to move current player on to that player
		GameManager::Manager()->NextPlayer();
		GameManager::Manager()->ConsultRules();
	}
	else
	{
		cout << "The player right of the dealer will start." << endl << endl;
		GameText << "The player right of the dealer will start." << endl << endl;

		GameManager::Manager()->DeckOfCards.lastCard[0]->turnsSincePlayed == 1;
		GameManager::Manager()->ConsultRules();
	}

	//Player left of the dealer starts, so we need to move current player on to that player
	//GameManager::Manager()->NextPlayer();
	//GameManager::Manager()->ConsultRules();

	//^ I'm gonna move the nextplayer() here and put it in the if
	//I'm thinking that if the first card to play on is a jack, it's gonna do that automatically




	//Initialising SFML window
	RenderWindow window(VideoMode(800, 600), "Welcome to NeuroSwitch!");
	window.setFramerateLimit(60);	//60FPS (not really necessary for this project) 
	window.clear(Color(63, 191, 127, 255));	//Setting the background colour for the game window

	//SFML
	GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
	for (auto &c : GameManager::Manager()->DeckOfCards.allCards)
	{
		window.draw(c->sprite);
	}
	window.display();


	//Game Loop
	while (window.isOpen())
	{
		//Setting the background colour
		window.clear(Color(63, 191, 127, 255));

		GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());

		for (auto &c : GameManager::Manager()->DeckOfCards.allCards)
		{
			window.draw(c->sprite);
		}
		window.display();
		window.setActive();


		//Getting the position of the mouse (in relation to the window)
		Vector2i mousePos = Mouse::getPosition(window);

		//For checking if mouse is released
		sf::Event eventt;

		

		while (window.pollEvent(eventt))
		{


			/*if (Keyboard::isKeyPressed(Keyboard::F))
			{
				window.setSize(Style::Fullscreen));
			}*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Human Players playing
			if (GameManager::Manager()->GetCurrentPlayer()->playstyle == player::Playstyle::Human)
			{
				//This prints endlessly until a move is made... D: 
				cout << GameManager::Manager()->GetCurrentPlayer()->name << " to play." << endl << endl;
				
				//Messing about with clicking sprites
				for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
				{
					//If sprite is clicked on
					if (mousePos.x > c->sprite.getPosition().x
						&& mousePos.x < c->sprite.getPosition().x + c->sprite.getGlobalBounds().width
						&& mousePos.y > c->sprite.getPosition().y
						&& mousePos.y < c->sprite.getPosition().y + c->sprite.getGlobalBounds().height)
					{
						if (eventt.type == Event::MouseButtonReleased)
						{
							if (eventt.mouseButton.button == Mouse::Left)
							{
								if (GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
								{
									GameManager::Manager()->play(c);
									GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
									//Setting the background colour
									window.clear(Color(63, 191, 127, 255));

									goto draw;
								}
							}
						}
					}
				}

				//If human can't play
				if (mousePos.x > GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().x
					&& mousePos.x < GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().x + GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getGlobalBounds().width
					&& mousePos.y > GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().y
					&& mousePos.y < GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().y + GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getGlobalBounds().height)
				{
					if (eventt.type == Event::MouseButtonReleased)
					{
						if (eventt.mouseButton.button == Mouse::Left)
						{
							//If the current player cannot play
							if (!GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
							{
								if (GameManager::Manager()->GetCurrentPlayer()->canPickUp)
								{
									//GameManager::Manager()->GetCurrentPlayer()->hand.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
									GameManager::Manager()->pickup();
									//Update Hand and draw it
									/*cout << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
									cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;

									GameText << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
									GameText << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;

									GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

									GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());
									GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());

									GameManager::Manager()->NextPlayer();
									GameManager::Manager()->ConsultRules();*/

									//Setting the background colour
									window.clear(Color(63, 191, 127, 255));
								}
							}
						}
					}
				}
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//If Neural Network AI Agent is playing

			//[insert AI stuff here]
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//If "Aggressive" player is playing
			if (GameManager::Manager()->GetCurrentPlayer()->playstyle == player::Playstyle::Aggressive)
			{
				//Checking gameover isn't true cause if not it's gonna try to play on even if it's the last player
				if (!GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
				{
					cout << GameManager::Manager()->GetCurrentPlayer()->name << " to play." << endl << endl;
					
					//Draw hand etc before sleep
					GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
					for (auto &c : GameManager::Manager()->DeckOfCards.allCards)
					{
						window.draw(c->sprite);
					}
					window.display();

					cout << "[Not human, sleeping for 3 seconds . . .]" << endl << endl;
					//If the current player is not human, take 3 seconds before trying to make a move
					//just to allow us to see what the player is doing, and also to make it feel a bit
					//more authentic, rather than being able to loop through several non-human players'
					//moves in the blink of an eye
					sleep(seconds(3.0f));

					//auto tempHand = GameManager::Manager()->GetCurrentPlayer()->hand;

					if (GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
					{
						//Check for a black queen
						for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
						{
							//If "Aggressive" has a black queen, it will attempt to play it.
							if ((c->cardType == card::type::Queen) && (c->cardColour == card::colour::Black))
							{
								//Trying to fix nullptr issue
								if (GameManager::Manager()->card_is_playable(c))
								{
									GameManager::Manager()->play(c);
									GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
									//Setting the background colour
									window.clear(Color(63, 191, 127, 255));

									//test
									goto draw;
								}
							}
						}

						//If "Aggressive" has a two, it will attempt to play it after searching for a black queen.
						for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
						{
							if (c->cardType == card::type::Two)
							{
								//Trying to fix nullptr issue
								if (GameManager::Manager()->card_is_playable(c))
								{
									GameManager::Manager()->play(c);
									GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
									//Setting the background colour
									window.clear(Color(63, 191, 127, 255));

									//test
									goto draw;
								}
							}
						}

						//If "Aggressive" has an eight, it will attempt to play it after searching for a black queen and a two.
						for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
						{
							if (c->cardType == card::type::Eight)
							{
								//Trying to fix nullptr issue
								if (GameManager::Manager()->card_is_playable(c))
								{
									GameManager::Manager()->play(c);
									GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
									//Setting the background colour
									window.clear(Color(63, 191, 127, 255));

									//test
									goto draw;
								}
							}
						}

						//If no power cards are held, just attempt to play every card until something works
						for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
						{
							//Trying to fix nullptr issue
							if (GameManager::Manager()->card_is_playable(c))
							{
								GameManager::Manager()->play(c);
								GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
								//Setting the background colour
								window.clear(Color(63, 191, 127, 255));

								//test
								goto draw;
							}
						}
					}
				}
			}
			if (GameManager::Manager()->GetCurrentPlayer()->playstyle == player::Playstyle::Aggressive)
			{
				//If "aggressive" cannot play
				if (!GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
				{
					//Checking gameover isn't true cause if not it's gonna try to play on even if it's the last player
					if (!GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
					{
						if (GameManager::Manager()->GetCurrentPlayer()->canPickUp)
						{
							//GameManager::Manager()->GetCurrentPlayer()->hand.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
							GameManager::Manager()->pickup();
							//Update Hand and draw it
							/*cout << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
							cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;

							GameText << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
							GameText << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;

							GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

							GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());
							GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());

							GameManager::Manager()->NextPlayer();
							GameManager::Manager()->ConsultRules();*/

							//Setting the background colour
							window.clear(Color(63, 191, 127, 255));
						}
					}
				}
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//If "Unaggressive" player is playing
		if (GameManager::Manager()->GetCurrentPlayer()->playstyle == player::Playstyle::Unaggressive)
		{
			//Checking gameover isn't true cause if not it's gonna try to play on even if it's the last player
			if (!GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
			{
				cout << GameManager::Manager()->GetCurrentPlayer()->name << " to play." << endl << endl;
				
				//Draw hand etc before sleep
				GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
				for (auto &c : GameManager::Manager()->DeckOfCards.allCards)
				{
					window.draw(c->sprite);
				}
				window.display();


				cout << "[Not human, sleeping for 3 seconds . . .]" << endl << endl;
				//If the current player is not human, take 3 seconds before trying to make a move
				//just to allow us to see what the player is doing, and also to make it feel a bit
				//more authentic, rather than being able to loop through several non-human players'
				//moves in the blink of an eye
				sleep(seconds(3.0f));

				if (GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
				{
					//Avoid playing power cards initially, and just play the first available playable card
					for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
					{
						//If "Unaggressive" has a black queen, it will attempt to avoid playing it.
						if ((c->cardType == card::type::Queen) && (c->cardColour == card::colour::Black))
						{
							continue;
						}
						//If "Unaggressive" has a two, it will attempt to avoid playing it.
						else if (c->cardType == card::type::Two)
						{
							continue;
						}
						//If "Unaggressive" has an eight, it will attempt to avoid playing it.
						else if (c->cardType == card::type::Eight)
						{
							continue;
						}

						//Trying to fix nullptr issue
						if (GameManager::Manager()->card_is_playable(c))
						{
							//If no power cards are held, just attempt to play every card until something works
							GameManager::Manager()->play(c);
							GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
							//Setting the background colour
							window.clear(Color(63, 191, 127, 255));

							//test
							goto draw;
						}
					}

					//If power cards are the only playable cards, just play whichever is first available
					//Attempt to play every card until something works
					for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
					{
						//Trying to fix nullptr issue
						if (GameManager::Manager()->card_is_playable(c))
						{
							GameManager::Manager()->play(c);
							GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
							//Setting the background colour
							window.clear(Color(63, 191, 127, 255));

							//test
							//continue;
							goto draw;
						}
					}
				}
			}
		}
		if (GameManager::Manager()->GetCurrentPlayer()->playstyle == player::Playstyle::Unaggressive)
		{
			//Checking gameover isn't true cause if not it's gonna try to play on even if it's the last player
			if (!GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
			{
				//If "Unggressive" cannot play
				if (!GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
				{
					if (GameManager::Manager()->GetCurrentPlayer()->canPickUp)
					{
						//GameManager::Manager()->GetCurrentPlayer()->hand.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
						GameManager::Manager()->pickup();
						//Update Hand and draw it
						/*cout << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
						cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;

						GameText << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
						GameText << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;

						GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

						GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());
						GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());

						GameManager::Manager()->NextPlayer();
						GameManager::Manager()->ConsultRules();*/

						//Setting the background colour
						window.clear(Color(63, 191, 127, 255));
					}
				}
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//If "Random" player is playing
		if (GameManager::Manager()->GetCurrentPlayer()->playstyle == player::Playstyle::Random)
		{
			//Checking gameover isn't true cause if not it's gonna try to play on even if it's the last player
			if (!GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
			{
				cout << GameManager::Manager()->GetCurrentPlayer()->name << " to play." << endl << endl;
				
				//Draw hand etc before sleep
				GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
				for (auto &c : GameManager::Manager()->DeckOfCards.allCards)
				{
					window.draw(c->sprite);
				}
				window.display();

				cout << "[Not human, sleeping for 3 seconds . . .]" << endl << endl;
				//If the current player is not human, take 3 seconds before trying to make a move
				//just to allow us to see what the player is doing, and also to make it feel a bit
				//more authentic, rather than being able to loop through several non-human players'
				//moves in the blink of an eye
				sleep(seconds(3.0f));

				
				if (GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
				{
					//Shuffle the hand so that the order of cards attempted varies
					std::srand(std::time(0));	//For some reason shuffle doesn't work when you restart the program, it uses the previously shuffled version... this line solves that.Needs <ctime> included 
					std::random_shuffle(GameManager::Manager()->GetCurrentPlayer()->hand.begin(), GameManager::Manager()->GetCurrentPlayer()->hand.end());
					std::random_shuffle(GameManager::Manager()->GetCurrentPlayer()->hand.begin(), GameManager::Manager()->GetCurrentPlayer()->hand.end());
					std::random_shuffle(GameManager::Manager()->GetCurrentPlayer()->hand.begin(), GameManager::Manager()->GetCurrentPlayer()->hand.end());

					//Attempt to play every card until something works
					for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
					{
						//Trying to fix nullptr issue
						if (GameManager::Manager()->card_is_playable(c))
						{
							GameManager::Manager()->play(c);
							GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());
							//Setting the background colour
							window.clear(Color(63, 191, 127, 255));

							//test
							//continue;
							goto draw;
						}
					}
				}
			}
		}

		if (GameManager::Manager()->GetCurrentPlayer()->playstyle == player::Playstyle::Random)
		{
			//If "Random" cannot play
			if (!GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
			{
				//Checking gameover isn't true cause if not it's gonna try to play on even if it's the last player
				if (!GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
				{
					if (GameManager::Manager()->GetCurrentPlayer()->canPickUp)
					{
						////GameManager::Manager()->GetCurrentPlayer()->hand.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
						GameManager::Manager()->pickup();
						////Update Hand and draw it
						//cout << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
						//cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;

						//GameText << GameManager::Manager()->GetCurrentPlayer()->name << " picked up." << endl;
						//GameText << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;
						//
						//GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

						//GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());
						//GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());

						//GameManager::Manager()->NextPlayer();
						//GameManager::Manager()->ConsultRules();

						//Setting the background colour
						window.clear(Color(63, 191, 127, 255));
					}
				}
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


draw:
		GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer());

		for (auto &c : GameManager::Manager()->DeckOfCards.allCards)
		{
			window.draw(c->sprite);
		}
		window.display();
		window.setActive(); //Trying to deal with having to move the mouse cause of weird pause


		//If only one player is left, Gameover will be true. 
		//Add the loser to the scoreboard and close the SFML window
		if (GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
		{
			GameManager::Manager()->Scoreboard.PlayerIsOut(GameManager::Manager()->GetCurrentPlayer(), GameManager::Manager()->GetNumberOfPlayers());	//Must be current player cause they're the onl
			GameManager::Manager()->Scoreboard.DisplayScoreboard();
			window.close();
		}
	}

	GameManager::Manager()->GameOver();



	//Trying to start games over
	GameManager::Manager()->GetCurrentPlayer()->hand.clear();
	GameManager::Manager()->DeckOfCards.cardStack.clear();
	GameManager::Manager()->DeckOfCards.lastCard.clear();
	GameManager::Manager()->DeckOfCards.allCards.clear();
	GameManager::Manager()->GetListOfPlayers().clear();
	GameManager::Manager()->Scoreboard.clear();
	
	GameManager::Manager()->RespawnPlayers();
	GameManager::Manager()->setFirstPlayer();
	GameManager::Manager()->DeckOfCards.SetUpDeck();

	//Wipe GameText.txt when a new game starts
	if (remove("../GameRecords/GameText.txt") != 0)
	{
		cout << "Error deleting GameText.txt";
	}

	//For keeping track of what happened each game
	//fstream GameText("../GameRecords/GameText.txt", ios::in | ios::out | ios::app);
	if (!GameText.is_open())
	{
		cout << "Error opening GameRecords.txt" << endl << endl;
	}

	goto RestartPoint;

	return 0;
}


//Simon's comments:
//Rules like forcing to play a certain card could be difficult to implement,
//so start with just the black queen and jack rules for now and potentially
//add others later if things are going well

//Think what he meant by that was forcing it to pick up will be okay but forcing
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