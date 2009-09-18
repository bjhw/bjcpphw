#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "random.h"

/* Constants */

const int N_TRIALS = 500;

/* Private function prototypes */

void CollectVotingParams(int *n_voters, double *pct_spread, double *err_pct);
//double CalcChanceOfInvalidElection(int n_voters, double pct_spread, double err_pct);
int CalcChanceOfInvalidElection(int n_voters, double pct_spread, double err_pct);
void RunSim( double err_pct, int votes_X_should_get, int *votes_for_X, int *votes_for_Y );

/* Main program */

int main() {
    int n_voters = 0;
    double pct_spread = 0.0;
    double err_pct = 0.0;
    CollectVotingParams(&n_voters, &pct_spread, &err_pct);

    Randomize();
    //double chance_of_invalid_election
        //= CalcChanceOfInvalidElection(n_voters, pct_spread, err_pct);
    int n_invalid_trials
        = CalcChanceOfInvalidElection(n_voters, pct_spread, err_pct);
    double chance_of_invalid_election
        = 100.0 * n_invalid_trials / N_TRIALS;

    cout << "Chance of an invalid election result after ";
    cout << N_TRIALS << " trials = " << chance_of_invalid_election << "%" << endl;
    //cout << N_TRIALS << " trials = " << chance_of_invalid_election << "%" << endl;
}


/*
 * Function: CollectVotingParams
 * Usage: CollectVotingParams(*n_voters, *pct_spread, *err_pct);
 * -----------------------------------
 * Gathers user's parameters for examining potential voting problems
 *
 */
void CollectVotingParams(int *n_voters, double *pct_spread, double *err_pct) {
    while ( true ) {
        cout << "Enter number of voters: ";
        *n_voters = GetInteger();
        if ( *n_voters > 0 ) {
            break;
        }
    }

    while ( true ) {
        cout << "Enter percentage spread between candidates: ";
        *pct_spread = GetReal();
        if ( *pct_spread > 0 && *pct_spread < 1.0 ) {
            break;
        }
    }

    while ( true ) {
        cout << "Enter voting error percentage: ";
        *err_pct = GetReal();
        if ( *err_pct > 0 && *err_pct < 1.0 ) {
            break;
        }
    }
}

/*
 * Function: CalcChanceOfInvalidElection
 * Usage: CalcChanceOfInvalidElection(n_voters, pct_spread, err_pct);
 * -----------------------------------
 * Calculates chance of an invalid election given user's parameters for
 * examining potential voting problems
 *
 */
//double CalcChanceOfInvalidElection(int n_voters, double pct_spread, double err_pct) {
int CalcChanceOfInvalidElection(int n_voters, double pct_spread, double err_pct) {
    int votes_A_should_get = n_voters * ( 1 + pct_spread ) / 2;
    int votes_B_should_get = n_voters - votes_A_should_get;

    int n_invalid_elections = 0; // tracks num simulations which gen invalid electn
    for ( int i = 1; i <= N_TRIALS; i++ ) {
        int votes_for_A = 0;
        int votes_for_B = 0;

        RunSim( err_pct, votes_A_should_get, &votes_for_A, &votes_for_B );
        RunSim( err_pct, votes_B_should_get, &votes_for_B, &votes_for_A );
        if ( votes_for_B > votes_for_A ) {
            n_invalid_elections ++;
        }
    }

    //return (n_invalid_elections / N_TRIALS);
    return n_invalid_elections;
}

void RunSim( double err_pct, int votes_X_should_get, int *votes_for_X, int *votes_for_Y ) {
    for ( int i = 1; i <= votes_X_should_get; i++ ) {
        if ( RandomChance(1 - err_pct) ) {
            (*votes_for_X)++;
        }
        else {
            (*votes_for_Y)++;
        }
    }
}
