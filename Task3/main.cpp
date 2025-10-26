#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

struct Line
{
    float x1, y1, x2, y2;
};

float xmin = 100, ymin = 100, xmax = 400, ymax = 300; // minimum and maximum of clipping window

vector<Line> lines;  // input lines gula vector a rakha

void drawRect()   // rectangle draw  using the min max windows
{
    glBegin(GL_LINE_LOOP); // instead of 8 coordinates, jokhon line lop use kori tokhon 4 ta coordinates diyey rectangle aka hoye jai
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}

// line er visibility check (fully, partially, or not visible)
bool clipTest(float p, float q, float &u1, float &u2)
{
    float r;
    if (p == 0 && q < 0) return false;  // parallel and outside line then not clipped
    if (p != 0)   //if not parallel
    {
        r = q / p;  // intersection ratio
        if (p < 0)   // p value 0 er cheye kom mane line ta window er bhitore dhuktese
        {
            if (r > u2) return false; // jodi r value beshi hoi tahole line ta pura baire
            else if (r > u1) u1 = r;  // entry point eikhane update
        }
        else if (p > 0)   // p value 0 er cheye boro hole line ta window theke ber hocche
        {
            if (r < u1) return false; // r value chhoto mane line already baire chole geche
            else if (r < u2) u2 = r;  // exit point eikhane update
        }

    }

return true;
}


void liangBarsky(Line l)
{
    float dx = l.x2 - l.x1, dy = l.y2 - l.y1;  // x,y direction change
    float u1 = 0.0, u2 = 1.0;  // parameter limits (start & end)

    // checking 4 boundaries of the rectangle  (left, right, bottom, top)
    if (clipTest(-dx, l.x1 - xmin, u1, u2))
        if (clipTest(dx, xmax - l.x1, u1, u2))
            if (clipTest(-dy, l.y1 - ymin, u1, u2))
                if (clipTest(dy, ymax - l.y1, u1, u2))
                {

                    // visible line er new start & end point
                    float nx1 = l.x1 + u1 * dx;
                    float ny1 = l.y1 + u1 * dy;
                    float nx2 = l.x1 + u2 * dx;
                    float ny2 = l.y1 + u2 * dy;

                    glColor3f(1, 0, 1);  // visible part er color pink
                    glBegin(GL_LINES);
                    glVertex2f(nx1, ny1);
                    glVertex2f(nx2, ny2);
                    glEnd();
                }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0);
    drawRect();  //
    glColor3f(0, 0.4, 1);  //original unclipped line er color blue

    for (auto l : lines)    // sob line draw korchi for-loop chaliye
    {
        glBegin(GL_LINES);
        glVertex2f(l.x1, l.y1);
        glVertex2f(l.x2, l.y2);
        glEnd();
    }

    // visible part ta draw
    for (auto l : lines)
        liangBarsky(l);

    glFlush(); //screen a dekhabe
}

int main(int argc, char** argv)
{
    int n;
    cout << " -------------Liang-Barsky Line Clipping-------------\n\n";
    cout << "Rectangle coordinates of clipping are: xmin=" << xmin << ", ymin=" << ymin
         << ", xmax=" << xmax << ", ymax=" << ymax << "\n\n";


    cout << "***How to Enter Your Lines*** \n\n";
    cout << "1. Entirely Inside: Provide both endpoints fully within the rectangle. Example: 150 150 350 250\n";
    cout << "2. Completely Outside: Provide both endpoints outside the rectangle with no crossing. Example: 10 10 50 50\n";
    cout << "3. Partially Crossing: Provide one endpoint inside and one outside, or crossing the rectangle. Example: 50 150 450 250\n\n";

    cout << "Enter number of lines: ";
    cin >> n;

    lines.resize(n); //lines vector ta ready kra for n lines
    for (int i = 0; i < n; i++)
    {
        cout << "Line " << i + 1 << " - Enter x1 y1 x2 y2: ";
        cin >> lines[i].x1 >> lines[i].y1 >> lines[i].x2 >> lines[i].y2; //user inputs
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutCreateWindow("Liang-Barsky Line Clipping");
    gluOrtho2D(0, 500, 0, 400);
    glClearColor(1, 1, 1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
