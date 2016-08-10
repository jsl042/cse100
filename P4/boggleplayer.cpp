/*
 * Terry Chu tjchu
 * Gunganit Tiwapong gtiwapon
 */

#include "iboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <fstream>

//bool flag indicating that the board is built
bool boardBuilt = 0;

//bool flag indicating that trie (aka the lexicon) is built
bool trieBuilt = 0;

//Function building a lexicon from a vector of strings
void BogglePlayer::buildLexicon(const vector<string>& wordList) {
   BogglePlayer::trie->buildTrie(wordList);
   trieBuilt = 1;
}

/* This function sets and fills a new board rows, columns and 
content specified by the three arguments.*/
void BogglePlayer::setBoard(unsigned int r, unsigned int c,string** diceArray){
   /*if a board has been built, reset all the variables in BogglePlayer
   so that you can rebuild a new board if you want to*/
   if(boardBuilt){
     boardBuilt = 0;
     boardRow = 0;
     boardCol = 0;
     board.clear();
     isUsed.clear();
   }
   
   //assign new rows and columns from input
   BogglePlayer::boardRow = r;
   BogglePlayer::boardCol = c;

   //looping through diceArray, fill in board with 
   //all lowercase words
   for (unsigned int i = 0; i < r; i++) {
      for (unsigned int j = 0; j < c; j++) {
	     board.push_back(makeStringLower(diceArray[i][j]));
       //to note if word already used
	     isUsed.push_back(0);
      }
   }
   //turn on boardBuilt flag in case it's the first time being built
   boardBuilt = 1;
}

/* It returns false if either setBoard() or buildLexicon() have not yet
been called for this BogglePlayer. If they have both been called, it will
return true, after filling the set with all the words that (1) are of at
least the given minimum length, (2) are in the lexicon specified by the most
recent call to buildLexicon(), and (3) can be found by following an acyclic
simple path on the board specified by the most recent call to setBoard().*/
bool BogglePlayer::getAllValidWords(unsigned int minWordLength,
                                    set<string>* words){
   //If both flags are on, then start getting all the valid words
   if(boardBuilt && trieBuilt){
      for(int i = 0; i < BogglePlayer::boardRow; i++) {
        for(int j = 0; j < BogglePlayer::boardCol; j++){
          string word = "";
          
          //call helper function
     	  validBoardSearch(minWordLength,i,j,words,word);
	}
      }
      return 1; //return true because valid word is found
   }
      return 0; //return false otherwise
}

/* This function takes as argument a const string passed
by reference, and determines whether it be found in the
lexicon specified by the most recent call to
buildLexicon(). The function returns true if the word
is in the lexicon, and returns false if it is not in
the lexicon or if buildLexicon() has not yet been called.*/
bool BogglePlayer::isInLexicon(const string& word_to_check) {
   //if trie is built, find the words if not, return false
   if (trieBuilt)
      return trie->find(word_to_check);

    return 0;
}

/*this function takes as argument a string passed by reference.
It determines whether the string can be found by following 
an acyclic simple path on the board specified by the most 
recent call to setBoard(). If it is possible to find the 
word in the current board, the function returns vector with 
integers specifying the locations of dice that can be used 
to form the word, in the order that spells the word.*/
vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
   vector<int> locs;
   string diceString;
   string newWord = makeStringLower(word_to_check);

   //if the board has not been made return the empty vector
   if (boardBuilt == 1) {
      for (int i = 0; i < BogglePlayer::boardRow; i++){
 	for (int j = 0; j < BogglePlayer::boardCol; j++){
          //call helper function. if returns true, return the locations
          if(searchBoard(newWord,i,j,locs))
	    return locs;
        }
      }
   }     
   return locs;
}

//Since getCustomBoard is an optional method, it's not fully implemented.
void BogglePlayer::getCustomBoard(string** &new_board,
                            unsigned int *r, unsigned int *c){
  /*Made the arguments equal to itself so that there wouldn't warnings 
  about unused parameters.*/
  new_board = new_board;
  r = r;
  c= c;

  return; //return nothing to end this method
}


