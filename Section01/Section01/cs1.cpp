#include <iostream>
#include "genlib.h"
#include "simpio.h"

/* Private function prototypes */

string CensorString1(string text, string remove);

/* Main program */

int main() {
    // Get base string and characters to remove.
    cout << "Enter the basic string: ";
    string text = GetLine();
    cout << "Enter the chars to remove: ";
    string remove = GetLine();

    // Execute CensorString
    string text2 = CensorString1(text, remove);

    // Display results
    cout << "The new string is: " << text2 << endl;

}


/*
 * Function: CensorString1
 * Usage: CensorString1(text, remove);
 * -----------------------------------
 * Removes characters in the 'remove' string from the 'text' string.
 *
 *
 *
 *
 *
 */
string CensorString1(string text, string remove) {
    // foreach character in the 'text' string,
    // see if it matches any of the 'remove' chars.
    // If so, move to next char, else add char to 'newtext' string.
    string newtext = "";
    for (int i = 0; i < text.length(); i++) {
        bool add_newtext = true;
        for (int j = 0; j < remove.length(); j++) {
            if ( text[i] == remove[j] ) {
                add_newtext = false;
                break;
            }
        }
        if ( add_newtext ) {
            newtext += text[i];
        }
    }
    return newtext;
}
