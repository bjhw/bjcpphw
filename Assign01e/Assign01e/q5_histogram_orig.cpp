/*
Program reads a text file full of exam scores as directed by user.
A count of the scores is arranged and printed as a histogram.
Uses 'push_back' as a means to convert char to string; must be another way...
Program should also pass open file by reference rather than jamming code
into a certain function in order to avoid passing by reference.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include "genlib.h"
#include "simpio.h"
#include "strutils.h"
#include "vector.h"

/* Constants */

const string testfile = "exam_scores.txt";
const int nBuckets = 10;
typedef Vector<string> scoresV;
const string HISTO_CHAR = "X";

/*
Type: statsT
------------
Statistics on a set of exam scores
 */
struct statsT {
    double min;
    double max;
    double avg;
};

/* Private function prototypes */
scoresV GetScoresFromFile(statsT &stats);
void DevelopHistogram(scoresV scores, int histo[], int n);
void PrintResults(int histo[], int n);
string getLabel(int bucket);

/* Main program */

int Xmain() {
    statsT stats;
    scoresV scores = GetScoresFromFile(stats);
    //for (int i = 0; i < scores.size(); i++)
        //cout << "score " << i << " is " << scores.getAt(i) << endl;

    // Determine how many scores are in each bucket.  Use array indexes as
    // buckets to hold count of scores.
    int histogram[nBuckets];
    DevelopHistogram(scores, histogram, nBuckets);
    //for (int i = 0; i < nBuckets; i++)
        //cout << "count for " << i << " is " << histogram[i] << endl;

    PrintResults(histogram, nBuckets);

    cout << endl;
    cout << "Statistics: " << setprecision(3);
        cout << "  Min: " << stats.min;
        cout << "  Max: " << stats.max;
        cout << "  Avg: " << stats.avg;
//setw(1) 
        cout << endl;
    return 0;
}

/*
Function: PrintResults
Usage: PrintResults(histogram, nBuckets)
-----------------------------------------
For each of the buckets of the histogram array, print a label and a count
of the number of items in the bucket.
*/
void PrintResults(int histo[], int n) {
    for (int i = 0; i < n; i++) {
        cout << getLabel(i);
        for (int j = 0; j < histo[i]; j++) {
            cout << HISTO_CHAR;
        }
        cout << endl; 
    }
}


/*
Function: DevelopHistogram
Usage: DevelopHistogram(scores, histo, n)
-----------------------------------------
Upon receiving a vector of numeric strings 'scores', we examine the number
that start with any given digit, updating the counts within the array 'histo'.
 */
void DevelopHistogram(scoresV scores, int histo[], int n) {
    // Initialize the histogram
    for (int i = 0; i < n; i++) {
        histo[i] = 0;
    }

    for (int i = 0; i < scores.size(); i++) {
        // get first char of score
        if (scores[i].length() > 1) {
            string tens_char = "";
            tens_char.push_back( (scores[i])[0] );
            histo[ StringToInteger(tens_char) ] ++;
        }
        else {
            histo[0] ++;
        }
    }
}

/*
Function: GetScoresFromFile
Usage: GetScoresFromFile(statsT stats)
-----------------------------------
User types a filename that contains exam scores, this function reads the file
and returns a 'scores' vector of those scores. Updates stats struct w/ min/max/avg.
Would be nice to break this in two:  Have the first part return a ref to an
open file, second function would parse the data.
 */
scoresV GetScoresFromFile(statsT &stats) {
    ifstream infile;
    bool file_open = false;
    while (! file_open) {
        // Prompt the user for the name of a file of exam scores to compile
        cout << "Enter filename containing exam scores (RETURN to quit): ";

        string filename = testfile;     cout << endl;   // for debugging
        //string filename = GetLine();

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
        
    double sum = 0.0;
    stats.min = 100.0;
    stats.max = 0.0;
    stats.avg = 0.0;

    scoresV score;
    string line = "";
    while (true) {
        getline(infile, line);
        if (infile.fail()) break;
        score.add(line);

        double the_score = StringToReal(line);
cout << "The score is " << the_score << endl;
        sum += the_score;
        if (the_score < stats.min) stats.min = the_score;
        if (the_score > stats.max) stats.max = the_score;
/*
*/
    }
    infile.close();

    if (score.size() > 0)
        stats.avg = sum / score.size();
    
    return score;
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
