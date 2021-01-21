#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>

const int SCREEN_WIDTH = 640; // width of screen window in pixels
const int SCREEN_HEIGHT = 480; // height of screen window in pixels


class GLintPoint {
public:
    GLfloat x, y;
};

class Window {
public:
    GLfloat l, b, r, t;
};

void swap_points(GLintPoint* p1, GLintPoint* p2) {
    GLintPoint t = *p1;
    *p1 = *p2;
    *p2 = t;
}

void swap_codes(GLint* x, GLint* y) {
    GLint t = *x;
    *x = *y;
    *y = t;
}

GLint inside(GLint code) {
    return !code;
}

GLint accept(GLint code1, GLint code2) {
    return !(code1 | code2);
}

GLint reject(GLint code1, GLint code2) {
    return code1 & code2;
}

GLint encode(GLintPoint P, Window win) {
    GLint code = 0;

    if (P.x < win.l) code |= 8;
    if (P.x > win.r) code |= 4;
    if (P.y < win.b) code |= 2;
    if (P.y > win.t) code |= 1;
    return code;
}

GLint round(GLfloat a) {
    return (GLint)(a + 0.5f);
}

void ChopLine(GLintPoint p1, GLintPoint p2, Window win) {
    GLint code1, code2;
    GLint done = 0, plot_line = 0;
    GLfloat m = 0;
    if (p1.x != p2.x) {
        m = (p2.y - p1.y) / (p2.x - p1.x);
    }
    while (!done) {
        code1 = encode(p1, win);
        code2 = encode(p2, win);
        if (accept(code1, code2)) {
            done = 1;
            plot_line = 1;
        }
        else if (reject(code1, code2)) {
            done = 1;
        }
        else {
            if (inside(code1)) {
                swap_points(&p1, &p2);
                swap_codes(&code1, &code2);
            }

            if (code1 & 8) {
                p1.y += (win.l - p1.x) * m;
                p1.x = win.l;
            }
            else if (code1 & 4) {
                p1.y += (win.r - p1.x) * m;
                p1.x = win.r;
            }
            else if (code1 & 2) {
                if (p1.x != p2.x)
                    p1.x += (win.b - p1.y) / m;
                p1.y = win.b;
            }
            else if (code1 & 1) {
                if (p1.x != p2.x)
                    p1.x += (win.t - p1.y) / m;
                p1.y = win.t;
            }
        }
    }

    if (plot_line) {
        glColor3f(0, 1, 0);
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex2i(round(p1.x), round(p1.y));
        glVertex2i(round(p2.x), round(p2.y));
        glEnd();
        glFlush();
    }

}

void draw_window(Window win) {

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(round(win.l), round(win.b));
    glVertex2i(round(win.l), round(win.t));
    glVertex2i(round(win.r), round(win.t));
    glVertex2i(round(win.r), round(win.b));
    glEnd();
    glFlush();
}

void draw(GLintPoint List[], Window win, int last) {
    glColor3f(1, 0, 0);

    glBegin(GL_LINES);
    for (int i = 0; i < last; i += 2)
    {
        glVertex2i(round(List[i].x), round(List[i].y));
        glVertex2i(round(List[i + 1].x), round(List[i + 1].y));
    }
    glEnd();
    for (int i = 0; i < last; i += 2)
    {
        ChopLine(List[i], List[i + 1], win);
    }
}

const int NUM = 20;
static GLintPoint List[NUM];
static int last = -1;

Window win;

const int NUM1 = 2;
static GLintPoint win_list[NUM1];
static int last1 = -1; 

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last1 < NUM1 - 1)
    {
        win_list[++last1].x = x; // add new point to list
        win_list[last1].y = SCREEN_HEIGHT - y; // window height is 480
        glClear(GL_COLOR_BUFFER_BIT); // clear the screen
        if (last1 == 1) {
            win = { win_list[0].x,win_list[0].y,win_list[1].x,win_list[1].y };
            draw_window(win);            
        }
    }else
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last1 == 1) {
        last1 = 2;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last < NUM - 1 && last1 == 2)
    {
        List[++last].x = x; // add new point to list
        List[last].y = SCREEN_HEIGHT - y; // window height is 480

        /*glClear(GL_COLOR_BUFFER_BIT); // clear the screen
        glBegin(GL_LINES); // redraw the polyline
        for (int i = 0; i <= last; i++)
            glVertex2i(List[i].x, List[i].y);
        glEnd();
        glFlush();*/
        if (last % 2 != 0)
        {   
            /*int i = last - 1;
            
            glColor3f(1, 0, 0);
            glBegin(GL_LINES);
            glVertex2i(round(List[i].x), round(List[i].y));
            glVertex2i(round(List[i + 1].x), round(List[i + 1].y));
            glEnd();
            ChopLine(List[i], List[i + 1], win);*/
            draw(List,win,last);
            
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        last = -1; // reset the list to empty
}

//Window win = { 150,150,500,300 };

//void myMouse1(int button, int state, int x, int y)
//{
//
//    // last index used so far
//   // test for mouse button as well as for a full array
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last < NUM - 1)
//    {
//
//
//        List[++last].x = x; // add new point to list
//        List[last].y = SCREEN_HEIGHT - y; // window height is 480
//
//        /*glClear(GL_COLOR_BUFFER_BIT); // clear the screen
//        glBegin(GL_LINES); // redraw the polyline
//        for (int i = 0; i <= last; i++)
//            glVertex2i(List[i].x, List[i].y);
//        glEnd();
//        glFlush();*/
//        if (last % 2 != 0)
//        {
//            draw(List, win);
//        }
//
//    }
//    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//        last = -1; // reset the list to empty
//}

void myDisplay() {
    //glClear(GL_COLOR_BUFFER_BIT);

    /*GLintPoint p0 = { 50, 50 };
    GLintPoint p1 = { 500, 320 };
    GLintPoint p2 = { 100, 100 };
    GLintPoint p3 = { 40, 70 };
    GLintPoint p4 = { 260, 160 };
    GLintPoint p5 = { 250, 290 };
    GLintPoint p6 = { 200, 200 };
    GLintPoint p7 = { 400, 30 };
    GLintPoint p8 = { 240, 250 };
    GLintPoint p9 = { 20, 300 };
    GLintPoint myArray[] = { p0,p1,p2,p3,p4,p5,p6,p7,p8,p9 };

    */
    //draw_window(win);

}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    GLint x = mouseX;
    GLint y = SCREEN_HEIGHT - mouseY; // flip the y value as always
    switch (theKey)
    {
    case 'w':
        last = -1;
        last1 = -1;
        
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glutMouseFunc(myMouse);
        break;
    case 'e':
        exit(-1); //terminate the program
    default:
        break; // do nothing
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    //glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
}
