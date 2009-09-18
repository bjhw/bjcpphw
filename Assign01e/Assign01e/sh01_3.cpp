/*
Program reads a text file full of exam scores as directed by user.
A count of the scores is arranged and printed as a histogram.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "genlib.h"
#include "simpio.h"
#include "strutils.h"
#include "vector.h"
#include "brig_lib.h"


/* Constants */

typedef Vector<string> linesV;
const int alpha_size = 26;


/* Private function prototypes */
void BumpCountForEachChar(string line, int lCount[]);
void PrintCounts(int lCount[]);


/* Main program */

int Xmain() {
    ifstream infile;

    // Get lines from file
	cout << "Let's process a file of random text and count characters!" << endl;
    PromptUserToOpenFile(infile);
    linesV lines = GetLinesFromFile(infile);
    //for (int i = 0; i < lines.size(); i++)
        //cout << "score " << i << " is " << lines.getAt(i) << endl;

    // Prepare an array to hold the data.
    int lCount[alpha_size];
    for (int i = 0; i < alpha_size; i++)
        lCount[i] = 0;

    // Examine each line for its characters, increment the proper indexes.
    for (int i = 0; i < lines.size(); i++) {
        BumpCountForEachChar(lines[i], lCount);
    }

    PrintCounts(lCount);



    return 0;
}


/*
Function: BumpCountForEachChar
Usage: BumpCountForEachChar(line, lCount)
-----------------------------------------
This function examines a line 'line' of text and for each alpha character
increments the associated index in 'lCount'.  Case-insensitive, letters only.
*/
void BumpCountForEachChar(string line, int lCount[]) {
    string chars_lc = ConvertToLowerCase(line);
    for (int i = 0; i < chars_lc.length(); i++) {
        if (isalpha(chars_lc[i]))
            lCount[ chars_lc[i] % 'a' ] ++;
    }
}


/*
Function: PrintCounts
Usage: PrintCounts(lCount)
--------------------------
This function prints a report about the frequency of each alpha character
that was found and 'counted' into 'lCount'.
*/
void PrintCounts(int lCount[]) {
    for (int i = 'a'; i < 'a' + alpha_size; i++)
        cout << (char)i << ": " << lCount[i % 'a'] << endl;
        //char c=(char)('a' + i - 1);
}


/*
Function: getLabel
Usage: getLabel(bucket);
-----------------------------------
This function executes a switch statement to fish out the proper label
for the given bucket/index.  [[ This now in a library but maybe resurrect. ]]

string getLabel(int bucket) {
    switch (bucket) {
        case 0: return "0-9:   ";
        case 1: return "10-19: ";
        case 2: return "20-29: ";
        case 3: return "30-39: ";
        case 4: return "40-49: ";
        case 5: return "50-59: ";
        case 6: return "60-69: ";
        case 7: return "70-79: ";
        case 8: return "80-89: ";
        case 9: return "90-99: ";
        default:
            Error("Unexpected case value"); // raises an error msg since no 'return'
    }
    return("Unexpected case value");
}
 */
