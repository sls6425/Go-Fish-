// FILE: card.cpp
//
// Savannah Schmidt
// UTEID: sls6425
//
// This class represents a playing card, i.e., "ace of spades"
// a Card is constructed from a rank (int in range 1..13)
// and a suit (Card::spades, Card::hearts, Card::diamonds,
// Card::clubs)
//
// Cards should be created by a Deck (see deck.h), a Deck returns
// good cards
// The function toString() converts a card to a string, e.g., to print
//
// Accessor functions include
//
// int GetRank()      -- returns 1, 2, ..., 13 for ace, two, ..., king
//
// bool SameSuitAs(c) -- returns true if same suit as Card c
//
// string suitString() -- returns "s", "h", "d" or "c"
//
// Note that the Ace is represented by 1 and the King by 13

#include "card.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


//constructors
Card::Card(){
   //default ace of spades
   mySuit = Card::spades;
   myRank = 1;
}

Card::Card(int rank, Suit s){
   mySuit = s;
   myRank = rank;
}

//methods
//prints out card
string Card::toString() const{
   return(rankString(myRank) + suitString(mySuit));
}

//is this card the same suit as c?
bool Card::sameSuitAs(const Card& c) const{
   return(this->mySuit == c.mySuit);
}

//return rank as int (1-13)
int Card::getRank() const{
   return myRank;
}


//return suit as string
string Card::suitString(Suit s) const{
   string suits;

   switch(s){
      case spades:
         suits = "s";
         break;
      case hearts:
         suits = "h";
         break;
      case diamonds:
         suits = "d";
         break;
      case clubs:
         suits = "c";
         break;
   }

   return suits;
}


//return rank as string
string Card::rankString(int rank) const{
   const int cardRanks = 13;
   string ranks[cardRanks] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10","J", "Q", "K"};
   return ranks[rank-1];
}


//boolean operators
//equal to
bool Card::operator == (const Card& rhs) const{
   return(toString() == rhs.toString());
} 

//not equal to
bool Card::operator != (const Card& rhs) const{
   return(!(toString() == rhs.toString()));
}

//output
ostream& operator << (ostream& out, const Card& c){
   out << c.toString();
   return out; 
}

