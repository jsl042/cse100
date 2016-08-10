/*
 * Terry Chu tjchu
 * Gunganit Tiwapong gtiwapon
 *
 */

#include "iboggleplayer.h"
#include "boggleutil.h"
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using std::vector;
using std::set;
using std::string;

class BogglePlayer: public IBogglePlayer{
   private:
      Tree* trie; //ternary trie to contain the words
      int boardRow; //num of rows on board
      int boardCol; //num of cols on board
      vector<string> board; //vector containing the words on the board
      vector<bool> isUsed; //vector indicating the words that are visited

   public:
      //constructor for BogglePlayer
      BogglePlayer(){
         trie= new Tree();
      }

      //Methods implemented for P4 assignment
      void buildLexicon(const vector<string>& wordList);
      void setBoard(unsigned int rows, unsigned int cols, string ** diceArray);
      bool getAllValidWords(unsigned int minWordLength, set<string>* words );
      bool isInLexicon(const string& word_to_check);
      vector <int> isOnBoard(const string& word_to_check);
      void getCustomBoard(string** &newBoard, unsigned int *r,unsigned int *c);

      //Helper methods
      string makeStringLower(string word);
      void validBoardSearch(int length, int r, int c,
                            set<string>* words, const string& word);
      bool determinePrefix(string& prefix);
      bool searchBoard(const string& word,int r,int c,
                       vector <int>& loc);


      //destructor method
      ~BogglePlayer(){
         if(trie->root)
            trie->destructor(trie->root);
         delete trie;
         trie=0;
      }

};
