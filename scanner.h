#include <string>
#ifndef _SCANNER_H
#define _SCANNER_H

using namespace std;

enum token_type { ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRON\
    OUN, CONNECTOR };

class scanner
{
    // ** Done by: TONY
    bool vowel(char letter);
    
    // ** Done by: TONY
    bool cons1(char letter);
    
    // ** Done by: TONY
    bool cons2(char letter);
    
    // ** MYTOKEN DFA to be replaced by the WORD DFA
    // ** Done by: TONY
    bool word_dfa(string s);
    
    // ** Done by: Cam Tran
    bool period(string s);
    
    // Scanner processes only one word each time it is called
    // ** Done by: Cam Tran
    int scan(token_type& a, string& w);
};

#endif
