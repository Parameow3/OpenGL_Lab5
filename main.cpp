/**
 *
 * Created on 01/06/2023 By: Tan Bunchhay
 */

// require header
#include <math.h>

using namespace std;

// pre-define header
#if __APPLE__
#include <GLUT/glut.h>
#elif _WIN64
#include <GL/glut.h>
#include <iostream>
#endif

using namespace std;

int submenu_Drawing;
int submenu_Color;
int submenu_Width;
int menu;
int valueDrawing = 0;
int valueColor = 0;
int valueWidth = 0;
int ix1,ix2,iy1,iy2;

void display(void);
void init(void);
void selectMenu(int n);
void createMenu();
void reqInput();
void changeLineWidth();
void changeLineColor();


//#region MIDPOINT_ALGORITHM_predefine
void changeLineDrawing();
void ddaLine(int x1, int x2, int y1, int y2);
void midpointLine(int x1, int x2, int y1, int y2);
void midpointCircle(int x, int y, int r);
void pointsCircle(int x, int y, int ix, int iy);
//#endregion


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    menu = glutCreateWindow("Menu");
    createMenu();
    init();
//    reqInput();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

//#region BRONZE_CHALLENGE

void display(void) {
    // clear background of current window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();// Reset the model-view matrix
    gluOrtho2D(0, 500.0, 0, 500.0);

    glColor3f(0,0,0);

    midpointCircle(250, 250, 200);
    changeLineColor();
    changeLineWidth();
    changeLineDrawing();

    glFlush();
}

void init(void) {
    //Clear background color to white
    glClearColor(1.0, 0.8980, 0.8, 0.0);

    //change projection mode
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void selectMenu(int n){
    // if n = 0, exit the program
    if (n == 0)
    {
        glutDestroyWindow(menu);
        exit(0);
    }

    else if(n > 0 && n < 3)
    {
        valueDrawing = n;
    }
    else if(n > 2 && n < 6)
    {
        valueColor = n;
    }
    else if(n > 5 && n < 10)
    {
        valueWidth = n;
    }
    // re-paint display
    glutPostRedisplay();
}

void createMenu(){

    // for line drawing
    submenu_Drawing = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("DDA Line", 1);
    glutAddMenuEntry("Midpoint Line", 2);
    glutAddMenuEntry("Trigonometry Circle", 10);
    glutAddMenuEntry("Midpoint Circle", 11);


    // for line color changing
    submenu_Color = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("Black", 3);
    glutAddMenuEntry("Red", 4);
    glutAddMenuEntry("Blue", 5);

    // for line width changing
    submenu_Width = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("1", 6);
    glutAddMenuEntry("3", 7);
    glutAddMenuEntry("6", 8);
    glutAddMenuEntry("9", 9);


    menu = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu

    glutAddSubMenu("Drawing", submenu_Drawing);
    glutAddSubMenu("Color", submenu_Color);
    glutAddSubMenu("Line Width", submenu_Width);
    glutAddMenuEntry("Exit", 0); // add exit to menu
    // attach menu to the right button of the mouse
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

//#region MIDPOINT_ALGORITHM
void ddaLine(int x1, int x2, int y1, int y2){
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    double x = x1;
    double y = y1;
    double slope, step;
    bool slopeInfinite = false;

    // prevent infinite value
    if (deltaX != 0){
        slope = (double) deltaY / deltaX;
    } else {
        slopeInfinite = true;
    }

    // check slope Infinite
    if (slopeInfinite || slope > 1){
        step = deltaY;
    } else{
        step = deltaX;
    }

    // find increment of x and y
    double xInc = (double) deltaX / step;
    double yInc = (double) deltaY / step;

    glBegin(GL_POINTS);
    for (int i = 0; i < step; ++i) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

void midpointCircle(int ix, int iy, int r){
    int x = 0;
    int y = r;
    double d = (5.0/4.0) - r;
    glBegin(GL_POINTS);
    glVertex2i(ix, iy);
    pointsCircle(x, y, ix, iy);
    while(y > x)
    {
        if(d < 0){
            d += (2*x) + 3; x +=1;
        }
        else{
            d += (2*x) - (2*y) + 5;
            x += 1;
            y -= 1;
        }
        pointsCircle(x, y, ix, iy);
    }
    glEnd();

}

void pointsCircle(int x, int y, int ix, int iy) {
    glVertex2i(x + ix, y + iy);
    glVertex2i(y + iy, x + ix);
    glVertex2i(-x + ix, y + iy);
    glVertex2i(-y + iy, x + ix);
    glVertex2i(-y + iy, -x + ix);
    glVertex2i(-x + ix, -y + iy);
    glVertex2i(x + ix, -y + iy);
    glVertex2i(y + iy, -x + ix);
}

void midpointLine(int x1, int x2, int y1, int y2){
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int decision = (2 * deltaY) - deltaX;
    int dE = 2 * deltaY;
    int dNE = 2 * (deltaY - deltaX);
    int x = x1;
    int y = y1;

    glBegin(GL_POINTS);
    while(x < x2){
        glVertex2i(x, y);
        if (decision <= 0){
            decision += dE;
            x += 1;
        } else{
            decision += dNE;
            x += 1;
            y += 1;
        }
    }
    glEnd();
}

void changeLineDrawing(){
    // DDA LINE
    if(valueDrawing == 1 || valueDrawing == 0){
        ddaLine(ix1, ix2, iy1, iy2);
    }
    // MIDPOINT LINE
    else if (valueDrawing == 2){
        midpointLine(ix1, ix2, iy1, iy2);
    }
}
//#endregion

void changeLineColor(){
    if (valueColor == 3){
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glPopMatrix();
    } else if (valueColor == 4){
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glPopMatrix();
    }
    else if (valueColor == 5){
        glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glPopMatrix();
    }
}

void changeLineWidth(){
    if (valueWidth == 6){
        glPushMatrix();
        glPointSize(1);
        glPopMatrix();
    } else if (valueWidth == 7){
        glPushMatrix();
        glPointSize(3);
        glPopMatrix();
    }
    else if (valueWidth == 8){
        glPushMatrix();
        glPointSize(6);
        glPopMatrix();
    }
    else if (valueWidth == 9){
        glPushMatrix();
        glPointSize(9);
        glPopMatrix();
    }
}

void reqInput(){
    cout << "Please Input:" << endl;
    cout << " x1: "; cin >> ix1;
    cout << "y1: "; cin >> iy1;
    cout << "x2: "; cin >> ix2;
    cout << "y2: "; cin >> iy2;
}