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
	GameManager::Manager()->DeckOfCards.LoadTextures();

	//Ranking for when players get out
	vector<shared_ptr<player>> ranking;

	//shared_ptr<GameManager> GM;
	//make_shared<GameManager>(GM);

	//GameManager *GM = GameManager::Manager();

	GameManager::Manager()->PlayerCreation();
	GameManager::Manager()->setFirstPlayer();
	GameManager::Manager()->DeckOfCards.SetUpDeck();
	//GameManager::Manager()->DeckOfCards.Deal(GameManager::Manager()->GetListOfPlayers(), GameManager::Manager()->GetCardsPerPlayer());






	//Testing SFML
	//RenderWindow window(VideoMode(800,600), "Welcome to NeuroSwitch!", Style::Fullscreen);
	RenderWindow window(VideoMode(800, 600), "Welcome to NeuroSwitch!");
	window.setFramerateLimit(60);	//60FPS (not really necessary for this project tbh but meh) 
	window.clear(Color(63, 191, 127, 255));	//Setting the background colour
	//window.draw(GameManager::Manager()->DeckOfCards.Draw().sprite);
	//window.display();








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
	GameManager::Manager()->SetCardsPerPlayer(2);






	


	//testing next player works
	//GameManager::Manager()->NextPlayer();
	//cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	//GameManager::Manager()->NextPlayer();
	//cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	//GameManager::Manager()->NextPlayer();
	//cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	//GameManager::Manager()->NextPlayer();
	//cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	//GameManager::Manager()->NextPlayer();
	//cout << GameManager::Manager()->GetCurrentPlayer()->name << endl;
	//cout << endl;
	




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

	//Unnecessary here (I think), but every time the card on the top of the card stack changes, call this to sort the texture of the one moving out, and then next call to flip one coming in
	GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer()->hand);
	//Setting the new top card of the cardStack to be facedown (texture wise)
	GameManager::Manager()->DeckOfCards.SetFaceDown(GameManager::Manager()->DeckOfCards.cardStack[0]);

	//Draw card at top of the stack
	//GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.setPosition(Vector2f(365, 250));
	//window.draw(GameManager::Manager()->DeckOfCards.cardStack[0]->sprite);

	cout << "The cards have been dealt by " << GameManager::Manager()->GetCurrentPlayer()->name << " and our first card to be played on is" << endl;
	
	//Player left of the dealer starts, so we need to move current player on to that player
	GameManager::Manager()->NextPlayer();
//****************************************************************************************************************************************************************************************
//1337haxx to make it a jack
	//GameManager::Manager()->DeckOfCards.lastCard[0]->PickYourOwnLastCard(card::type::Jack, card::suit::Clubs);
//*****************************************************************************************************************************************************************************************

	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->DeckOfCards.lastCard);
	cout << "(which is " << GameManager::Manager()->DeckOfCards.checkColour(GameManager::Manager()->DeckOfCards.lastCard[0]) << ")" << endl << endl << endl;


	//Testing SFML - Drawing first card to be played on
	//GameManager::Manager()->DeckOfCards.lastCard[0]->sprite.setPosition(Vector2f(365, 5));
	//window.draw(GameManager::Manager()->DeckOfCards.lastCard[0]->sprite);
	//window.display();



	cout << "The player left of the dealer will start." << endl;
	cout << GameManager::Manager()->GetCurrentPlayer()->name << ", do you have any cards that match either in suit or in type?" << endl << endl;

	//Display Current Player's hand
	cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s hand:" << endl;
	GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

	//Check the current player can play (sets canPlay and canPickUp bools)
	GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand);
	



	
	//Every time a card is played, call:
	/*if (GameManager::Manager()->DoesLastCardAffectCurrentPlayer(GameManager::Manager()->WhoPlayedTheLastCard(), GameManager::Manager()->GetCurrentPlayer()) == true)
	{
		GameManager::Manager()->ConsultRules();
	}*/
	//This checks the last card against the rules relating to certain cards
	//At the moment, a black queen forces 5 cards, a two forces 2, and
	//eight and jack are there but just produce cout statements at this point.





	
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
				&& Mouse::isButtonPressed(Mouse::Left))
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


		//If the current player cannot play
		if (!GameManager::Manager()->can_play_checker(GameManager::Manager()->GetCurrentPlayer()->hand))
		{
			//if (GameManager::Manager()->GetCurrentPlayer()->canPickUp)
			{
				if (mousePos.x > GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().x
					&& mousePos.x < GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().x + GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getGlobalBounds().width
					&& mousePos.y > GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().y
					&& mousePos.y < GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getPosition().y + GameManager::Manager()->DeckOfCards.cardStack[0]->sprite.getGlobalBounds().height
					&& Mouse::isButtonPressed(Mouse::Left))
				{
					GameManager::Manager()->GetCurrentPlayer()->hand.push_back(GameManager::Manager()->DeckOfCards.cardStack[0]);
					//Update Hand and draw it
					cout << GameManager::Manager()->GetCurrentPlayer()->name << "'s updated hand:" << endl;
					GameManager::Manager()->DeckOfCards.identify_cards(GameManager::Manager()->GetCurrentPlayer()->hand);

					GameManager::Manager()->DeckOfCards.cardStack.erase(GameManager::Manager()->DeckOfCards.cardStack.begin());
					GameManager::Manager()->DeckOfCards.UpdatePositionsAndTextures(GameManager::Manager()->GetCurrentPlayer()->hand);

					GameManager::Manager()->NextPlayer();
					

					//Setting the background colour
					window.clear(Color(63, 191, 127, 255));
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