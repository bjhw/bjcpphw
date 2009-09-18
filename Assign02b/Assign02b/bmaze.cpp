/*
 * Project: Assign02b
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: Brig Johnson
 * Section: Independent
Program draws a maze using Aldous-Broder algorithm and CS106B maze.h
Then it solves the maze using breadth-first algorithm.
 */

#include "genlib.h"
#include <iostream>
#include <fstream>
#include "map.h"  
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "simpio.h" 
#include "random.h" 
#include "maze.h"
#include "brig_lib.h"
#include "windows.h"
#include "time.h"

/* Constants */

//const int nROWS = 3;
//const int nCOLS = 4;
const int nROWS = 15;
const int nCOLS = 20;
const int xMAX = nCOLS - 1;
const int yMAX = nROWS - 1;
//const int xMAX = nROWS - 1;
//const int yMAX = nCOLS - 1;


/*
 * Type: pointT
 * ------------
 * The type pointT is used to encapsulate a pair of integer
 * coordinates into a single value with row and col components.
 * This Type is officially defined in 'maze.h'.

struct pointT { 
	int row; 
	int col; 
};

 */


/*
 * Type: pathT
 * ------------
 * The type pathT encapsulates a pair of containers.  The first container
 * is a stack of pointT pts that traces a path from the origin to the finish.
 * The second container is the set of all such points, intended for easy
 * reference as to whether a given point is already a member of the set.
 */

struct pathT { 
	Stack<pointT> trail;
	Set<int> pts;
};

/*
Debugging option: traceFlag
---------------------------
Controls whether the program produces a debugging trace during build/find modes.
*/

static bool traceFlag_build = false;
static bool traceFlag_find  = false;


/* Private function prototypes */

void BuildMaze(Maze &m);
void SeedCP(pointT &cp);
int ComparePts(pointT a, pointT b);
int GetPtNum(pointT pt);
pointT GetValidNeighborPt(pointT cp);
bool PointIsValid(pointT cp, int dir);
pointT GetNP(pointT cp, int dir);
void ProcessQueueLeader(Maze &m, Queue<pathT> &path);
void Create_new_pathT_w_np(pathT &orig_trail, pathT &new_trail, pointT &np);

int InitTrail(Queue<pathT> &path);

/* Main program */

int main ()
{
  Randomize();

  while (true) {
    // initialize empty maze with walls
    Maze m(nROWS, nCOLS, true);
    m.draw();

    // Build out the maze...
    BuildMaze(m);

    // Now solve the maze...
    pointT stop_pt;

    Queue< pathT > path;
    int stop_pt_num = InitTrail(path);

    if (traceFlag_find) {
        cout << "First pt in queue is ";
        cout << GetPtNum(path.peek().trail.peek()) << endl;
        cout << "Stop pt is " << stop_pt_num << endl;
    }

    Stack<pointT> soln;
    while (true) {
        // If no more paths and we haven't yet found a solution, then there are
        // no solutions to this maze.  Say so and get out.
        if (path.isEmpty()) {
            cout << "The maze seems to have no solutions." << endl;
            break;
        }

        // Go to the queue, peek at the leading record.  If its trail points
        // at the stop_point, we have a solution trail.  Make note and get out.
        if (stop_pt_num == GetPtNum(path.peek().trail.peek()) ) {
            soln = path.peek().trail;
            break;
        }

        ProcessQueueLeader(m, path);
        
        //break;
    }

    Stack<pointT> soln_orig = soln;
    Stack<pointT> soln_proper;

    if (traceFlag_find) {
        if (path.isEmpty()) {
            cout << "The maze seems to have no solutions. 2" << endl;
        }
        else {
            Stack<int> soln_proper_text;
            Stack<pointT> solnS = soln;
            cout << "A valid path appears to be:" << endl;
            while (!solnS.isEmpty()) {
                soln_proper_text.push( GetPtNum(solnS.pop()) );
            }
            while (!soln_proper_text.isEmpty()) {
                cout << soln_proper_text.pop() << endl;
            }
        }
    }

    cout << "Would you like to see the solution?  Type 1 for 'yes', 0 for no: ";
    if (GetInteger()) {
        // reverse the solution stack in order to play it out in the proper order
        while (!soln_orig.isEmpty())
            soln_proper.push(soln_orig.pop());
        while (!soln_proper.isEmpty()) {
            m.drawMark(soln_proper.pop(), "Blue");
            Sleep(100);
        }
    }


    cout << "Would you like to see another maze?  Type 1 for 'yes', 0 for no: ";
    if (!GetInteger()) {
        cout << "Thanks for playing.  Press 'Enter' to exit." << endl;
        break;
    }
  }
  return 0;
}

