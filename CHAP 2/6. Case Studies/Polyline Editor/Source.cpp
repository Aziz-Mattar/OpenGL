#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <iostream>

const int screenWidth = 640; // width of screen window in pixels
const int screenHeight = 480; // height of screen window in pixels
boolean flag = false;
static int last = -1; // last index used so far


//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // background color is white
	glColor3f(0.0f, 0.0f, 0.0f); // drawing color is black
	glPointSize(10.0); // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION); // set "camera shape"
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}
//<<<<<<<<<<<<<<<<<<<<<<<< GLintPoint >>>>>>>>>>>>>>>>>
class GLintPoint {
public:
	GLint x, y;
};
//<<<<<<<<<<<<<<<<<<<<<<<< GLintPointArray >>>>>>>>>>>>>>>>>
class GLintPointArray {
public:
	int num;
	GLintPoint pt[100];
};
static GLintPointArray List;
//<<<<<<<<<<<<<<<<<<<<<<<< drawPolyLine >>>>>>>>>>>>>>>>>
void drawPolyLine(GLintPointArray poly, int closed)
{
	glBegin(closed ? GL_LINE_LOOP : GL_LINE_STRIP);
	for (int i = 0; i <= last; i++)
		glVertex2i(poly.pt[i].x, poly.pt[i].y);
	glEnd();
	glFlush();
}

//<<<<<<<<<<<<<<<<<<<<<<<< findPoly >>>>>>>>>>>>>>>>>
int findPoly(int x, int y) {
	for (int i = 0; i <= last; i++)
	{
		if (List.pt[last].x == x && List.pt[last].y == screenHeight - y) {
			return last;			
		}
		else return -1;		
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<< createPolyline >>>>>>>>>>>>>>>>>
void createPolyline(int button, int state, int x, int y)
{

#define NUM 20
	// test for mouse button as well as for a full array
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last < NUM - 1 && flag == true)
	{
		++last;
		List.pt[last].x = x;
		List.pt[last].y = screenHeight - y;
		glClear(GL_COLOR_BUFFER_BIT); // clear the screen
		drawPolyLine(List, 0);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		last = -1; // reset the list to empty
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

}
//<<<<<<<<<<<<<<<<<<<<<<<< deleteLine >>>>>>>>>>>>>>>>>
void deleteLine(int button, int state, int x, int y) {
	int del = findPoly(x, y);
	if (del !=-1) {
		for (int i = del; i < last - 1; i++)
		{
			List.pt[i].x = List.pt[i + 1].x;
			List.pt[i].y = List.pt[i + 1].y;
		}
	}	
}
//<<<<<<<<<<<<<<<<<<<<<<<< movePolyline >>>>>>>>>>>>>>>>>
void movePolyline(int x, int y) {
	int move = findPoly(x, y);
	if (move != -1) {
		List.pt[move].x = x;
		List.pt[move].y = screenHeight - y;
		drawPolyLine(List, 0);
	}
}
//<<<<<<<<<<<<<<<<<<<<<<<< eraseScreen >>>>>>>>>>>>>>>>>
void eraseScreen() {
	drawPolyLine(List, 0);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	GLint x = mouseX;
	GLint y = screenHeight - mouseY; // flip the y value as always
	switch (theKey)
	{
	case 'b':		//create a new polyline
		flag = true;
		glutMouseFunc(createPolyline);
		break;

	case 'd':		//delete the next point pointed to
		flag = true;
		glutMouseFunc(deleteLine);
		drawPolyLine(List, 0);
		break;

	case 'm':		//drag the point pointed to new location
		flag = false;
		glutMotionFunc(movePolyline);		
		break;

	case 'r':		//erase the screen and redraw all the polylines		
		flag = true;
		eraseScreen();
		break;

	case 'q':		//exit from the program
		exit(-1);
	default:		// do nothing
		break;
	}
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	//drawPolyLine(List, 0);
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
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}