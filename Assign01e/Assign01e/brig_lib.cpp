/*
Uses 'string("")+' as a means to convert char to string; must be another way...
*/
#include <iostream>
//#include <iomanip>
#include <fstream>
#include "genlib.h"
#include "simpio.h"
#include "strutils.h"
#include "vector.h"

/* Constants */

const string testfile = "exam_scores.txt";
const string HISTO_CHAR = "X";

typedef Vector<string> scoresV;
typedef Vector<string> linesV;

/* Private function prototypes */


/*
Function: DevelopHistogram
Usage: DevelopHistogram(scores, histo, n)
-----------------------------------------
Upon receiving a vector of numeric strings 'scores', which range as
0 <= score <= 99, we examine the number that start with any given digit,
updating the counts within the array 'histo'.  'histo' will have 'n'
different categories/slots, could probably hardcode as 10 since 0<n<100.
 */
void DevelopHistogram(scoresV scores, int histo[], int n) {
    // Initialize the histogram
    for (int i = 0; i < n; i++) {
        histo[i] = 0;
    }

    for (int i = 0; i < scores.size(); i++) {
        // get first char of score
        if (scores[i].length() > 1) {
            //tens_char.push_back( (scores[i])[0] );    // from earlier efforts...
            histo[ StringToInteger(string ("") + (scores[i])[0]) ] ++;
        }
        else {
            histo[0] ++;
        }
    }
}


/*
Function: PromptUserToOpenFile
Usage: PromptUserToOpenFile(infile)
-----------------------------------
User types a filename, this function opens the file.
 */
void PromptUserToOpenFile(ifstream &infile) {
    bool file_open = false;
    while (! file_open) {
        // Prompt the user for the name of a file of exam scores to compile
        cout << "Enter filename (RETURN to quit): ";

        //string filename = testfile;     cout << endl;   // for debugging
        string filename = GetLine();

        if (filename == "") break;
        infile.open( filename.c_str() );
        if (infile.fail()) {
            cout << "Could not open file: '" << filename << "'" << endl;
            infile.clear();
        }
        else { 
            file_open = true;
        }
    }
}


/*
Function: GetLinesFromFile
Usage: GetLinesFromFile(infile)
-----------------------------------
This function reads a file and returns a 'linesV' vector of those lines.
*/
linesV GetLinesFromFile(ifstream &infile) {
    linesV lines;
    string line = "";
    while (true) {
        getline(infile, line);
        if (infile.fail()) break;
        lines.add(line);
    }
    infile.close();

    return lines;
}


/*
Function: getLabel
Usage: getLabel(bucket);
-----------------------------------
This function executes a switch statement to fish out the proper label
for the given bucket/index.
 */
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


/*
Function: PrintResults
Usage: PrintResults(histogram, n)
-----------------------------------------
For each of the 'n' buckets of the histogram array, print a label and a count
of the number of items in the bucket.
*/
void PrintResults(int histo[], int n, string (getTheLabel)(int) = getLabel) {
    for (int i = 0; i < n; i++) {
        cout << getTheLabel(i); //Hmm, this a problem:  How does user alter? callback?
        for (int j = 0; j < histo[i]; j++) {
            cout << HISTO_CHAR;
        }
        cout << endl; 
    }
}
