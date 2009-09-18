#include <iostream>
#include "genlib.h"
#include "simpio.h"

/* Private function prototypes */

bool IsPerfect(int n);

/* Constants */

const int MIN = 1;
const int MAX = 10000;

/* Main program */

int main() {
    for ( int i = MIN; i <= MAX; i++ ) {
        if ( IsPerfect(i) ) {
            cout << "Perfect Number: " << i << endl;
        }
    }
}


/*
 * Function: IsPerfect
 * Usage: IsPerfect(n);
 * -----------------------------------
 * Returns 'true' if 'n' is a perfect number
 */
bool IsPerfect(int n) {
    int total = 0;
    for ( int i = 1; i <= n/2; i++ ) {
        if ( ! (n % i) ) {
            total += i;
        }
    }
    return ( total == n );
}
