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
//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

int main()
{
	//Initialising SFML window
	//RenderWindow window(VideoMode(800, 600), "Welcome to NeuroSwitch!");
	//window.setFramerateLimit(60);	//60FPS (not really necessary for this project) 
	//window.clear(Color(63, 191, 127, 255));	//Setting the background colour for the game window


	GameManager::Manager()->DeckOfCards.LoadTextures();
	GameManager::Manager()->PlayerCreation();
	GameManager::Manager()->setFirstPlayer();
	GameManager::Manager()->DeckOfCards.SetUpDeck();

	


	//For all cards in allCards, shout out the suit (testing that populating and shuffling works)
	//For some reason both this and the [i] method are getting a first result but then crashing the program
	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->DeckOfCards.allCards);


	//We need to know how many cards each player is going to be dealt.
	//This could be something we let the user decide...
	//But for now let's make it 7.
	//int CardsPerPlayer = 7;
	GameManager::Manager()->SetCardsPerPlayer(2);

	
	//Let's deal!
	//We need a nested for loop here so that the outside loop deals 7 times
	//but the inside loop makes sure that it doesn't just deal 7 cards to each player
	//sequentially. Cards should be dealt 1 by 1 around the table until everyone has 
	//[CardsPerPlayer] cards.
	//The inner loop decides who is recieving the next card.
	GameManager::Manager()->DeckOfCards.Deal(GameManager::Manager()->GetListOfPlayers(), GameManager::Manager()->GetCardsPerPlayer());


	//I'm not confident about the * notation so let's get some tests done here
	cout << endl << endl; 
	cout << "allCards.size() = " << GameManager::Manager()->DeckOfCards.allCards.size() << endl;
	cout << "cardStack.size() = " << GameManager::Manager()->DeckOfCards.cardStack.size() << endl << endl;
	cout << "If that worked, each player should have 7 cards." << endl << "allCards should still have 52 cards, and cardstack should have "
		<< 52 - (GameManager::Manager()->GetListOfPlayers().size() * GameManager::Manager()->GetCardsPerPlayer()) << endl << endl;


	//Right let's turn the top (or bottom in our case) card over and see what we're playing on
	GameManager::Manager()->DeckOfCards.lastCard.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
	GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());

	cout << "The cards have been dealt by " << GameManager::Manager()->GetCurrentPlayer()->name << " and our first card to be played on is" << endl;
	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->DeckOfCards.lastCard);
	cout << "The player left of the dealer will start." << endl << endl;

	//Player left of the dealer starts, so we need to move current player on to that player
	GameManager::Manager()->NextPlayer();
	
	//Display Current Player's hand
	cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s hand:" << endl;
	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

	//Check the current player can play (sets canPlay and canPickUp bools)
	if (GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
	{
		cout << GameManager::Manager()->GetCurrentPlayer()->name << " can play.";
	}
	else
	{
		cout << GameManager::Manager()->GetCurrentPlayer()->name << ", you'll have to pick up.";
	}



	
	//Every time a card is played, call:
	/*if (GameManager::Manager()->DoesLastCardAffectCurrentPlayer(GameManager::Manager()->WhoPlayedTheLastCard(), GameManager::Manager()->GetCurrentPlayer()) == true)
	{
		GameManager::Manager()->ConsultRules();
	}*/
	//This checks the last card against the rules relating to certain cards
	//At the moment, a black queen forces 5 cards, a two forces 2, and
	//eight and jack are there but just produce cout statements at this point.




	//Initialising SFML window
	RenderWindow window(VideoMode(800, 600), "Welcome to NeuroSwitch!");
	window.setFramerateLimit(60);	//60FPS (not really necessary for this project) 
	window.clear(Color(63, 191, 127, 255));	//Setting the background colour for the game window
	
	//SFML
	GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer()->hand);
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
		
												
		//Getting the position of the mouse (in relation to the window)
		Vector2i mousePos = Mouse::getPosition(window);

		//For checking if mouse is released
		sf::Event eventt;

		while (window.pollEvent(eventt))
		{
			//TeSting
			//cout << "It's " << GameManager::Manager()->GetCurrentPlayer()->name << "'s turn" << endl << endl;



			/*if (Keyboard::isKeyPressed(Keyboard::F))
			{
				window.setSize(Style::Fullscreen));
			}*/


			//Messing about with clicking sprites
			for (auto &c : GameManager::Manager()->GetCurrentPlayer()->hand)
			{
				//More serious now, going to 'play' a card (add it to last card[])
				//If sprite is clicked on
				if (mousePos.x > c->sprite.getPosition().x
					&& mousePos.x < c->sprite.getPosition().x + c->sprite.getGlobalBounds().width
					&& mousePos.y > c->sprite.getPosition().y
					&& mousePos.y < c->sprite.getPosition().y + c->sprite.getGlobalBounds().height
					)//&& Mouse::isButtonPressed(Mouse::Left))
				{
					if (eventt.type == Event::MouseButtonReleased)

					{

						if (eventt.mouseButton.button == Mouse::Left)
						{

							if (GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
							{
								GameManager::Manager()->play(c, GameManager::Manager()->GetCurrentPlayer()->hand);
								GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer()->hand);
								//Setting the background colour
								window.clear(Color(63, 191, 127, 255));

								break;
							}
						}
					}
				}
			}


			if (mousePos.x > GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().x
				&& mousePos.x < GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().x + GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getGlobalBounds().width
				&& mousePos.y > GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().y
				&& mousePos.y < GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().y + GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getGlobalBounds().height
				)//&& Mouse::isButtonPressed(Mouse::Left))
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
								//Last card is still the same, so increment turnsSincePlayed variable to prevent rules being enforced multiple times
								//GameManager::Manager()->DeckOfCards.lastCard[0]->turnsSincePlayed += 1;

								GameManager::Manager()->GetCurrentPlayer()->hand.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
								//Update Hand and draw it
								cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;
								GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

								GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());
								GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer()->hand);

								GameManager::Manager()->NextPlayer();
								GameManager::Manager()->ConsultRules();

								//Setting the background colour
								window.clear(Color(63, 191, 127, 255));
							}
						}
					}
				}
			}
		}

		GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer()->hand);
		
		for (auto &c : GameManager::Manager()->DeckOfCards.allCards)
		{
			window.draw(c->sprite);
		}
		window.display();



		
		//If only one player is left, Gameover will be true. 
		//Add the loser to the scoreboard and close the SFML window
		if (GameManager::Manager()->Scoreboard.Gameover(GameManager::Manager()->GetNumberOfPlayers()))
		{
			GameManager::Manager()->Scoreboard.PlayerIsOut(GameManager::Manager()->GetCurrentPlayer());	//Must be current player cause they're the only one left..? 
			GameManager::Manager()->Scoreboard.DisplayScoreboard();
			window.close();
		}
	}

	GameManager::Manager()->GameOver();

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