/*
Program uses "Soundex algorithm" to allow user to generate Soundex patterns
for various surnames.  (O'Dell and Russell:  1918)
Uses 'push_back' as a means to convert char to string; must be another way...
*/
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "strutils.h"

/* Constants */

const int MAX_SDX_DIGITS = 3;
const char SDX_DFLT_CHAR = '0';

/* Private function prototypes */

string GetSoundexDigit(char ch);
string ConvertLettersToSoundexDigits(string surname);
string GetSoundex(string surname);
void PadStringWithThisChar(string& pad_this_string, int num_places, char ch);

/* Main program */

int main() {
    while (true) {
        // Prompt the user for a surname that should be transformed to a Soundex
        cout << "Enter surname (RETURN to quit): ";
        string surname = GetLine();
        if (surname == "") break;
        string soundex = GetSoundex(surname);
        cout << "Soundex code for " << surname << " is " << soundex << endl;
    }
    return 0;
}


/*
Function: GetSoundex
Usage: GetSoundex(surname)
-----------------------------------
Given a string surname, this function returns the associated Soundex pattern.
 */
string GetSoundex(string surname) {
    surname = ConvertToUpperCase(surname); 

    // move first letter of surname to be first letter of soundex
    string soundex = "";
    soundex.push_back( surname[0] );
    surname.replace(0, 1, "");

    // convert remaining letters to digits, toss zero and non-letter characters
    string sdx_digits = ConvertLettersToSoundexDigits(surname);

    // Pad the soundex digits with zeros if necessary
    PadStringWithThisChar(sdx_digits, MAX_SDX_DIGITS, SDX_DFLT_CHAR);

    soundex += sdx_digits;
    return soundex;
}

/*
Function: ConvertLettersToSoundexDigits
Usage: ConvertLettersToSoundexDigits(surname)
-----------------------------------
This function converts the letters in an uppercase string to their
corresponding Soundex digit.  "Consecutive" digits and zeros are ignored.
Certain other characters are also ignored (e.g. punctuation and whitespace.)
Function returns the string of digits that remain.
 */
string ConvertLettersToSoundexDigits(string surname) {
    string sdx_digits = "";
    string last_digit = "";
    for (int i = 0; i < surname.length(); i++) {
        string this_digit = GetSoundexDigit(surname[i]);
        // will be "" if char was punctuation or a '0'-type letter

        if (this_digit == last_digit  ||  this_digit == "") {
            // do nothing
        }
        else {
            sdx_digits += this_digit;
            last_digit = this_digit;
        }

        if (sdx_digits.length() == MAX_SDX_DIGITS) break;
    }
        
    return sdx_digits;
}

/*
Function: GetSoundexDigit
Usage: GetSoundexDigit(surname[i]);
-----------------------------------
This function converts an upper-case character into its corresponding
Soundex digit.  Digits that would return zero are ignored.
Certain other characters are also ignored (e.g. punctuation and whitespace.)
Function returns the corresponding digit as a string.
 */
string GetSoundexDigit(char ch) {
    switch (ch) {
        case 'B': case 'F': case 'P': case 'V': return "1";

        case 'C': case 'G': case 'J': case 'K':
        case 'Q': case 'S': case 'X': case 'Z': return "2";

        case 'D': case 'T':                     return "3";

        case 'M': case 'N':                     return "4";

        case 'L':                               return "5";

        case 'R':                               return "6";

        default:                                return "";
    }
}

/*
Function: PadStringWithThisChar
Usage: PadStringWithThisChar(pad_this_string, num_places, ch) {
-----------------------------------
This function insures there is a string of characters num_places long by padding
trailing positions with char 'ch' as necessary.  Might be useful for creating
histograms...
 */
void PadStringWithThisChar(string& pad_this_string, int num_places, char ch) {
    int num_chars_reqd = num_places - pad_this_string.length();
    if (num_chars_reqd > 0) {
        for (int i = 0; i < num_chars_reqd; i++) {
            pad_this_string.push_back( ch );
        }
    }
}
