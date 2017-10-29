#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 10
//=====================================================

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by:*************************** TONY *****************************
// ** RE:
bool mytoken(string s)
{
  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      if (state == 0 && s[charpos] == 'a')
      state = 1;
      else
      if (state == 1 && s[charpos] == 'b')
      state = 2;
      else
      if (state == 2 && s[charpos] == 'b')
      state = 2;
      else
	  return(false);
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
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
typedef enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};


// ** Need the lexicon to be set up here (to be used in Part C)
// ** Need the reservedwords list to be set up here
// ** Do not require any file input for these.
// ** a.out should work without any additional files.

// Scanner processes only one word each time it is called
// ** Done by: Cam Tran
int scanner(tokentype& a, string& w)
{

  // ** Grab the next word from the file               ***************** BRAD *****************************

  /* ************************* REST DONE *****************************
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error if both DFAs failed.
     Let the token_type be ERROR in that case.
  3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
  4. Return the token type & string  (pass by reference)
  */

	if (mytoken(w)) {
		char lastChar = w[w.length - 1];
		
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
	}
	else if (period(w))
		a = PERIOD;
	else
		a = ERROR;

}//the end



// The test driver to call the scanner repeatedly  
// ** Done by:  Cam Tran
int main()
{
  	tokentype thetype;
  	string theword; 
	string tokens[16] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"};

  /* ************** BRAD *****************************
1. get the input file name from the user
2. open the input file which contains a story written in Japanese (fin.open).

   ******************* DONE ******************************
3. call Scanner repeatedly until the EOF marker is read, and
     each time cout the returned results
     e.g. STRING TOKEN-TYPE
          =====  ===========
          watashi PRONOUN  (from the first call)
          wa      SUBJECT  (from the second call)
          gakkou  WORD1
          etc.
  */
	
  while (true)
    {
      int tokenInt = scanner(thetype, theword);  // call the scanner

	  cout << "Word is: " << theword << "	";  cout << "Type is: " << thetype[tokenInt] << endl;
    

    }

  // ** close the input file ********************* BRAD *****************************

}// end



