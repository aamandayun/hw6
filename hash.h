#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

#include <vector>
#include <map>
#include <string>
#include <algorithm>
typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        //translate string of 6 letters into an unsigned long long
        HASH_INDEX_T combined[5] = {0};
        std::vector<std::string> substrings;
        //std::vector<HASH_INDEX_T> result;
        //place zeros in leading position if string is shorter than 6 letters
        if(k.length()==0){
          return 0; 
        }
        int count = 4;

        //break into substrings of 6
        int length = k.length();

        int end = length;

        while(end>0){
          int start = std::max(0, end-6);

          std::string substring = k.substr(start, end-start);
          substrings.push_back(substring);
          end = start;
        }
        if(k.length()<=6){
          std::reverse(substrings.begin(), substrings.end());
        }

        for(std::string s : substrings){
          HASH_INDEX_T w = 0;
          int val = letterDigitToNumber(s[0]);
          //std::cout << "letter: " <<s[0]<< "  val: "<<val<<std::endl;
          w = val;
          for(int i =1; i<s.length();i++){
            val = letterDigitToNumber(s[i]);
            // std::cout << "letter: " <<s[i]<< "  val: "<<val<<std::endl;
            w = 36*w + val;
            // std::cout <<"w: "<<w<<std::endl;
          }

          combined[count]=w;
          count--;
          
        }
        for(int i=0; i<5; i++){
          std::cout << "w[" <<i<<"] = "<<combined[i]<<std::endl;
        }

        //hash the string
        HASH_INDEX_T hk = (rValues[0] * combined[0] +rValues[1] * combined[1] +rValues[2] * combined[2] +rValues[3] * combined[3] +rValues[4] * combined[4]);

        return hk;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //translate each letter into a value between 0 and 35
        //convert upper to lower before mapping
        std::map<char, int> alpha;
        size_t count = 0;
        for(char i='a'; i<='z'; i++){
          alpha.insert(std::make_pair(i, count++));
        }

        for(char c = '0'; c<='9'; c++){
          alpha.insert(std::make_pair(c, count++));
        }

        auto it = alpha.find(tolower(letter));
        if(it != alpha.end()){
          return it->second;
        }

        return 0;


    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
