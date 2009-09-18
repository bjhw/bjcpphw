/*
Program uses "Chaos Game" theory to draw a special pattern on the screen.
By default, it uses three points clicked by the user, but a nice extension
would be to allow the user to set the number of points (nPOINTS) to enable
creation of various-sided diagrams.

For additional theory, see:  http://en.wikipedia.org/wiki/Chaos_game

Program requires libraries from 
http://www.stanford.edu/class/cs106b/using-visual-studio.html
http://see.stanford.edu/materials/icspacs106b/PCLibs-VS2005-ADT-Installer.zip
http://see.stanford.edu/materials/icspacs106b/ProgrammingAbstractionsAllMaterials.zip
*/
#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
#include "random.h"

/* Constants */

const int nPOINTS = 3;
const double FILL_RADIUS = 0.01;
const string FILL_COLOR = "Magenta";
const double PT_DENSITY = 1.0;


/*
Type: pointT
------------
A point on the graph as determined by an X- and Y-coordinate.
 */
struct pointT {
    double xp;
    double yp;
};


/* Private function prototypes */

void GetTrianglePoints(pointT tri[]);
void DrawCircle(pointT pt);

/* Main program */

int main() {
    pointT tri[nPOINTS];

    // Get three different points from the user via mouse, connect pts as arrive
    cout << "Click your mouse in three different areas of the canvas." << endl;
    cout << "The points will be connected to form a triangle and then" << endl;
    cout << "the triangle will mysteriously begin to fill." << endl;
	cout << endl;
    cout << "ALERT! Click your mouse in the window to stop the fill process." << endl;

    InitGraphics();
    
    GetTrianglePoints(tri);

    // randomly choose one of the points, i.e. pick an index from 'tri'
    Randomize();
    int vertex;
    vertex = RandomInteger(0, nPOINTS-1);
    pointT cp = tri[vertex];

    while ( ! MouseButtonIsDown() ) {
    //for ( int i = 0; i < 10000; i++ ) {

        // draw a small, filled circle around the current point
        DrawCircle(cp);
        UpdateDisplay();

        // randomly choose any of the perimeter vertices
        vertex = RandomInteger(0, nPOINTS-1);

        // move the current point halfway towards the new point
        cp.xp = ( tri[vertex].xp + cp.xp ) / 2;
        cp.yp = ( tri[vertex].yp + cp.yp ) / 2;
        
    //}
    }

    return 0;
}

/*
Function: DrawCircle
Usage: DrawCircle(pt)
-----------------------------------
Given a pointT point (pt), this function draws a circle of radius FILL_RADIUS
and color FILL_COLOR around that point.
 */
void DrawCircle(pointT pt) {
    SetPenColor(FILL_COLOR);
    StartFilledRegion(PT_DENSITY);
    MovePen(pt.xp + FILL_RADIUS, pt.yp);
    DrawArc(FILL_RADIUS, 0, 360);
    EndFilledRegion();
}

/*
 * Function: GetTrianglePoints
 * Usage: GetTrianglePoints(tri)
 * -----------------------------------
 * This function watches the user click three points on the Graphics Console.
 * The function notes the location of those points by loading the 'tri' array
 * with three pointT structs.
 * The function connects the dots to create a triangle on the screen.
 * Graphics should already be initialized.  We assume working with triangles,
 * but the constant nPOINTS will let us see if this works for four points.
 */
void GetTrianglePoints(pointT tri[]) {
    int pt_ct = 0;
    while ( pt_ct < nPOINTS ) {
        //cout << "got to this point" << endl;
        WaitForMouseDown();
        WaitForMouseUp();
        tri[pt_ct].xp = GetMouseX();
        tri[pt_ct].yp = GetMouseY();
        if ( pt_ct == 0 )
        {
            MovePen(tri[0].xp, tri[0].yp);
        }
        else
        {
            DrawLine(
                (tri[pt_ct].xp - tri[pt_ct - 1].xp ),
                (tri[pt_ct].yp - tri[pt_ct - 1].yp )
                    );
        }
        UpdateDisplay();
        pt_ct ++;
    }

    // Connect the third and first points of the triangle with lines
    DrawLine(
        (tri[0].xp - tri[nPOINTS - 1].xp ),
        (tri[0].yp - tri[nPOINTS - 1].yp )
            );
    UpdateDisplay();
}
