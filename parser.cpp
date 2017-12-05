#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>


using namespace std;
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();



//=================================================
// File parser.cpp written by Group Number: 10
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:


string tokens[15] = { "ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR" };

tokentype  saved_token;     // global buffer for the scanner token

bool exitFlag = false;
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
	exitFlag = true;
}

// Done by: Brad
void syntaxerror2(string lexeme, string parserFunction)
{
	cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << parserFunction << endl;
	exitFlag = true;
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
		if (exitFlag)
			exit(0);
		scan(saved_token, lexeme, fin);
		cout << "Scanner called using word: " << lexeme << endl;
		if (saved_token == ERROR) {
			cout << "Lexical Error: " << lexeme << " is not a valid token" << endl;
		}
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
	if (exitFlag)
		return false;
	if (next_token() != expected)  // mismatch has occurred with the next token
	{ // generate a syntax error message here
	  // do error handling here if any
		syntaxerror1(expected, saved_lexeme);
		return false;
	}
	else  // match has occurred
	{
		cout << "Match found for " << tokens[expected] << endl;
		token_available = false;  // eat up the token
		return true;              // say there was a match
	}
}



// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

// 1 <story> ::= <s> { <s> }
// Done by: Cam
void story()
{
	if (exitFlag)
		return;
	cout << "Processing <story>" << endl;
	s();
	while (true)
	{
		if (exitFlag)
			return;
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
		default:
			return;  // loop stops
		}//end switch
	}//end loop
}


//2 <s>  ::=  [CONNECTOR] <noun> SUBJECT <afterSubject>
// Done by: Cam
void s()
{
	if (exitFlag)
		return;
	cout << "Processing <afterSubject>" << endl;
	if (next_token() == CONNECTOR)    // start of what is in [ ] is found
		match(saved_token);// do it

	noun();
	match(SUBJECT);
	afterSubject();
}

// 3 <afterSubject> ::=  <verb> <tense> PERIOD | <noun> <afterNoun>
// Done by: Cam
void afterSubject()
{
	if (exitFlag)
		return;
	cout << "Processing <afterSubject>" << endl;
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
		afterNoun();
		break;

	default:
		syntaxerror2(saved_lexeme, "afterSubject");
	}

}

// 4 <afterNoun> :: = <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterObject>
// Done by: Brad
void afterNoun()
{
	if (exitFlag)
		return;
	cout << "Processing <afterNoun>" << endl;
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
		afterObject();
		break;

	default:
		syntaxerror2(saved_lexeme, "afterNoun");
	}
}

// 5 <afterObject> ::=  <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD 
// Done by: Brad
void afterObject()
{
	if (exitFlag)
		return;
	cout << "Processing <afterObject>" << endl;
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
		syntaxerror2(saved_lexeme, "afterObject");
	}
}

// 6 <noun> :: = WORD1 | PRONOUN
// Done by: Brad
void noun()
{
	if (exitFlag)
		return;
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
	if (exitFlag)
		return;
	cout << "Processing <verb>" << endl;
	match(WORD2);
}

// 8 <be> :: = IS | WAS
// Done by: Tony
void be()
{
	if (exitFlag)
		return;
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
	if (exitFlag)
		return;
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


	string fileName;
	cout << "please enter a file name" << endl;
	cin >> fileName;//enter transaction.txt for commands                                                                                                                  
	fin.open(fileName.data());

	story();

	fin.close();

}// end
 //** should require no other input files!
