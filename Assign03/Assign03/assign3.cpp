#include <iostream>
#include "genlib.h"
#include "simpio.h"

/* Private function prototypes */

void doChoice(int choice);
void doWarmupBinary();
void PrintInBinary(int num);

/* Main program */

int main() {
  while (true) {
    // Get pgm to run
    cout << "Which program would you like to run?" << endl;
    cout << "1: warmup binary" << endl;
    int choice = GetInteger();
    if (choice == 0) {
        cout << "Press <Enter> to quit..." << endl;
        break;
    }
    if (choice < 0) choice *= -1;
    doChoice(choice);
  }
}

void doWarmupBinary () {
    // Determine binary representation of a decimal number
    cout << "What's the decimal that should be turned into binary? ";
    int num = GetInteger();
    if (num < 0) num *= -1;
    PrintInBinary(num);
    cout << endl;
}

void PrintInBinary(int num) {
    if (num == 0 || num == 1) {
        cout << num;
    }
    else {
        int digit = num % 2;
        int half = num / 2;
        PrintInBinary(half);

        cout << digit;
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
        case 1: doWarmupBinary(); return;
        case 2: return;
        case 3: return;
        case 4: return;
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
