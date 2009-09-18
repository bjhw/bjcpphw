/*
 * Project: Assign02a
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: Brig Johnson
 * Section: Independent
 * Program uses Markov Modeling to read a file of sample text and then
 * create a new set of output that simulates what the computer might
 * expect to receive based on what it learned from character usage from
 * the first file.
 *
 * An improvement would be to do a special reset when the seed gets a "\n".
 * Since punch items are independent from one another, we should build up from
 * a seed of length k that starts a new line.  This means creating a vector of
 * terms of length k that start new lines to draw on as seeds when the textmaker
 * hits a "\n" character.
 */

#include "genlib.h"
#include <iostream>     // due to:  
#include <fstream>
#include "map.h"        //          Map
#include "set.h"
#include "simpio.h"     // due to:  GetLine();
#include "random.h"     // due to:  GetLine();
#include "brig_lib.h"

/* Constants */

const string testfile = "exam_scores.txt";
const int minK = 0;
const int maxK = 10;
const int nCHARS = 2000;

Map< Map<int> > BuildPatterns(int k, string textbase, string &max_p_pattern);
string BuildMarkovString(int k, Map< Map<int> > &p, string &max_p_pattern);

int main ()
{
    // Get filename from user
    ifstream infile;
	cout << "What file contains the sample text we should learn from?" << endl;
    PromptUserToOpenFile(infile);

    // Build string of file's data
    string textbase;    // string of text from designated file
    long count = 0;     // allows for looking at a large base of text...
    while (true) {
        infile.peek();  // adding by char as an easy way to preserve '\n'
        if (infile.fail()) break;
        textbase.push_back( (char)infile.get() ); // need char since get returns int
    }
    infile.close();
    //cout << textbase << endl;

    // Get Markov level from user
    int k = -1;              // user's choice of Markov order number
    while ( !(k >= minK && k <= maxK) ) {
        cout << "What Markov level of analysis (a number from 1 to 10)? ";
        k = GetInteger();
        cout << "Analyzing.... Please wait." << endl;
    }

    // Build Markov Model
    string max_p_pattern;
    Map< Map<int> > p = BuildPatterns(k, textbase, max_p_pattern);

    // Create appropriate output
    string new_text = BuildMarkovString(k, p, max_p_pattern);
    cout << new_text << endl;

	return 0;
}

Map< Map<int> > BuildPatterns(int k, string textbase, string &max_p_pattern) {
    Map< Map<int> > p;
    int max_p_count = 0;
    //string max_p_pattern = "";
    for (int i = k; i <= textbase.length() - k; i++) {
        string pattern = textbase.substr(i-k, k);
        string the_char = string("") + textbase[i];
        if (p.containsKey(pattern)) {
            if (p[pattern].containsKey(the_char))
                p[pattern][the_char] ++;
            else
                p[pattern][the_char] = 1;

            p[pattern]["TOTAL"] ++;
            if (p[pattern]["TOTAL"] > max_p_count) {
                max_p_pattern = pattern;
                max_p_count = p[pattern]["TOTAL"];
            }
        }
        else {
            p[pattern][the_char] = 1;
            p[pattern]["TOTAL"] = 1;
        }
    }
cout << max_p_pattern << " = " << max_p_count << endl;
    
	return p;
}

string BuildMarkovString(int k, Map< Map<int> > &p, string &max_p_pattern) {
    string new_text = max_p_pattern;
    string current_view = max_p_pattern;
    Randomize();
    int r_index;
    string key;
    for (int i = 0; i < nCHARS; i++) {
		int total = p[current_view]["TOTAL"];
        r_index = RandomInteger(1, p[current_view]["TOTAL"]);
        Map<int>::Iterator itr = p[current_view].iterator();
        
        while (itr.hasNext()) {
            key = itr.next();
            if ( key == "TOTAL" )
                key = itr.next();
            if (r_index <= p[current_view][key]) {
                new_text += key;
                current_view += key;
                current_view.replace(0, 1, "");
                break;
            }
            else {
                r_index -= p[current_view][key];
            }
        }   
    }
    return new_text;
}

/*
    Map< Map<int> >::Iterator itr = p.iterator();
    int max_p_count = 0;
    string max_p_pattern = "";
    while (itr.hasNext()) {
        string key = itr.next();
        if (p[key]["TOTAL"] > max_p_count) {
            max_p_pattern = key;
            max_p_count = p[key]["TOTAL"];
//cout << key << " = " << p[key]["TOTAL"] << endl;
cout << max_p_pattern << " = " << max_p_count << endl;
        }
    }   
*/
