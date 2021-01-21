#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
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
//<<<<<<<<<<<<<<<<<<<<<<<< GLintPoint >>>>>>>>>>>>>>>>>
class GLintPoint {
public:
	GLint x, y;
};
//<<<<<<<<<<<<<<<<<<<<<<<< GLintPointArray >>>>>>>>>>>>>>>>>
class GLintPointArray {
	//const int MAX_NUM = 100;
public:
	int num;
	GLintPoint pt[100];
};


//<<<<<<<<<<<<<<<<<<<<<<<< drawPolyLine >>>>>>>>>>>>>>>>>
void drawPolyLine(GLintPointArray poly, int closed)
{
	glBegin(closed ? GL_LINE_LOOP : GL_LINE_STRIP);
	for (int i = 0; i < poly.num; i++)
		glVertex2i(poly.pt[i].x, poly.pt[i].y);
	glEnd();
	glFlush();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	//drawPolyLine();
	glFlush(); // send all output to display
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(640, 480); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Building a Polyline Drawer"); // open the screen window
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}