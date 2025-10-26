#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1_, y1_, x2_, y2_, width_;

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

    // ei function ta diye ekta thick pixel banacchi using 8-way symmetry
void drawThickPixel(int x, int y, int w)
{
    int r = w / 2; // line er half width
    for (int dx = 0; dx <= r; dx++)
    {
        for (int dy = 0; dy <= r; dy++)
        {
            if (dx * dx + dy * dy <= r * r)  //dx square  + dy square is less than or equal to r sqaure formula
            {
                //  tahole same pixel 8 side e draw korbo for thickness
                drawPixel(x + dx, y + dy);
                drawPixel(x - dx, y + dy);
                drawPixel(x + dx, y - dy);
                drawPixel(x - dx, y - dy);
                drawPixel(x + dy, y + dx);
                drawPixel(x - dy, y + dx);
                drawPixel(x + dy, y - dx);
                drawPixel(x - dy, y - dx);
            }
        }
    }
}

void thickLine(int x1, int y1, int x2, int y2, int w)
{
    int dx = abs(x2 - x1); // change in x; always positive
    int dy = abs(y2 - y1); //change in y; always positive

    int sx, sy; // direction variables for x and y

    //x kon direction a jabe decide korbo
    if (x1 < x2)
        sx = 1; // move right
    else
        sx = -1; // move left

//y kon direction a jabe decide korbo
    if (y1 < y2)
        sy = 1; // upore e jabe
    else
        sy = -1; // niche jabe

    int err = dx - dy; // decision variable set

    while (true)
    {
        drawThickPixel(x1, y1, w); //thickpixel ta draw kortesi using the width

        if (x1 == x2 && y1 == y2)
            break; // jekhane line sesh 2 ta value e same hoye jai, oikhanei stop

        int e2 = 2 * err; // error double kore check kortesi

        if (e2 > -dy)
        {
            err -= dy;  // error update kortesi by minusing one step
            x1 += sx;   // ek step x direction e
        }

        if (e2 < dx)
        {
            err += dx;  // abar error update kortesi
            y1 += sy;   // ek step y direction e
        }
    }
    glFlush(); // pura line ta screen e show kortesi
}

void display()
    {
        glClear(GL_COLOR_BUFFER_BIT); // clear the screen
        glColor3f(1, 0.93, 0.38); // yellow line
        thickLine(x1_, y1_, x2_, y2_, width_); // thick line ta draw korteis
        glFlush(); // forces the drawing to appear on screen
    }

int main(int argc, char** argv)
    {
        cout << "Enter x1 y1 x2 y2: ";
        cin >> x1_ >> y1_ >> x2_ >> y2_; // user input for line coordinates
        cout << "Enter line thickness (in pixels, e.g., 5, 10, 15): ";
        cin >> width_; // user input for line width
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(800, 600);
        glutCreateWindow("Thick Line (Bresenham 8-way symmetry)");
        gluOrtho2D(0, 800, 0, 600);
        glClearColor(1, 1, 1, 1); // white  background
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;
    }
