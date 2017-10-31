#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 10
//=====================================================

enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM };

// ** Done by:*************************** TONY *****************************
bool vowel(char letter)
{
  const char vow[] = {'a','e','i','o','u','I','E'};
  for(int i = 0; i < 7; i++)
    {
      if(letter == vow[i]) //if the char is in the array
	return true;
    }
  return false;
}
// ** Done by:*************************** TONY *****************************
bool cons1(char letter)
{
  const char cons[] = {'b','g','h','k','m','n','p','r'};
  for(int i = 0; i < 8; i++)
    {
      if(letter == cons[i]) //if the char is in the array
	return true;
    }
  return false;
}
// ** Done by:*************************** TONY *****************************
bool cons2(char letter)
{
  const char cons[] = {'d','j','w','y','z'};
  for(int i = 0; i < 5; i++)
    {
      if(letter == cons[i]) //if the char is in the array
	return true;
    }
  return false;
}
// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by:*************************** TONY *****************************
// ** RE:
bool word_dfa(string s)
{
  string state = "q0"; //starting state
  int charpos = 0; //char index
    
  cout << "Trying the word dfa machine " << endl;
    
  while (s[charpos] != '\0') //loops through each char in string
    {
      cout << "current state: " << state << endl;
      cout << "character: " << s[charpos] << endl;
        
      //the following statements set the states
        
      if (state == "q0" || state == "q0q1")
        {
	  if (vowel(s[charpos]))
	    state = "q0q1";
	  else if (state == "q0q1" && s[charpos] == 'n')
	    state = "q0";
	  else if (cons1(s[charpos]))
	    state = "q2q5";
	  else if (cons2(s[charpos]))
	    state = "q5";
	  else if (s[charpos] == 't')
	    state = "q3q5";
	  else if (s[charpos] == 's')
	    state = "q4q5";
	  else if (s[charpos] == 'c')
	    state = "q4";
	  else
	    return(false);
        }
        
      else if (state == "q2q5")
        {
	  if (vowel(s[charpos]))
	    state = "q0q1";
	  else if (s[charpos] == 'y')
	    state = "q5";
        }
        
      else if (state == "q3q5")
        {
	  if (vowel(s[charpos]))
	    state = "q0q1";
	  else if (s[charpos] == 's')
	    state = "q5";
        }
        
      else if (state == "q4q5")
        {
	  if (vowel(s[charpos]))
	    state = "q0q1";
	  else if (s[charpos] == 'h')
	    state = "q5";
        }
        
      else if (state == "q5")
        {
	  if (vowel(s[charpos]))
	    state = "q0q1";
        }
        
      else if (state == "q4")
        {
	  if (s[charpos] == 'h')
	    state = "q5";
        }
        
      else
        {
	  return(false);
        }
      charpos++;
    }//end of while
    
  if (state == "q0" || state == "q0q1")
    return(true);  // end in a final state
  else
    return(false);
}
// ** Add the PERIOD DFA here ********************** DONE **********************
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


// ** Update the tokentype to be WORD1, WORD2, PERIOD and ERROR.



// ** Need the lexicon to be set up here (to be used in Part C)
// ** Need the reservedwords list to be set up here
// ** Do not require any file input for these.
// ** a.out should work without any additional files.

// Scanner processes only one word each time it is called
// ** Done by: Cam Tran
int scanner(tokentype& a, string& w)
{
    
  
    
  /* ************************* REST DONE *****************************
     // ** Grab the next word from the file
     //I did this in main ***BY BRAD***
     2. Call the token functions one after another (if-then-else)
     And generate a lexical error if both DFAs failed.
     Let the token_type be ERROR in that case.
     3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
     4. Return the token type & string  (pass by reference)
  */
    
  if (word_dfa(w)) {
    char lastChar = w[w.length() - 1];
        
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
    else if (w == "eofm")
      a = EOFM;
    else if ((lastChar == 'a') || (lastChar == 'e') || (lastChar == 'i') || (lastChar == 'o') || (lastChar == 'u'))
      a = WORD1;
    else
      a = WORD2;
    return 1;
  }
  else if (period(w)) {
    a = PERIOD;
    return 1;
  }
  else {
    a = ERROR;
    return 0;
  }
    
}//the end



// The test driver to call the scanner repeatedly
// ** Done by:  Cam Tran
int main()
{
  tokentype thetype;
  string theword;
  string tokens[16] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};
    
  /* ************** BRAD *****************************
     
  ******************* DONE ******************************
     1. get the input file name from the user
     2. open the input file which contains a story written in Japanese (fin.open).
     3. call Scanner repeatedly until the EOF marker is read, and
     each time cout the returned results
     e.g. STRING TOKEN-TYPE
     =====  ===========
     watashi PRONOUN  (from the first call)
     wa      SUBJECT  (from the second call)
     gakkou  WORD1
     etc.
  */
  string fileName;
  cout << "please enter a file name" << endl;
  cin >> fileName;//enter transaction.txt for commands                                                                         
  ifstream fin;
  fin.open(fileName.data()); 

    
  while (true)
    {
      fin >> theword;
        
      int tokenInt = scanner(thetype, theword);  // call the scanner
        
      if (tokenInt = 1)
	cout << "Word is: " << theword << "    ";  cout << "Type is: " << tokens[thetype] << endl;
        
        
    }
  fin.close();
  //********************* BRAD *****************************
    
    
    
}// end
