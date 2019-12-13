// FILE: deck.cpp
// 
// this class respresents a deck of cards
// When a Deck is constructed, it contains 52 cards
// in a "regular" order (aces, twos, threes, ... , kings)
//
// Shuffling a deck makes it consist of 52 cards in a random order
//
// dealCard() returns a card from the deck and decreases the
// number of cards in the deck (returned by size())
// The idea is that after shuffling, calling dealCard() 52 times
// returns each card in the deck after shuffling.
//
// Calling shuffle again replenishes the deck with 52 cards.

#include "deck.h"

using namespace std;


//constructor - create entire deck and leave sorted
//ascending rank separated by suit
//spades -> clubs -> hearts - diamonds
Deck::Deck(){
   myIndex = 0;

   Card toAdd;
   //SPADES
   for(int i = 1; i <= 13; i++){
      toAdd = Card(i, Card::spades);
      myCards[i-1] = toAdd;
   }

   //CLUBS
   for(int i = 1; i <= 13; i++){
      toAdd = Card(i, Card::clubs);
      myCards[i+12] = toAdd;
   }

   //HEARTS
   for(int i = 1; i <= 13; i++){
      toAdd = Card(i, Card::hearts);
      myCards[i+25] = toAdd;
   }

   //DIAMONDS
   for(int i = 1; i <= 13; i++){
      toAdd = Card(i, Card::diamonds);
      myCards[i+38] = toAdd;
   }

}


//print out whole deck
string Deck::toString(){
   string toReturn = "";
   for(int i = 0; i < this->size(); i++){
      toReturn += (myCards[i].toString() + " ");
   }
   return toReturn;
}


//random order
void Deck::shuffle(){
   //initialize seed
   srand(time(0));

   //for length of array (52)
   for(int i = 0; i < this->size(); i++){
      //random num
      int first = (i + (rand()%(52 - i)));
      //swap
      Card temp = myCards[first];
      myCards[first] = myCards[i];
      myCards[i] = temp;
   }
   for(int j = 0; j < this->size(); j++){
      //random num
      int second = (j + (rand()%(52 - j)));
      //swap
      Card temp2 = myCards[second];
      myCards[second] = myCards[j];
      myCards[j] = temp2;
   }
}


//deal top card
Card Deck::dealCard(){
   myIndex++;
   return myCards[myIndex-1];
}


//return size of remaining deck
int Deck::size() const{
   return(52-myIndex);
}
