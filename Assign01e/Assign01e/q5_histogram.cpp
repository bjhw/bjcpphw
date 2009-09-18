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

//const int nBuckets = 10;
typedef Vector<string> scoresV;

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
scoresV GetScoresFromFile(ifstream &infile, statsT &stats);
string getLabelB(int bucket);

/* Main program */

int main() {
    ifstream infile;
    statsT stats;
    int nBuckets = 10;

	cout << "Let's process a file of exam scores!" << endl;
    PromptUserToOpenFile(infile);
    scoresV scores = GetScoresFromFile(infile, stats);
    //for (int i = 0; i < scores.size(); i++)
        //cout << "score " << i << " is " << scores.getAt(i) << endl;

    // Determine how many scores are in each bucket.  Use array indexes as
    // buckets to hold count of scores.
    int histogram[10];  // Hmm; redefine histogram as a Vector instead of array?
    DevelopHistogram(scores, histogram, nBuckets);
    //for (int i = 0; i < nBuckets; i++)
        //cout << "count for " << i << " is " << histogram[i] << endl;

    PrintResults(histogram, nBuckets, getLabelB);

    cout << endl;
    cout << "Statistics: " << setprecision(3);
        cout << "  Min: " << stats.min;
        cout << "  Max: " << stats.max;
        cout << "  Avg: " << stats.avg;     // could do something like setw(x) 
        cout << endl;
    return 0;
}

/*
Function: GetScoresFromFile
Usage: GetScoresFromFile(infile, stats)
-----------------------------------
This function reads a file that contains exam scores and returns a 'scores'
vector of those scores.  Updates ref to 'stats' struct w/ min/max/avg.
*/
scoresV GetScoresFromFile(ifstream &infile, statsT &stats) {
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
//cout << "The score is " << the_score << endl;
        sum += the_score;
        if (the_score < stats.min) stats.min = the_score;
        if (the_score > stats.max) stats.max = the_score;
    }
    infile.close();

    if (score.size() > 0)
        stats.avg = sum / score.size();
    
    return score;
}


/*
Function: getLabelB
Usage: getLabelB(bucket);
-----------------------------------
This function executes a switch statement to fish out the proper label
for the given bucket/index.  This is also in a library as 'getLabel', w/ "0-9:   "
 */

string getLabelB(int bucket) {
    switch (bucket) {
        case 0: return "00-09: ";
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
