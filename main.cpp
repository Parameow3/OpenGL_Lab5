/**
 * menuOpenGL.cpp is a program that plot the wave based on formula Asin(wt + @)
 * Created on 16/03/2023 By: Tan Bunchhay
 */

// require header
#include <math.h>

using namespace std;

// pre-define header
#if __APPLE__
#include <GLUT/glut.h>
#elif _WIN64
#include <GL/glut.h>
#endif


int submenu_AxisColor;
int submenu_UnitColor;
int submenu_Geometric;
int submenu_ObjType;
int submenu_Drawing;
int menu;
int valueAxis = 0;
int valueUnit = 0;
int valueGeoType = 0;
int valueObjType = 0;
int valueDrawing = 0;

//#region BRONZE_CHALLENGE_predefine
void display(void);
void init(void);
void selectMenu(int n);
void createMenu();
void changeAxisColor();
void createAxis();
//#endregion

//#region SILVER_CHALLENGE_predefine
void createUnit();
void changeUnitColor();
void createSinWave();
//#endregion

//#region GOLDEN_CHALLENGE_predefine
void createParabola();
void changeObjType();
void createStar();
//#endregion



int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200);
    menu = glutCreateWindow("Menu");
    createMenu();
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

//#region BRONZE_CHALLENGE

void display(void) {
    // clear background of current window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();// Reset the model-view matrix
    gluOrtho2D(250, 0, 0, 250.0);

    // axis line
    createAxis();

    // unit
    createUnit();

    changeObjType();
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

    else if(n > 0 && n < 4)
    {
        valueAxis = n;
    } else if(n > 3 && n < 7){
        valueUnit = n;
    } else if (n > 6 && n < 10){
        valueGeoType = n;
    }
    else if (n > 9 && n < 13){
        valueObjType = n;
    }
    // re-paint display
    glutPostRedisplay();
}

void createMenu(){
    // for Axis Color
    submenu_AxisColor = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("Blue", 1); // add the blue at the first row of the submenu_AxisColor
    glutAddMenuEntry("Green", 2); // add the green at the second row of the submenu_AxisColor
    glutAddMenuEntry("Yellow", 3); // add the green at the second row of the submenu_AxisColor

    // for Unit Color
    submenu_UnitColor = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("Brown", 4); // add the blue at the first row of the submenu_UnitColor
    glutAddMenuEntry("Cyan", 5); // add the green at the second row of the submenu_UnitColor
    glutAddMenuEntry("White", 6); // add the green at the second row of the submenu_UnitColor

    // for Geometric type
    submenu_Geometric = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("Point", 7); // add the blue at the first row of the submenu_Geometric
    glutAddMenuEntry("+/-", 8); // add the green at the second row of the submenu_Geometric
    glutAddMenuEntry("Line", 9); // add the green at the second row of the submenu_Geometric

    // for Object type
    submenu_ObjType = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("Parabola", 10); // add the blue at the first row of the submenu_Geometric
    glutAddMenuEntry("Sin wave", 11); // add the green at the second row of the submenu_Geometric
    glutAddMenuEntry("Stars", 12); // add the green at the second row of the submenu_Geometric

    // for Object type
    submenu_Drawing = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu
    glutAddMenuEntry("DDA Line", 13);
    glutAddMenuEntry("Midpoint Line", 14);


    menu = glutCreateMenu(selectMenu);
    // the selectColor is the function that will
    // create in order to response when the user
    // select on each item on the menu

    glutAddSubMenu("Object Types", submenu_ObjType);
    glutAddSubMenu("Axis Color", submenu_AxisColor); // add the blue at the first row of the submenu_AxisColor
    glutAddSubMenu("Unit Color", submenu_UnitColor);
    glutAddSubMenu("Geometric Types", submenu_Geometric);
    glutAddSubMenu("Drawing", submenu_Drawing);
    glutAddMenuEntry("Exit", 0); // add exit to menu
    // attach menu to the right button of the mouse
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

// change axis color on selected menu
void changeAxisColor(){
    if (valueAxis == 1){
        glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glPopMatrix();
    }
    else if (valueAxis == 2){
        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glPopMatrix();
    }
    else if (valueAxis == 3){
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glPopMatrix();
    }
}

// create axis
void createAxis(){
    glLineWidth(2); // resize line
    // change color check
    // draw x axis and y axis
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.6f, 1.0f); // blue
    changeAxisColor();
    // draw here
    glVertex2f(10, 125); // end horizontal
    glVertex2f(240, 125); // start horizontal

    // arrow horizontal >
    glVertex2f(10, 125);
    glVertex2f(15, 120);
    glVertex2f(10, 125);
    glVertex2f(15, 130);

    glVertex2f(125, 10); // bottom vertical
    glVertex2f(125, 240); // top vertical

    // arrow vertical ^
    glVertex2f(125, 240);
    glVertex2f(120, 235);
    glVertex2f(125, 240);
    glVertex2f(130, 235);

    glEnd();
}
//#endregion

