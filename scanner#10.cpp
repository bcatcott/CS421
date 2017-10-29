#include <iostream>
#include <string>

//Returns true if one of the reserved words is found and prints out the token type and word.
bool reservedWord(string input) {
	if (input == ".") {
		cout << "Token Type: PERIOD		Word is: " << input << endl;
		return true;
	}
	else if (input == "masu") {
		cout << "Token Type: VERB		Word is: " << input << endl;
		return true;
	}
	else if (input == "masen") {
		cout << "Token Type: VERBNEG		Word is: " << input << endl;
		return true;
	}
	else if (input == "mashita") {
		cout << "Token Type: VERBPAST		Word is: " << input << endl;
		return true;
	}
	else if (input == "masendeshita") {
		cout << "Token Type: VERBPASTNEG	Word is: " << input << endl;
		return true;
	}
	else if (input == "desu") {
		cout << "Token Type: IS			Word is: " << input << endl;
		return true;
	}
	else if (input == "deshita") {
		cout << "Token Type: WAS		Word is: " << input << endl;
		return true;
	}
	else if (input == "o") {
		cout << "Token Type: OBJECT		Word is: " << input << endl;
		return true;
	}
	else if (input == "wa") {
		cout << "Token Type: SUBJECT		Word is: " << input << endl;
		return true;
	}
	else if (input == "ni") {
		cout << "Token Type: DESTINATION	Word is: " << input << endl;
		return true;
	}
	else if (input == "watashi" || input == "anata" || input == "kare" || input == "sore") {
		cout << "Token Type: PRONOUN		Word is: " << input << endl;
		return true;
	}
	else if (input == "mata" || input == "soshite" || input == "shikashi" || input == "dakara") {
		cout << "Token Type: CONNECTOR		Word is: " << input << endl;
		return true;
	}
	else if (input == "eofm") {
		cout << "Token Type: EOFM		Word is: " << input << endl;
		return true;
	}
	else
		return false;
}

int main ()
{
	string input;
	
	//
	// Read in from the file
	//
	
	
	//checks if it is not a reserved word
	if (!reservedWord(input))
		//checks if it is a word in the language
		if (scanner(input)) {
			char lastChar = input[input.length - 1];
			
			//Checks if it ends in a vowel(lowercase) and outputs the word as WORD1
			//If it does not end in a vowel(lowercase) it outputs the word as WORD2
			if ((lastChar == 'a') || (lastChar == 'e') || (lastChar == 'i') || (lastChar == 'o') || (lastChar == 'u'))
				cout << "Token Type: WORD1		Word is: " << input << endl;
			else
				cout << "Token Type: WORD2		Word is: " << input << endl;
		}
		else 	//If the word is not in the language, displays an error
			cout << "Token Type: ERROR		Word is: " << input << endl;
		

	return 0;
}
