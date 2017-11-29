#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>


using namespace std;
void s ();
void s1();
void s2();
void s3();
void noun();
void verb();
void be();
void tense();



//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:


string tokens[16] = {"EOFM", "ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR"};

tokentype  saved_token;     // global buffer for the scanner token

bool eofmFlag = false;

string saved_lexeme;// global buffer for the saved lexeme
ifstream fin;               //global file
// global flag indicating whether
// we have saved a token to eat up or not
bool   token_available;


// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)

// Done by: Brad
void syntaxerror1(tokentype expected, string lexeme)
{
  cout << "SYNTAX ERROR: expected " << tokens[expected] << " but found " << lexeme << endl;
}

// Done by: Brad
void syntaxerror2 (string lexeme, string parserFunction)
{
  cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << parserFunction << endl;
}

// ** Need the updated match and next_token (with 2 global vars)

//next_token(void)
//    Looks ahead to see what token comes next from the scanner.
//    HOW: checks first to see if the token_available flag is false.
//    If so, saved_token gets scanner() result.
//    and the flag is set true.
//    Thus a token is grabbed but is not eaten up.
//    Returns the saved_token
//   
// Done by: Cam
tokentype next_token()
{
  string lexeme;

  if (!token_available)   // if there is no saved token from previous lookahead
    {
      	cout << "Scanner was Called..." << endl;
	scan(saved_token, lexeme, fin);
        scan(saved_token, lexeme, fin);
	if (saved_token == ERROR) 
		cout << "Lexical Error" << endl;
     	token_available = true;                  // mark that fact that you have saved it
      	saved_lexeme = lexeme;

    }
  return saved_token;    // return the saved token
}

//match(expected)
//  Checks and eats up the expected token.
//  HOW: checks to see if expected is different from next_token()
//  and if so, generates a syntax error and handles the error
//  else token_available becomes false (eat up) and returns true.
// Done by: Cam
bool match(tokentype expected)
{
	if (saved_lexeme == "eofm")
	{
		eofmFlag = true;
		exit(0);
	}
		
  if (next_token() != expected)  // mismatch has occurred with the next token
    { // generate a syntax error message here
      // do error handling here if any
      syntaxerror1(expected, saved_lexeme);
    }
  else  // match has occurred
    {
      cout << "Match found for " << tokens[expected] << endl;
      token_available = false;  // eat up the token
      return true;              // say there was a match
    }
}



// ** Make each non-terminal into a function here
// *********ALL OF US***************
// ** Be sure to put the corresponding grammar rule above each function

// 1 <story> ::= <s> { <s> }
// Done by: Cam
void story()
{
  cout << "Processing <story>" << endl;
  s();
  while (!eofmFlag)
    {
      switch (next_token()) // look ahead to see if the valid start is there
	{
	case CONNECTOR: s();// found another beginning 
	  // so do it
	  break;
	case WORD1:s();// found another beginning 
	  // so do it
	  break;
	case PRONOUN:s();// found another beginning 
	  // so do it
	  break;
	      case EOFM:
		      return;
	default: 
	  return;  // loop stops
	}//end switch
    }//end loop
}


//2 <s>  :: = [CONNECTOR] <noun> SUBJECT  <s1>
// Done by: Cam
void s()
{
  cout << "Processing <s>" << endl;
  if (next_token() == CONNECTOR)    // start of what is in [ ] is found
    match(saved_token);// do it

  noun();
  match(SUBJECT);
  s1();
}

// 3 <s1> :: = <verb> <tense> PERIOD | <noun> <s2>
// Done by: Cam
void s1()
{
  cout << "Processing <s1>" << endl;
  switch (next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;

    case WORD1:
    case PRONOUN:
      noun();
      s2();
      break;

    default:
      syntaxerror2(saved_lexeme, "s1");
    }

}

// 4 <s2> ::=  <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <s3>
// Done by: Brad
void s2()
{
  cout << "Processing <s2>" << endl;
  switch (next_token())
    {
    case IS:
    case WAS:
      be();
      match(PERIOD);
      break;

    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    case OBJECT:
      match(OBJECT);
      s3();
      break;

    default:
      syntaxerror2(saved_lexeme, "s2");
    }
}

// 5 <s3> :: = <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Brad
void s3()
{
  cout << "Processing <s3>" << endl;
  switch (next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;

    case WORD1:
    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    default:
      syntaxerror2(saved_lexeme, "s3");
    }
}

// 6 <noun> :: = WORD1 | PRONOUN
// Done by: Brad
void noun()
{
  cout << "Processing <noun>" << endl;
  switch (next_token())
    {
    case WORD1:
      match(WORD1);
      break;

    case PRONOUN:
      match(PRONOUN);
      break;

    default:
      syntaxerror2(saved_lexeme, "noun");
    }
}

// 7 <verb> ::= WORD2
// Done by: Tony
void verb()
{
  cout << "Processing <verb>" << endl;
  match(WORD2);
}

// 8 <be> :: = IS | WAS
// Done by: Tony
void be()
{
  cout << "Processing <be>" << endl;
  switch (next_token())
    {
    case IS:
      match(IS);
      break;

    case WAS:
      match(WAS);
      break;

    default:
      syntaxerror2(saved_lexeme, "be");
    }
}

// 9 <tense> : = VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Tony
void tense()
{
  cout << "Processing <tense>" << endl;
  switch (next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;

    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;

    case VERB:
      match(VERB);
      break;

    case VERBNEG:
      match(VERBNEG);
      break;

    default:
      syntaxerror2(saved_lexeme, "tense");
    }
}

// The test driver to start the parser
// Done by: Tony/Brad
int main()
{

  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

  tokentype thetype;
  string theword;
  


  string fileName;
  cout << "please enter a file name" << endl;
  cin >> fileName;//enter transaction.txt for commands                                                                                                                  
  fin.open(fileName.data());

  story();
  
  fin.close();

}// end
 //** should require no other input files!