//#region SILVER_CHALLENGE
void createUnit(){
    // draw x axis and y axis units
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); // black
    changeUnitColor();
    // draw here
    for (int i = 20; i < 240; i += 10) {
        if (i == 130 || i == 120) {

        } else {
            // horizontal unit
            glVertex2f(i, 120);
            glVertex2f(i, 130);
            // vertical unit
            glVertex2f(120, i); // start vertical
            glVertex2f(130, i); // end vertical
        }
    }
    glEnd();

    // display text unit
    glBegin(GL_BITMAP);
    changeUnitColor();
    glRasterPos2i(120, 240);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');

    glRasterPos2i(10, 115);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'x');

    // unit for Quadrant IV axis
    glRasterPos2i(123, 120);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

    char c[] = { '2', '3', '4', '5', '6', '7', '8', '9' };
    int j = 0;
    for (int i = 111; i > 40; i -= 10) {
        glRasterPos2i(i, 115);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[j]);

        glRasterPos2i(137, i - 3);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[j]);

        j++;
    }
    // -10 -11 y axis
    glRasterPos2i(139, 28);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
    glRasterPos2i(139, 18);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');

    // 10 11 x axis
    glRasterPos2i(33, 115);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
    glRasterPos2i(23, 115);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');

    // unit for Quadrant II axis
    j = 0;
    for (int i = 142; i < 215; i += 10) {
        glRasterPos2i(i + 2, 115);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[j]);

        glRasterPos2i(135, i - 3);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[j]);

        j++;
    }

    // -10 -11 x axis
    glRasterPos2i(225, 115);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
    glRasterPos2i(235, 115);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');

    // 10 11 y axis
    glRasterPos2i(137, 219);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
    glRasterPos2i(137, 229);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
}
// change unit color on selected menu
void changeUnitColor(){
    // brown
    if (valueUnit == 4){
        glPushMatrix();
        glColor3f(0.588, 0.294, 0.0);
        glPopMatrix();
    }
        // cyan
    else if (valueUnit == 5){
        glPushMatrix();
        glColor3f(0.0, 1.0, 1.0);
        glPopMatrix();
    }
        // white
    else if (valueUnit == 6){
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();
    }
}

// create sin wave
void createSinWave(){
    if(valueGeoType == 0){
        // Sin Wave in default
        glPointSize(2);
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        for (double x = 28.3; x < 227.3; x += 0.1) {
            double y = 50 * sin(0.3 * x + 180);
            glVertex2f(x, y + 125);
        }
        glEnd();
    } else if (valueGeoType == 7){
        // Sin Wave in point
        glPointSize(4);
        glColor3f(0,0,0);
        glBegin(GL_POINTS);
        for (double x = 28.3; x < 227.8; x += 0.5) {
            double y = 50 * sin(0.3 * x + 180);
            glVertex2f(x, y + 125);
        }
        glEnd();
    } else if (valueGeoType == 8){
        // Sin Wave in +/-
        glPointSize(4);
        glColor3f(0,0,0);
        glBegin(GL_BITMAP);
        bool test = false;
        for (double x = 28.3; x < 228.3; x += 0.5) {
            double y = 50 * sin(0.3 * x + 180);
            if (test){
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '+');
            } else{
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
            }
            glRasterPos2f(x, y + 125);
            test = !test;
        }
        glEnd();
    } else if (valueGeoType == 9){
        // Sin Wave in line
        glLineWidth(2);
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        for (double x = 29; x < 228; x += 3) {
            double y = 50 * sin(0.3 * x + 180);
            glVertex2f(x, y + 125);
        }
        glEnd();
    }
}
//#endregion

//#region GOLDEN_CHALLENGE
void createParabola(){
    if(valueGeoType == 0){
        // draw parabola default
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f); // black

        for(double x = 125; x < 140; x+= 0.0001){
            double y = pow(x - 125, 2);
            glVertex2f(x, y + 125);
        }

        for(double x = 125; x > 110; x-= 0.0001){
            double y = pow(x - 125, 2);
            glVertex2f(x, y + 125);
        }
        glEnd();
    } else if (valueGeoType == 7){
        // draw parabola in point
        glPointSize(3);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f); // black

        for(double x = 125; x < 140; x+= 0.5){
            double y = pow(x - 125, 2);
            glVertex2f(x, y + 125);
        }

        for(double x = 125; x > 110; x-= 0.5){
            double y = pow(x - 125, 2);
            glVertex2f(x, y + 125);
        }
        glEnd();
    } else if (valueGeoType == 8){
        // Sin Wave in +/-
        glColor3f(0,0,0);
        glBegin(GL_BITMAP);
        bool test = false;
        for (double x = 125; x < 140; x+= 0.5) {
            double y = pow(x - 125, 2);
            if (test){
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '+');
            } else{
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
            }
            glRasterPos2f(x, y + 125);
            test = !test;
        }

        for (double x = 125; x > 110; x-= 0.5) {
            double y = pow(x - 125, 2);
            if (test){
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '+');
            } else{
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
            }
            glRasterPos2f(x, y + 125);
            test = !test;
        }
        glEnd();
    } else if (valueGeoType == 9){
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f); // black

        for(double x = 125; x < 140; x+= 0.5){
            double y = pow(x - 125, 2);
            glVertex2f(x, y + 125);
        }

        for(double x = 125; x > 110; x-= 0.5){
            double y = pow(x - 125, 2);
            glVertex2f(x, y + 125);
        }
        glEnd();
    }
}
void createStar(){
    if(valueGeoType == 0){
        // Sin Wave in default
        glColor3f(1,0,0);
        glPointSize(5);
        glBegin(GL_TRIANGLES);
        glVertex2f(125, 190);
        glVertex2f(190, 90);
        glVertex2f(60, 90);

        glVertex2f(125, 60);
        glVertex2f(190, 160);
        glVertex2f(60, 160);
        glEnd();
    }
}
void changeObjType(){
    if (valueObjType == 0) {
        createSinWave();
    }
    else if ( valueObjType == 10){
        createParabola();
    }
    else if (valueObjType == 11){
        createSinWave();
    } else if (valueObjType == 12){
        createStar();
    }
}
//#endregion