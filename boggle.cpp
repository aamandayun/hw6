#ifndef RECCHECK
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <iomanip>
#include <fstream>
#include <exception>
#endif

#include "boggle.h"

std::vector<std::vector<char> > genBoard(unsigned int n, int seed)
{
	//random number generator
	std::mt19937 r(seed);

	//scrabble letter frequencies
	//A-9, B-2, C-2, D-4, E-12, F-2, G-3, H-2, I-9, J-1, K-1, L-4, M-2, 
	//N-6, O-8, P-2, Q-1, R-6, S-4, T-6, U-4, V-2, W-2, X-1, Y-2, Z-1
	int freq[26] = {9,2,2,4,12,2,3,2,9,1,1,4,2,6,8,2,1,6,4,6,4,2,2,1,2,1};
	std::vector<char> letters;
	for(char c='A'; c<='Z';c++)
	{
		for(int i=0;i<freq[c-'A'];i++)
		{
			letters.push_back(c);
		}
	}
	std::vector<std::vector<char> > board(n);
	for(unsigned int i=0;i<n;i++)
	{
		board[i].resize(n);
		for(unsigned  int j=0;j<n;j++)
		{
			board[i][j] = letters[(r() % letters.size())];
		}
	}
	return board;
}

void printBoard(const std::vector<std::vector<char> >& board)
{
	unsigned int n = board.size();
	for(unsigned int i=0;i<n;i++)
	{
		for(unsigned int j=0;j<n;j++)
		{
			std::cout << std::setw(2) << board[i][j];
		}
		std::cout << std::endl;
	}
}

std::pair<std::set<std::string>, std::set<std::string> > parseDict(std::string fname)
{
	std::ifstream dictfs(fname.c_str());
	if(dictfs.fail())
	{
		throw std::invalid_argument("unable to open dictionary file");
	} 
	std::set<std::string> dict;
	std::set<std::string> prefix;
	std::string word;
	while(dictfs >> word)
	{
		dict.insert(word);
		for(unsigned int i=word.size()-1;i>=1;i--)
		{
			prefix.insert(word.substr(0,i));
			
		}
	}
	prefix.insert("");
	return make_pair(dict, prefix);
}

std::set<std::string> boggle(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board)
{
	std::set<std::string> result;
	for(unsigned int i=0;i<board.size();i++)
	{
		for(unsigned int j=0;j<board.size();j++)
		{
			boggleHelper(dict, prefix, board, "", result, i, j, 0, 1);
			boggleHelper(dict, prefix, board, "", result, i, j, 1, 0);
			boggleHelper(dict, prefix, board, "", result, i, j, 1, 1);
		}
	}
	
	return result;
}


//recursively search for words in the given board
//r (row) and c (col) are current position on the board
//dr and dc st the search direction
//do not need to change dr or dc as you search, but use them to set r and c as you recurse to the next position
//INSERT ONLY THE LONGEST WORD FOUND INTO RESULT set
//return true if inserted the longest word
bool boggleHelper(const std::set<std::string>& dict, const std::set<std::string>& prefix, const std::vector<std::vector<char> >& board, 
								   std::string word, std::set<std::string>& result, unsigned int r, unsigned int c, int dr, int dc)
{
//add your solution here!
//base case
//check if out of bounds? or if reached end of board?
if(r>=board.size() || c >=board[0].size() || r<0 || c<0){
  if(dict.count(word)){
    result.insert(word);
    return true;
  }else{
    return false;
  }
}

	word += board[r][c];

  //std::cout<<"adding this letter: "<<board[r][c]<<" to this word: "<<word<<std::endl;


	r+=dr;
	c+=dc;
	if(!prefix.count(word)){
    if(dict.count(word)){
      result.insert(word);
      return true;
    }
    //check if word is a substring of another word?
		return false;
	}

	// if(dict.count(word)){
  //   std::string temp = word;
  //   bool longestFound = boggleHelper(dict, prefix, board, word, result, r, c, dr, dc);
  //   if(!longestFound){

  //     result.insert(word);
  //     return true;
  //   }
	// 	//result.insert(word);
	// }

  // bool longest = false;
  // longest |= boggleHelper(dict, prefix, board, word, result, r, c, dr, dc);
  // if(!longest){
  //   return false;
  // }

  if(boggleHelper(dict, prefix, board, word, result, r, c, dr, dc)){
    return true;
  }else{
    if(dict.count(word)){
      result.insert(word);
      return true;
    }else{
      return false;
    }
  }



	// if(r>=board.size() || c>= board[0].size() || r<0||c<0){
	// 	return true;
	// }

	return boggleHelper(dict, prefix, board, word, result, r, c, dr, dc);
}



/*

word += board[r][c];

if(dict.count(word)){
		result.insert(word);
}
//checking prefixes?
if(!prefix.count(word)){
	return false;
}

if(r + dr>=board.size() || c + dc>=board[0].size()){
	return false;
	//return boggleHelper(dict, prefix, board, word, result, r+dr, c+dc, dr, dc);
}else{
	bool longestFound = boggleHelper(dict, prefix, board, word, result, r+dr, c+dc, dr, dc);
	if(longestFound){
		if(!prefix.count(word)){
			std::cout<<"prefix word: "<< word<<std::endl;
			result.insert(word);
		}
			
	}
  //return boggleHelper(dict, prefix, board, word, result, r+dr, c+dc, dr, dc);
}

return true;


}
*/


//deleting now
