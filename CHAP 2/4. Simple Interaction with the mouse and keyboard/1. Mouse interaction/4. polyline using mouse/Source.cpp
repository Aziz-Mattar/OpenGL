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
	glPointSize(4.0); // a �dot� is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
//<<<<<<<<<<<<<<<<<<<<<<<< GLintPoint >>>>>>>>>>>>>>>>>
class GLintPoint {
public:
	GLint x, y;
};

//<<<<<<<<<<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>>
void myMouse(int button, int state, int x, int y)
{
#define NUM 20
	static GLintPoint List[NUM];
	static int last = -1; // last index used so far
	// test for mouse button as well as for a full array
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last < NUM - 1)
	{
		List[++last].x = x; // add new point to list
		List[last].y = screenHeight - y; // window height is 480
		glClear(GL_COLOR_BUFFER_BIT); // clear the screen
		glBegin(GL_LINE_STRIP); // redraw the polyline
		for (int i = 0; i <= last; i++)
			glVertex2i(List[i].x, List[i].y);
		glEnd();
		glFlush();
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		last = -1; // reset the list to empty
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
	glutCreateWindow("create a polyline using the mouse"); // open the screen window
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}