/* Helper recursive method to find if word is on the board or not.*/
bool BogglePlayer::searchBoard(const string& word, int r,
                              int c, vector<int>& locs){
  int index;
  //if invalid row or column boundaries, set the index value to -1
  if(c < 0 || r < 0 || r >= boardRow
      || c >= boardCol)
    index= -1;
   
  else
    index = r*boardCol+c;
   
   //if the string has been used or the index is not within the board
   //return false
   if(index < 0 || index > (int) board.size())
      return 0;

   if(isUsed[index])
      return 0;
   
   //dicestring is the word at board's location index
   string diceString = board[index];
   int diceLength = (int)diceString.length();
   int wordLength = (int)word.length();

   //if the dicelength is longer it can not be the end, return false
   if(diceLength > wordLength)
      return 0;

   if(word.substr(0,diceLength) != diceString)
      return 0;
   

   //insert index into locations, vector returned has the path word made in
   locs.push_back(index);

   //if the dicelength and wordlength == then word is found
   //return true
   if(diceLength == wordLength)
      return 1;
   
   //indicate used at the index
   isUsed[index] = 1;

   //take off the part of the was found in the string
   string parsed = word.substr(diceLength);

   //the values added to find the adjancent nodes
   static int adj[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0,
                            1, 1, -1, 1, 0, 1, 1};
   for(int i = 0; i < 8; i++){
      //call recursion helper method
      bool recursion = searchBoard(parsed, r + adj[i][0],
                            c + adj[i][1], locs);
      //if recursion is true, then reset the used index and return true;
      if(recursion){
         isUsed[index] = 0;
         return 1;
      }
   }

   //reset the index as its looked through, pop back so location has no index
   isUsed[index] = 0;
   locs.pop_back();
   return 0;
}

/*Helper method to return a string in lowercase form*/
string BogglePlayer::makeStringLower(string word){
   int wordLength = (signed int)word.length();
   string lowerCased;

   //for loop going each letter in the word argument and lowercase it
   int i;
   for(i = 0; i < wordLength; i++){
      lowerCased+= tolower(word.at(i));
   }
   return lowerCased;
}

/*Helper method that determines if the word is a prefix of another word*/
bool BogglePlayer::determinePrefix(string& prefix){
   //call the helper method prefixFind in Tree class
   return trie->prefixFind(prefix);
}

/*Helper method to determines what valid words exist*/
void BogglePlayer::validBoardSearch(int length, int row, int col,
                                   set<string>* words, const string& word){
   int index;
   if(col < 0 || row < 0 || row >= boardRow
      || col >= boardCol){
      index= -1;
   }
   else 
      index = row * boardCol + col;
   
   //if the index is within parameters and the index has not been used
   if(index >= 0 && index < (signed int)board.size() && !isUsed[index]){
      //gets string from dice, changes the boolean to true, append string
      string diceString = board[index];
      isUsed[index] = 1;
      string result = word + diceString;
      int wordLength = (int)result.length();
      static int adj[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0,
                            1, 1, -1, 1, 0, 1, 1};

      //if the length of word not long enough, keep adding
      if(wordLength < length){
         //if the word is a prefix, continuing searching
         //else reset index and leave method
         if(determinePrefix(result)){
            int i;
            //go through all adjancent indexes and recurse
            for (i = 0; i < 8; i++){
               validBoardSearch(length,row + adj[i][0],
                               col + adj[i][1],words,result);
            }
         }
         else
            isUsed[index] = 0;
      }

      else{
         //if length is long enough, check lexicon
         if(isInLexicon(result))
            words->insert(result);

         //if word is not a prefix, reset index to false
         if(determinePrefix(result)){
            int i;
            //go through all adjacent indices
            for(i = 0; i < 8; i++){
               validBoardSearch(length,row + adj[i][0],
                                col + adj[i][1],words,result);
            }
         }
         else
            isUsed[index] = 0;
      }
      //reset the index in case it has not been
      if(row < 0 || col < 0 || row >= boardRow
      || col >= boardCol)
         index= -1;
      
      else
         index = row*boardCol+col;
      
      isUsed[index] = 0;
   }
}

