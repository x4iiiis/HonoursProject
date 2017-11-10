#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <fstream>
#include <random> 
/////////////////////////////
#include "card.h"
#include "player.h"
#include <vector>
#include <ctime>

using namespace std;

int main() {

  //card test;

  //////////////////////////////////////////////////////////////////////////////////52 cards, first index = 0
  vector<card> allCards;
  vector<card> cardStack;


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
  vector<card> clubsArray{ ca, c2, c3, c4, c5, c6, c7, c8, c9, c10, cj, cq, ck };
  vector<card> diamondsArray{ da, d2, d3, d4, d5, d6, d7, d8, d9, d10, dj, dq, dk };
  vector<card> heartsArray{ ha, h2, h3, h4, h5, h6, h7, h8, h9, h10, hj, hq, hk };
  vector<card> spadesArray{ sa, s2, s3, s4, s5, s6, s7, s8, s9, s10, sj, sq, sk};



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
  for (auto &c : clubsArray)
  {
	  //allCards->push_back(clubsArray);
	  allCards.push_back(c);
  }

  //Add shuffled diamonds to allCards
  for (auto &c : diamondsArray)
  {
	  allCards.push_back(c); 
  }

  //Add shuffled hearts to allCards
  for (auto &c : heartsArray)
  {
	  allCards.push_back(c);
  }
  
  //Add shuffled spades to allCards
  for (auto &c : spadesArray)
  {
	  allCards.push_back(c);
  }

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
  for (auto &c : allCards)
  {
	  if (c.cardType == card::type::Ace)
	  {
		  cout << "Ace of ";
	  }
	  if (c.cardType == card::type::Jack)
	  {
		  cout << "Jack of ";
	  }
	  if (c.cardType == card::type::Queen)
	  {
		  cout << "Queen of ";
	  }
	  if (c.cardType == card::type::King)
	  {
		  cout << "King of ";
	  }
	  if (c.cardType != card::type::Ace && c.cardType != card::type::Jack && c.cardType != card::type::Queen && c.cardType != card::type::King)
	  {
		  cout << (static_cast<int>(c.cardType) + 1) << " of ";
	  }


	  if (c.cardSuit == card::suit::Diamonds)
	  {
		  cout << "Diamonds!" << endl;
	  }
	  if (c.cardSuit == card::suit::Clubs)
	  {
		  cout << "Clubs!" << endl;
	  }
	  if (c.cardSuit == card::suit::Hearts)
	  {
		  cout << "Hearts!" << endl;
	  }
	  if (c.cardSuit == card::suit::Spades)
	  {
		  cout << "Spades!" << endl;
	  }
  }


  //for (int i = 0; i < allCards->size(); i++)
  //{
	 // if (allCards[i].data()->cardSuit == card::suit::Diamonds)
	 // {
		//  cout << "Diamonds!";
	 // }
	 // if (allCards[i].data()->cardSuit == card::suit::Clubs)
	 // {
		//  cout << "Clubs!";
	 // }
	 // if (allCards[i].data()->cardSuit == card::suit::Hearts)
	 // {
		//  cout << "Hearts!";
	 // }
	 // if (allCards[i].data()->cardSuit == card::suit::Spades)
	 // {
		//  cout << "Spades!";
	 // }

  //}



  ////For checking if arrays are empty
  //int suitcounter;

  ////Until every suit array has been emptied completely
  //while (clubsArray.empty() == false && diamondsArray.empty() == false && heartsArray.empty() == false && spadesArray.empty() == false)
  //{
	 // //Randomly pick a suit - needs to be something to stop it going in to empty arrays
	 // int suitSelector = ((rand() % 4) + 1);
	 // int cardSelector;

	 // //If clubs is selected and clubs isn't empty
	 // if (suitSelector == 1 && clubsArray.empty() == false)
	 // {
		//  //Randomly pick a club
		//  cardSelector = ((rand() % clubsArray.size()) + 1);

		//  //Add selected card to allCards
		//  allCards->push_back(clubsArray[cardSelector]);

		//  //Remove selected card from clubs array
		//  clubsArray.erase(clubsArray.begin()+cardSelector);
	 // }


	 // //If diamonds is selected and diamonds isn't empty
	 // if (suitSelector == 2 && diamondsArray.empty() == false)
	 // {
		//  //Randomly pick a diamond
		//  cardSelector = ((rand() % diamondsArray.size()) + 1);

		//  //Add selected card to allCards
		//  allCards->push_back(diamondsArray[cardSelector]);

		//  //Remove selected card from diamonds array
		//  diamondsArray.erase(diamondsArray.begin() + cardSelector);
	 // }


	 // //If hearts is selected and hearts isn't empty
	 // if (suitSelector == 3 && heartsArray.empty() == false)
	 // {
		//  //Randomly pick a heart
		//  cardSelector = ((rand() % heartsArray.size()) + 1);

		//  //Add selected card to allCards
		//  allCards->push_back(heartsArray[cardSelector]);

		//  //Remove selected card from hearts array
		//  heartsArray.erase(heartsArray.begin() + cardSelector);
	 // }


	 // //If spades is selected and spades isn't empty
	 // if (suitSelector == 4 && spadesArray.empty() == false)
	 // {
		//  //Randomly pick a spade
		//  cardSelector = ((rand() % spadesArray.size()) + 1);

		//  //Add selected card to allCards
		//  allCards->push_back(spadesArray[cardSelector]);

		//  //Remove selected card from spades array
		//  spadesArray.erase(spadesArray.begin() + cardSelector);
	 // }




	 // //Randomly pick a card from the selected suit array
	 // //Add it to allCards / cardstack
	 // //Delete that card from the suit array
  //}


  //Populate allCards
  //for (int i = 0; i < 52; i++)
  //{ 
	 // card c;

	 // c.cardType = card::type::Two;
	 // c.cardSuit = card::suit::Clubs;
	 // allCards->push_back(c);
	 // //cout << i << endl;
  //}

  //for (auto &c : allCards)
  //{
	 // cout << &c << endl; 
  //}

  //cout << endl << allCards->size() << endl;

 /* for (int i = 0; i < allCards.size(); i++)
  {
	  allCards[i].card
  }*/

  //last played card is the highest number in cardStack I think

  //Ranking for when players get out
  vector<player> ranking;

 
  /*if (player gets out) [pseudocode]
  {
	  ranking.push_back(player);
  }*/

  return 0;
}