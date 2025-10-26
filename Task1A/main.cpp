#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1_, y1_, x2_, y2_;
void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1); // absolute change in x
    int dy = abs(y2 - y1); // absolute change in y

    int sx, sy; // direction er x,y

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

    if (dx > dy) // jodi slope chhoto hoy
    {
        int err = 2 * dy - dx; //decision variable j amra kohon y k move korbo
        int x = x1;
        int y = y1;

        for (int i = 0; i <= dx; i++) // loop shuru korlam  first to last pixel ta draw korar jonno
        {
            drawPixel(x, y);
            x += sx; // ek step right baleft e jabo
            if (err > 0)
            {
                y += sy; //  up ba down one step each
                err -= 2 * dx; // error ta update kortesi
            }
            err += 2 * dy; // error ta abar update kortesi loop theke ber hoye next pixel er jonno
        }
    }
    else // jodi slope boro ba steep hoy
    {
        int err = 2 * dx - dy; // decision variable kokhon amra x k move korbo
        int x = x1;
        int y = y1;

        for (int i = 0; i <= dy; i++)
        {
            drawPixel(x, y);
            y += sy; // ek step up ba down
            if (err > 0)
            {
                x += sx; // ek step right ba left
                err -= 2 * dy; // error ta update kortesi
            }
            err += 2 * dx; // error update kortesi loop theke ber hoye abar for next pixel
        }
    }
    glFlush(); // ekhon pura line ta screen e show korchi glut function ta diye
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); //clear korchi color buffer jeno screen a age kichu theke thakle oi ta remove hoye jai
    glColor3f(0, 0, 0); // line ta black hobe
    bresenhamLine(x1_, y1_, x2_, y2_); // bresenhem function ta call kore line draw korchi
    glFlush(); // screen e dekhabe shob drawings
}

int main(int argc, char** argv)
{
    cout << "Enter x1 y1 x2 y2: ";
    cin >> x1_ >> y1_ >> x2_ >> y2_; // user theke input nichi

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Bresenham Line Drawing");
    gluOrtho2D(0, 700, 0, 700);
    glClearColor(1, 1, 1, 1); // white   background
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
