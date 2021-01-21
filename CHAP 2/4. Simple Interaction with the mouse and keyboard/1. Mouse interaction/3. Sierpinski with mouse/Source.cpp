#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <iostream>

const int screenWidth = 640; // width of screen window in pixels
const int screenHeight = 480; // height of screen window in pixels
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
	glColor3f(1.0f, 0.0f, 0.0f); // set the drawing color
	glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
//<<<<<<<<<<<<<<<<<<<<<<<< drawDot >>>>>>>>>>>>>>>>>
void drawDot(int x, int y)
{ // draw dot at integer point (x, y)
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
//<<<<<<<<<<<<<<<<<<<<<<<< GLintPoint >>>>>>>>>>>>>>>>>
class GLintPoint {
public:
	GLint x, y;
};
//<<<<<<<<<<<<<<<<<<<<<<<< random >>>>>>>>>>>>>>>>>
int random(int m) { return rand() % m; }
//<<<<<<<<<<<<<<<<<<<<<<<< Sierpinski >>>>>>>>>>>>>>>>>
void Sierpinski(GLintPoint corners[])
{
	//GLintPoint T[3] = { {10,10},{300,30},{200, 300} };
	int index = random(3); // 0, 1, or 2 equally likely
	GLintPoint point = corners[index]; // initial point
	drawDot(point.x, point.y); // draw initial point
	for (int i = 0; i < 1000; i++) // draw 1000 dots
	{
		index = random(3);
		point.x = (point.x + corners[index].x) / 2;
		point.y = (point.y + corners[index].y) / 2;
		drawDot(point.x, point.y);
	}
	glFlush();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>>
void myMouse(int button, int state, int x, int y)
{
	static GLintPoint corners[3];
	static int numCorners = 0;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		corners[numCorners].x = x;
		corners[numCorners].y = screenHeight - y; // flip y coordinate
		if (++numCorners == 3)
		{
			Sierpinski(corners); // draw the gasket
			numCorners = 0; // back to 0 corners
		}

	}
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	glFlush(); // send all output to display
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(640, 480); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Specifying a rectangle with the mouse"); // open the screen window
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}