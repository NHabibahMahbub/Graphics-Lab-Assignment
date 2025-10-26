#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Midpoint Circle Algorithm
void drawCircle(int xc, int yc, int r) { //xc, yc circle er centre er x,y coordinates
    int x = 0, y = r;
    int d = 1 - r; // decision value equation, r is the radius

    while (x <= y) {
        // 8-way symmetry if y value is greater than x
        drawPixel(xc + x, yc + y);
        drawPixel(xc - x, yc + y);
        drawPixel(xc + x, yc - y);
        drawPixel(xc - x, yc - y);
        drawPixel(xc + y, yc + x);
        drawPixel(xc - y, yc + x);
        drawPixel(xc + y, yc - x);
        drawPixel(xc - y, yc - x);

        // circle er position check
        if (d < 0) //decision variable jodio 0 er theke boro hoi
            d += 2 * x + 3;   // circle er bhitore
        else {
            d += 2 * (x - y) + 5;  // naile circle er baire, tai y 1 1 kore kombe
            y--;
        }
        x++; // r always x  1 1 kore barbei
    }
}

// gradient color + thickness concentric circles
void drawGradientConcentricCircles(int xc, int yc, int numCircles) {
    int initialRadius = 20;
    int baseThickness = 2;
    float thicknessIncrement = 1.5;

    // color transition red→green→blue
    float r_start = 0.8f, g_start = 0.1f, b_start = 0.1f;
    float r_mid   = 0.0f, g_mid   = 0.7f, b_mid   = 0.0f;
    float r_end   = 0.0f, g_end   = 0.0f, b_end   = 0.8f;

    for (int i = 0; i < numCircles; i++) {
        int radius = initialRadius + i * 20;
        int thickness = baseThickness + i * thicknessIncrement;

        float t = (float)i / (numCircles - 1); // ratio of color gradient

        float r, g, b;
        if (t < 0.5f) {  // jodi circle ta inner theke middle er moddhe hoi
            float t1 = t / 0.5f;  // t ke normalize korchi 0–1 range e
            r = r_start + t1 * (r_mid - r_start); // red
            g = g_start + t1 * (g_mid - g_start);// green barche dhire dhire
            b = b_start + t1 * (b_mid - b_start); // blue kom
        } else {  // jodi circle ta middle theke outer half er moddhe hoi
            float t2 = (t - 0.5f) / 0.5f;   // abar normalize for second half
            r = r_mid + t2 * (r_end - r_mid); // red kome jacche
            g = g_mid + t2 * (g_end - g_mid); // green theke blue e shift hocche
            b = b_mid + t2 * (b_end - b_mid); // blue barche gradually
        }

        glColor3f(r, g, b);  // color set kora holo

        // ekta ekta circle er upor barte thaka thickness diye draw
        for (int t = 0; t < thickness; t++)
            drawCircle(xc, yc, radius + t);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGradientConcentricCircles(250, 250, 7);  // 7 ta circle diye korchi
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Concentric Circles with Increasing Thickness");
    gluOrtho2D(0, 500, 0, 500);
    glClearColor(1, 1, 1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