void ProcessQueueLeader(Maze &m, Queue<pathT> &path) {
    // peek at the tip of the queue's stack and designate that point as "current".
    // Examine the points around it for accessibility, and for each accessible
    // point, invent a new trail and set of 'used' points and enqueue to 'path'.
    pointT cp = path.peek().trail.peek();
    for (int dir = 0; dir <= 3; dir++) {
        pointT np = GetNP(cp, dir); // determine the next point in "that" direction
        if (!m.pointInBounds(np)) {
            // point is out of bounds so ignore it...
        }
        else if (m.isWall(cp, np)) {
            // There's a wall between current and next point, so the np is invalid
        }
        else if ( path.peek().pts.contains(GetPtNum(np)) ) {
            // point already in trail, so avoid circular consideration of same pt
        }
        else {
            pathT new_trail;
            Create_new_pathT_w_np(path.peek(), new_trail, np);
            path.enqueue(new_trail);
        }
    }
    // Once we have investigated possible points of forward progress, delete
    // the old stack that got us to this point.  We either have one, two, or
    // three new stacks or we have hit a dead end.  In any case, the old stack
    // has served its purpose and should be discarded.
    path.dequeue();
}


void Create_new_pathT_w_np(pathT &orig_trail, pathT &new_trail, pointT &np) {
    // Given an original trail (stack + set) and a new trail, copy the
    // original to be the base of the new and then add the new point to the new.
    new_trail.trail = orig_trail.trail;
    new_trail.pts   = orig_trail.pts;

    new_trail.trail.push(np);
    new_trail.pts.add(GetPtNum(np));
}


int InitTrail(Queue<pathT> &path) {
    // Initialize the solution-building state.  Declare point (0,0) as origin,
    // make the origin the single point on a possible solution, and configure
    // the "goal" point that, when reached, indicates a solution.
    pointT start_pt;
    start_pt.row = 0;
    start_pt.col = 0;
    int point_num = GetPtNum(start_pt);

    pathT first_trail;
    first_trail.trail.push(start_pt);
    first_trail.pts.add(point_num);
    path.enqueue(first_trail);

    pointT stop_pt;
    stop_pt.row = yMAX;
    //stop_pt.row = 0;
    stop_pt.col = xMAX;
    return (GetPtNum(stop_pt));
}


void BuildMaze(Maze &m) {
    // pick a random point
    pointT cp;
    SeedCP(cp);

    // add cp to set incPts
    Set<pointT> incPts(ComparePts);
    incPts.add(cp);

    int numPts = nROWS * nCOLS;
    while (incPts.size() < numPts) {
        // get a valid neighbor point
        pointT np = GetValidNeighborPt(cp);

// cout << "cp is " << GetPtNum(cp) << " and np is " << GetPtNum(np) << endl;
// if (m.pointInBounds(np))
// cout << "maze says np is in bounds" << endl;
// cout << "So there." << endl;

        // if neighbor !included, remove wall and add neighbor to incPts
        if (!incPts.contains(np)) {
            m.setWall(cp, np, false); // draws new state of wall, i.e. removes it
            incPts.add(np);
        }

        // neighbor becomes new cp
        cp = np;

        //m.draw();
    }
}

void SeedCP(pointT &cp) {
    cp.row = RandomInteger(0, yMAX);
    cp.col = RandomInteger(0, xMAX);
}

int ComparePts(pointT a, pointT b) {
    if (GetPtNum(a) < GetPtNum(b)) return -1;
    else if (GetPtNum(a) == GetPtNum(b)) return 0;
    else return 1;
}

int GetPtNum(pointT pt) {
    return (pt.row * 100  +  pt.col);
}

pointT GetValidNeighborPt(pointT cp) {
    // in integer form of Java's 'toString' method.  We need a number to
    // represent the point.  This methodology multiplies row by 100 and adds
    // the result to the value for the column.  Assumes that there won't be
    // more than 100 columns since it only multiplies rows by 100 to
    // create the 'row' portion of the impending integer..
    int dir = -1;
    if (traceFlag_build) cout << "get dir: ";

    while (!PointIsValid(cp, dir)) {
        dir = RandomInteger(0, 3);
        if (traceFlag_build) cout << dir << " ";
    }
    if (traceFlag_build) cout << " dir is " << dir << endl;

    pointT np = GetNP(cp, dir);
    return np;
}

// Hmm, maybe should have used 'pointInBounds'
bool PointIsValid(pointT cp, int dir) {
    if (cp.row == yMAX && dir == 0) return false;
    if (cp.col == xMAX && dir == 1) return false;
    if (cp.row == 0    && dir == 2) return false;
    if (cp.col == 0    && dir == 3) return false;
    if (dir < 0) return false;
    return true;
}

pointT GetNP(pointT cp, int dir) {
    pointT np;
    switch (dir) {
        case 0: np.row = cp.row + 1; np.col = cp.col    ; break;  // go North
        case 2: np.row = cp.row - 1; np.col = cp.col    ; break;  // go South
        case 1: np.row = cp.row;     np.col = cp.col + 1; break;  // go East
        case 3: np.row = cp.row;     np.col = cp.col - 1; break;  // go West
        default: // trigger Error
            break;
    }
    return np;
}
