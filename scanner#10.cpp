#include <iostream>
#include <string>

//Returns true if one of the reserved words is found and prints out the token type and word.
bool reservedWord(string input) {
	if (input == "masu") {
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

  return 0;
}
