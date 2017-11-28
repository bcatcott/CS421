#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 10
//=====================================================

enum token_type {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR};

// ** Done by: TONY
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
// ** Done by: TONY
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
// ** Done by: TONY 
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
// ** Done by: TONY
// ** RE:
bool word_dfa(string s)
{
    string state = "q0"; //starting state
    int charpos = 0; //char index
    
    cout << "Trying the word dfa machine " << endl;
    
    while (s[charpos] != '\0') //loops through each char in string
    {
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
int scan(token_type& a, string& w, ifstream& fin)
{
    fin >> w;
    
    if (word_dfa(w)) {
        char lastChar = w[w.length() - 1]; //sets a variable for the last letter to check if WORD1 or WORD2
        
		//checks reserved words
        if (w == "masu")
            a = token_type::VERB;
        else if (w == "masen")
            a = token_type::VERBNEG;
        else if (w == "mashita")
            a = token_type::VERBPAST;
        else if (w == "masendeshita")
            a = token_type::VERBPASTNEG;
        else if (w == "desu")
            a = token_type::IS;
        else if (w == "deshita")
            a = token_type::WAS;
        else if (w == "o")
            a = token_type::OBJECT;
        else if (w == "wa")
            a = token_type::SUBJECT;
        else if (w == "ni")
            a = token_type::DESTINATION;
        else if (w == "watashi" || w == "anata" || w == "kare" || w == "sore")
            a = token_type::PRONOUN;
        else if (w == "mata" || w == "soshite" || w == "shikashi" || w == "dakara")
            a = token_type::CONNECTOR;
        else if ((lastChar == 'I') || (lastChar == 'E')) //checks if it ends in capital I or E for WORD2
            a = token_type::WORD2;
        else
            a = token_type::WORD1;
        return 1;
    }
	//runs the period dfa
    else if (period(w)) {
        a = token_type::PERIOD;
        return 1;
    }
    else {
        a = token_type::ERROR;
        return 0;
    }
    
}//the end



