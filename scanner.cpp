#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 10
//====================================================

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: TONY
// ** RE:
bool word_dfa(string s)
{
	int state = 0;
	int charpos = 0;
	//cout << "Inside of the myword function" << endl;
	while (s[charpos] != '\0')
	{
		if (state == 0 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
			state = 1;
		else
		if (state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r'))
			state = 2;
		else
		if (state == 0 && (s[charpos] == 'c'))
			state = 5;
		else
		if (state == 0 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
			state = 6;
		else
		if (state == 0 && (s[charpos] == 's'))
			state = 4;
		else
		if (state == 0 && (s[charpos] == 't'))
			state = 3;
		else
		if (state == 1 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
			state = 1;
		else
		if (state == 1 && (s[charpos] == 'n'))
			state = 0;
		else
		if (state == 1 && (s[charpos] == 't'))
			state = 3;
		else
		if (state == 1 && (s[charpos] == 's'))
			state = 4;
		else
		if (state == 1 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'p' || s[charpos] == 'r'))
			state = 2;
		else
		if (state == 1 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
			state = 6;
		else
		if (state == 1 && (s[charpos] == 'c'))
			state = 5;
		else
		if (state == 6 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
			state = 1;
		else
		if (state == 3 && (s[charpos] == 's'))
			state = 6;
		else
		if (state == 4 && (s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'E' || s[charpos] == 'i' || s[charpos] == 'I' || s[charpos] == 'o' || s[charpos] == 'u'))
			state = 1;
		else
		if (state == 3 && (s[charpos] == 's'))
			state = 6;
		else
		if (state == 4 && (s[charpos] == 'h'))
			state = 6;
		else
		if (state == 5 && (s[charpos] == 'h'))
			state = 6;
		else
		if (state == 2 && (s[charpos] == 'y'))
			state = 6;
		else
		{
			return false;
		}

		charpos++;
	}//end of while
	 // where did I end up????

	if (state == 0 || state == 1)
		return true;  // end in a final state
	else
		return false;
}

// ** Done by: Cam Tran

bool period(string s) {
  int state = 0;
  int charpos = 0;
    
  while (s[charpos] != '\0') {
    if (state == 0 && s[charpos] == '.')
      state = 1;
    else
      return (false);
    charpos++;
  } //end of while
    
    // where did I end up????
  if (state == 1)
    return(true);  // end in a final state
  else
    return(false);
}


// Scanner processes only one word each time it is called
// ** Done by: Cam Tran/Brad
int scan(tokentype& a, string& w, ifstream& fin)
{
  fin >> w;
  if (w == "eofm")
    {
      return 0;
    }

    
  if (word_dfa(w)) {
    char lastChar = w[w.length() - 1]; //sets a variable for the last letter to check if WORD1 or WORD2
        
    //checks reserved words
    if (w == "masu")
      a = VERB;
    else if (w == "masen")
      a = VERBNEG;
    else if (w == "mashita")
      a = VERBPAST;
    else if (w == "masendeshita")
      a = VERBPASTNEG;
    else if (w == "desu")
      a = IS;
    else if (w == "deshita")
      a = WAS;
    else if (w == "o")
      a = OBJECT;
    else if (w == "wa")
      a = SUBJECT;
    else if (w == "ni")
      a = DESTINATION;
    else if (w == "watashi" || w == "anata" || w == "kare" || w == "sore")
      a = PRONOUN;
    else if (w == "mata" || w == "soshite" || w == "shikashi" || w == "dakara")
      a = CONNECTOR;
    else if ((lastChar == 'I') || (lastChar == 'E')) //checks if it ends in capital I or E for WORD2
      a = WORD2;
    else
      a = WORD1;
    return 1;
  }
  //runs the period dfa
  else if (period(w)) {
    a = PERIOD;
    return 1;
  }
  else {
    a = ERROR;
    return 1;
  }
    
}//the end
