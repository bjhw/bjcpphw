#include <iostream>
#include "genlib.h"
#include "simpio.h"

/* Private function prototypes */

void doChoice(int choice);
void doCannon();
int Cannonballs(int n);

/* Main program */

int main() {
  while (true) {
    // Get pgm to run
    cout << "Which program would you like to run?" << endl;
    cout << "4: Cannonballs" << endl;
    int choice = GetInteger();
    if (choice == 0) {
        cout << "Press <Enter> to quit..." << endl;
        break;
    }
    if (choice < 0) choice *= -1;
    doChoice(choice);
  }
}

void doCannon () {
    // Get height of stack of cannonballs
    cout << "What's the height of the stack of cannonballs? ";
    int height = GetInteger();
    if (height < 0) height *= -1;
    int qty = Cannonballs(height);
    cout << "There are " << qty << " cannonballs." << endl;
}

int Cannonballs(int n) {
    if (n==1) {
        return 1;
    }
    else {
        return (n*n + Cannonballs(n - 1));
    }
}

/*
Function: doChoice
Usage: doChoice(choice);
-----------------------------------
This function executes a switch statement to run the proper program.
 */

void doChoice(int choice) {
    switch (choice) {
        case 1: return;
        case 2: return;
        case 3: return;
        case 4: doCannon(); return;
        case 5: return;
        case 6: return;
        case 7: return;
        case 8: return;
        case 9: return;
        default:
            Error("Unexpected case value"); // raises an error msg since no 'return'
    }
    return;
}
