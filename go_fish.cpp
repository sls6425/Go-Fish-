// FILE: go_fish.cpp

/* Savannah Schmidt
 * UT EID: sls6425 
 * email address: savannah.schmidt@utexas.edu
 * section ID: 16015
 */

// 
// Driver to implement a game of Go Fish
// between TWO PLAYERS
// 
// Names can be changed within the main function
//
// Fall 2019
// 11/11/2019
// 



#include <iostream>	//provides cout and cin
#include <cstdlib>	//provides EXIT_SUCCESS
#include <fstream>
#include <ctime>
#include "card.h"
#include "player.h"
#include "deck.h"


#define HAND_SIZE 7	//7 cards per hand for 2 players

using namespace std;



//prototype, defined under main()
void dealHand(Deck &d, Player &p, int numCards);



//*********************************main*********************************

int main(){

    //file to store results
    ofstream file;
    file.open("gofish_results.txt");
    
    //creating players
    Player p1("Drake");
    Player p2("Josh");
    
    //create and shuffle deck
    Deck d;
    file << "Before shuffle: " << endl << endl << d.toString() << endl;
    d.shuffle();
    file << endl << "After shuffle: " << endl << endl << d.toString() << endl;
    
    //deal cards
    dealHand(d, p1, HAND_SIZE);
    dealHand(d, p2, HAND_SIZE);
    
    //write to file   
    file << endl << p1.getName() << "\'s initial hand : " << p1.showHand() << endl;
    file << endl << p2.getName() << "\'s initial hand : " << p2.showHand() << endl;
    
    //creating Card objects
    Card c1;
    Card c2;

    //figuring out who will go first
    Player current = p1;
    Player next = p1;

    //random start
    srand(time(0));
    if(rand() % 2){
       next = p2;
    }
    else{
       current = p2;
    }


/*
    file << endl << "                      Before the game starts, each player may book any pairs from their initial hands, if they have any." << endl << endl;

    //checking for pairs in initially dealt hand
    if(current.checkHandForBook(c1, c2)){
       current.bookCards(c1, c2);
       current.removeCardFromHand(c1);
       current.removeCardFromHand(c2);
       file << current.getName() << " books their " << c1.rankString(c1.getRank()) << "\'s." << endl << endl;
    }
    else{
       file << current.getName() << " has no initial pairs." << endl << endl;
    }

    if(next.checkHandForBook(c1, c2)){
       next.bookCards(c1, c2);
       next.removeCardFromHand(c1);
       next.removeCardFromHand(c2);
       file << next.getName() << " books their " << c1.rankString(c1.getRank()) << "\'s." << endl << endl;
    }
    else{
       file << next.getName() << " has no initial pairs." << endl << endl;
    }

*/

    file << endl <<  "-------------------------------------------------- GAME START --------------------------------------------------" << endl;
    file << endl << current.getName() << " will go first!" << endl << endl; 
  

    //play until all cards have been paired
    while((current.getBookSize() + next.getBookSize()) < 26){

     //  file << endl << "Cards remaining in deck: " << d.size() << endl;
     //  file << current.getName() << "\'s hand: " << current.showHand() << endl << endl;
       file << current.getName() << "\'s turn:" << endl;
       //if player is out of cards, try to draw from top of deck
       if(current.getHandSize() == 0){
       file << current.getName() << " has no more cards! Draws the ";
          if(d.size() > 0){
	     Card temp1 = d.dealCard();
	     current.addCard(temp1);
	     file << temp1.toString() << " from deck. Swap turns." << endl;
             file << "Cards remaining in deck: " << d.size() << endl << "---------------------------------------------------"<< endl;
          }
          else{
             file << "There are no more cards in the deck! Swap turns." << endl << "---------------------------------------------------"<< endl;
          }
	  //swap players around for next turn
          Player temp = next;
          next = current;
          current = temp;
       }
       //if player has cards in hand
       else{
	  //book any pairs if there are some
	  if(current.checkHandForBook(c1, c2)){
	     current.bookCards(c1, c2);
             current.removeCardFromHand(c1);
             current.removeCardFromHand(c2);

	     file << current.getName() << " books the " << c1.rankString(c1.getRank()) << "\'s." << endl << "---------------------------------------------------"<< endl;
          }
	  
	  //regardless of if there were previous pairs
          //request card from opponent
          //if they currently have cards
	  if(current.getHandSize() > 0){
	     Card request = current.chooseCardFromHand();
	     file << current.getName() << " asks - Do you have a " << request.rankString(request.getRank()) << "?" << endl;
	     //if they have what they asked for, write to file
             if(next.rankInHand(request)){
		//remove it from opponent's hand
		Card booked = next.removeCardFromHand(request);
		//create book of request and booked card
		current.bookCards(request, booked);
		//remove the request card
		current.removeCardFromHand(request);
		//Joe says - Yes. I have a 4s.
		file << next.getName() << " says - Yes. I have a " << booked.toString() << "." << endl;
		//Jane books the 4's.
		file << current.getName() << " books the " + request.rankString(request.getRank()) << "\'s" << "." << endl << "---------------------------------------------------"<< endl;
	     }
             //if they don't have one
	     else{
		//Joe says - Go Fish!
		file << next.getName() << " says - Go Fish!" << endl;
		//if there are still cards left in deck
		if(d.size() > 0){
		   //random card from deck
		   Card draw = d.dealCard();
		   //add it to current player's hand
		   current.addCard(draw);
		   file << current.getName() << " draws the " << draw.toString() << "." << endl;
                   file << "Cards remaining in deck: " << d.size() << endl << "---------------------------------------------------"<< endl;

		}
		else{
		   file << "There are no more cards in the deck! Swap turns." << endl << "---------------------------------------------------"<< endl;
		}
		//swap turns
		Player temp = next;
		next = current;
		current = temp;
	     }
          }
       }

    }
   file << endl << endl << "All the cards have been booked, lets see who won... " << endl << endl;

   file << endl << current.getName() << " has the following " << current.getBookSize() << " books: "<< endl << current.showBooks() << endl;
   file << endl << next.getName() << " has the following " << next.getBookSize() << " books: " << endl << next.showBooks() << endl;
 
   //tie?
   if(current.getBookSize() == next.getBookSize()){
      file << "It's a tie!" << endl << endl;
      file << "------------------------------------------------ GAME OVER -------------------------------------------------" << endl << endl;    
      file.close();
      return EXIT_SUCCESS;
   }
   else{
 
      Player winner;
      //if opposite player wins
      if(next.getBookSize() > current.getBookSize()){
         winner = next;
      }
      else{
         winner = current;
      }
      //otherwise default is current player wins
      file << endl <<  winner.getName() << " wins!" << endl << endl;

      file << "------------------------------------------------ GAME OVER -------------------------------------------------" << endl << endl;
      file.close();
      return EXIT_SUCCESS;  
   }
}


//given in starter file
void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}
  
