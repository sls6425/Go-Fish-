// FILE:  player.cpp
//
// This class represents a player in a card game that takes "tricks"
// The "Books" represent a container for holding tricks

#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//default constructor
Player::Player(){
   myName = "No name";
}

//add card to myHand vector
void Player::addCard(Card c){
   myHand.push_back(c);
}

//add pair to myBook vector
void Player::bookCards(Card c1, Card c2){
   myBook.push_back(c1);
   myBook.push_back(c2);
}

//returns true or false based on if there is a pair
//of matching ranks (a book) in a given player's hand
bool Player::checkHandForBook(Card &c1, Card &c2){
   int ranks[13];
   int book = -1;
   
   //fill array w zero
   for(int i = 0; i < 13; i++){
      ranks[i] = 0;
   }
   
   //adds 1 to index of rank every time it occurs
   for(int i=0; i<myHand.size(); i++){
        ranks[myHand[i].getRank()-1]++;
   }
   //finds index to consider a book
   for(int i=0; i<13; i++){
       if(ranks[i] >= 2){
           book = i+1;
           i = 13;
       }
   }  
   bool foundOne = false;
   //parsing thru actual hand
   for(int i = 0; i<myHand.size(); i++){
       //c1 holds one of the cards in the pair
       if(myHand[i].getRank() == book && !foundOne){
           c1= myHand[i];
           foundOne = true;
       }
       //c2 holds the second card pair
       else if(myHand[i].getRank() == book && foundOne){
           c2 = myHand[i];
       }
   }
   //returns if there is a pair or not
   return foundOne;
}

//checks if certain rank in hand
bool Player::rankInHand(Card c) const{
   int rank = c.getRank();
   for(int i = 0; i < myHand.size(); i++){
      if(myHand[i].getRank() == rank){
         return true;
      }
   }
   return false;
}

//uses random variable to select random
//index from current player's hand to request
//from opponent
Card Player::chooseCardFromHand() const{
   srand(time(0));
   int random = (rand() % myHand.size());
   return myHand[random];
}

//Does the player have card c in hand?
bool Player::cardInHand(Card c) const{

   for(int i = 0; i < myHand.size(); i++){
      if(myHand[i].operator==(c)){
         return true;
      }
   }
   return false;
}
 
//removes card from player's hand
//returns removed card upon execution
Card Player::removeCardFromHand(Card c){
   Card toReturn;
   for(int i = 0; i < myHand.size(); i++){
      if(myHand[i].getRank() == (c.getRank())){
         toReturn = myHand[i];
         myHand.erase(myHand.begin() + i);
         return toReturn;
      }
   }
   return toReturn;
}
 
//displays all cards in hand  
string Player::showHand() const{

   string hand = "";
   for(int i = 0; i < getHandSize(); i++){
      hand += (myHand[i].toString() + " ");
   }
   return hand;
}

//displays books and columns of pairs
string Player::showBooks() const{
 
   string book = "";
   for(int i = 0; i < myBook.size(); i++){
        if(i%2 == 0) {
            book += (myBook[i].toString() + "/");
        }
        else{
	    book += (myBook[i].toString() + "\n");
        }
   }
   return book;
}

//return # or cards in a player's hand
int Player::getHandSize() const{
   return myHand.size();
}

//returns number of books (half size of myBook)
int Player::getBookSize() const{
   return (myBook.size()/2);
}   

