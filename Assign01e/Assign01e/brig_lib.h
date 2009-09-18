/*
File: brig_lib.h
----------------
This interface contains various functions that were helpful in doing coursework
for CS106B.
*/

#ifndef _brig_lib_h
#define _brig_lib_h

typedef Vector<string> scoresV;
typedef Vector<string> linesV;


/*
Function: DevelopHistogram
Usage: DevelopHistogram(scores, histo, n)
-----------------------------------------
Upon receiving a vector of numeric strings 'scores', which range as
0 <= score <= 99, we examine the number that start with any given digit,
updating the counts within the array 'histo'.  'histo' will have 'n'
different categories/slots, could probably hardcode as 10 since 0<n<100.
 */
void DevelopHistogram(scoresV scores, int histo[], int n);


/*
Function: PromptUserToOpenFile
Usage: PromptUserToOpenFile(infile)
-----------------------------------
User types a filename, this function opens the file.
 */
void PromptUserToOpenFile(ifstream &infile);


/*
Function: GetLinesFromFile
Usage: GetLinesFromFile(infile)
-----------------------------------
This function reads a file and returns a 'linesV' vector of those lines.
*/
linesV GetLinesFromFile(ifstream &infile);


/*
Function: getLabel
Usage: getLabel(bucket);
-----------------------------------
This function executes a switch statement to fish out the proper label
for the given bucket/index.
 */
string getLabel(int bucket);


/*
Function: PrintResults
Usage: PrintResults(histogram, n, getLabelB)
-----------------------------------------
For each of the 'n' buckets of the histogram array, print a label and a count
of the number of items in the bucket.  Third param is a user-defined function
that returns labels as strings given a bucket number of 0-9.  Default function
getLabel is included here.
*/
void PrintResults(int histo[], int n, string (getTheLabel)(int) = getLabel);

#endif
