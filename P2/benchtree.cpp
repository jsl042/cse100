/*
 * Terry Chu tjchu
 *  Patrick Nguyen phn031
*/

#include "BST.hpp"
#include "RST.hpp"
#include "countint.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <vector>
#include <cmath>


  int main(int argc, char* argv[])
  {
    bool fBst = false; // BST Flag
    bool bRst = false; // RST Flag
    bool fSet = false; // Set Flag
    bool fSort = false; // Sorted or Shuffled

    if (argc != 5)
    {
      (void)fprintf(stderr, " ! There is an wrong number of arguments\n");
      return 0;
    }
    
    int numOfRuns = atoi(argv[4]); // Number of runs

    int bigSize = atoi(argv[3]); // Max size of insertions  //Max = big
	// Removes whitespace
 	
	// Make sure this is a size and number of runs != 0
    if( bigSize <= 0 )
    {
      (void)fprintf(stderr, " The maximum cannot be less than 0\n");
      return 0;
    }
    if( numOfRuns <= 0 )
    {
      (void)fprintf(stderr, " The numOfRuns cannot be less than 0\n");
      return 0;
    }
	
	// Objective
	std::cout << " # Benchmarking average number of comparisons"
	<< " for successful find" << std::endl; 

	// Determines whether or not bst, rst, or set was entered
	if (strcmp(argv[1],("bst")) == 0)
	{
		std::cout << " # Data structure: bst" << std::endl;
		fBst = true;
	}
	else if (strcmp(argv[1],"set") == 0)
	{
		std::cout << " # Data structure: set" << std::endl;
		fSet = true;
	}

	else if (strcmp(argv[1],("rst")) == 0)
	{
		std::cout << " # Data structure: rst" <<std::endl;
		bRst = true;
	}
	else
	{
		(void)fprintf(stderr, "! Not correct tree structure. Exiting program\n");
		return 0;
	}

	// Determines whether or not insertion should be sorted or shuffled
	if ((strcmp(argv[2],"shuffled")) == 0)
	{
		std::cout << " # Data: shuffled" << std::endl;
		fSort = false;
	}
       	else if (strcmp(argv[2],"sorted") == 0)
	{
		std::cout << " # Data: sorted" << std::endl;
		fSort = true;
	}
 	else
	{
		(void)fprintf(stderr, "! Not correct order\n");
		return 0;
	}
	
	// Basic info
	std::cout << " # N is powers of 2, minus 1, from 1 to " << bigSize << std::endl;
        std::cout << " # Averaging over " << numOfRuns << " runs for each N" << std::endl;
        std::cout << " #" << std::endl;
        std::cout << " # N \t avgcomps \t stdev" << std::endl;
	
	std::vector<int> vSize;  //size = vSize
	int temp = 1;  //coutner = temp
	int now = pow(2,temp)-1;  //cursize = now
	while ( now <= bigSize)
	{
	  temp++;
          vSize.push_back(now);
          now = pow(2,temp)-1;
	}
	
	if (fBst)
	{
	  for(unsigned int i = 0; i < vSize.size(); i++)
	  {
	  double avgComps = 0;  // Average # of comparisons  //avg = avgComps
	  double std_dev = 0; // Standard Deviation
	  double avgSquares = 0;
		
	  for (int j = 0; j < numOfRuns; j++)
	  {
	    std::vector<countint> v; // Creating the vector with all numbers
	    v.clear();  // Clear the vector
	    for(int k = 0; k < vSize[i]; k++)
	    {
     	      v.push_back(k); 
	    }
	    if(!fSort) // If user wanted it shuffled, shuffle
	    {
	      std::random_shuffle(v.begin(), v.end());
	    }
	    BST<countint> t;
	    std::vector<countint>::iterator beg = v.begin();
	    std::vector<countint>::iterator end = v.end();
	    for(beg=v.begin();beg != end; beg++)
	    {
	      t.insert(*beg);  // add
	    }
	    countint::clearcount();
	    for(beg=v.begin();beg != end; beg++)
	    {
	      t.find(*beg); // Find
	    }

	    avgComps = avgComps + countint::getcount()/((double)vSize[i]);
	    avgSquares = avgSquares + pow(countint::getcount()/((double)vSize[i]),2); 
	  }
			
          avgComps = avgComps / numOfRuns;
	  avgSquares = avgSquares / numOfRuns;
	  std_dev = sqrt(abs(avgSquares-pow(avgComps,2)));
          std::cout << std::setw(6) << vSize[i]; 
          std::cout << std::setw(14) << avgComps;
          std::cout << std::setw(14) << std_dev << std::endl;
          }
	}
 	else if (bRst)
	{
	  for(unsigned int i = 0; i < vSize.size(); i++)
	  {
	    double avgComps = 0;  // Average # of comparisons
	    double std_dev = 0; // Standard Deviation
            double avgSquares = 0;
		
	    for (int j = 0; j < numOfRuns; j++)
	    {

	      std::vector<countint> v; // Creating the vector with all numbers
	      v.clear();  // Clear the vector

	      for(int k = 0; k < vSize[i]; k++)
	      {
     	        v.push_back(k); 
	      }

	      if(!fSort) // If user wanted it shuffled, shuffle
	      {
	        std::random_shuffle(v.begin(), v.end());
	      }

	      RST<countint> t;
	      std::vector<countint>::iterator beg = v.begin();
	      std::vector<countint>::iterator end = v.end();

	      for(beg=v.begin();beg != end; beg++)
	      {
	        t.insert(*beg);  // add
	      }

	      countint::clearcount();
	      for(beg=v.begin();beg != end; beg++)
	      {
	        t.find(*beg); // Find
	      }

	      avgComps = avgComps + countint::getcount()/((double)vSize[i]);
	      avgSquares = avgSquares + pow(countint::getcount()/((double)vSize[i]),2); 
	    }

	    avgComps = avgComps/numOfRuns;
	    avgSquares = avgSquares/numOfRuns;

	    std_dev = sqrt(abs(avgSquares-pow(avgComps,2)));
   	    std::cout << std::setw(6) << vSize[i]; 
	    std::cout << std::setw(14) << avgComps;
	    std::cout << std::setw(14) << std_dev << std::endl;
          }
	}
	else if (fSet)
	{
	  for(unsigned int i = 0; i < vSize.size(); i++)
          {
	    double avgComps = 0;  // Average # of comparisons
	    double std_dev = 0; // Standard Deviation
	    double avgSquares = 0;
		
	    for (int j = 0; j < numOfRuns; j++)
	    {
	      std::vector<countint> v; // Creating the vector with all numbers
	      v.clear();  // Clear the vector

	      for(int k = 0; k < vSize[i]; k++)
	      {
     	        v.push_back(k); 
	      }

	      if(!fSort) // If user wanted it shuffled, shuffle
	      {
	        std::random_shuffle(v.begin(), v.end());
	      }

	      std::set<countint> t;
	      std::vector<countint>::iterator beg = v.begin();
	      std::vector<countint>::iterator end = v.end();

	      for(beg=v.begin();beg != end; beg++)
	      {
	        t.insert(*beg);  // add
	      }
	      countint::clearcount();
	      for(beg=v.begin();beg != end; beg++)
	      {
	        t.find(*beg); // Find
	      }

	      avgComps = avgComps + countint::getcount()/((double)vSize[i]);
	      avgSquares = avgSquares + pow(countint::getcount()/((double)vSize[i]),2); 
	    }
	    avgComps = avgComps/numOfRuns;
	    avgSquares = avgSquares/numOfRuns;

	    std_dev = sqrt(abs(avgSquares-pow(avgComps,2)));
	    std::cout << std::setw(6) << vSize[i]; 
	    std::cout << std::setw(14) << avgComps;

	    std::cout << std::setw(14) << std_dev << std::endl;
	    }
	}
	return 0;
  }
