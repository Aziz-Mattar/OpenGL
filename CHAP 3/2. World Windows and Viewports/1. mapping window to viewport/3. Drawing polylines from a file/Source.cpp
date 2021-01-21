#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <math.h>
#include <fstream>
#include <iostream>
using namespace std;
//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}
//---------------- setViewport ------------------
void setViewport(float left, float right, float bottom, float top)
{
	glViewport(left, bottom, (right - left), (top - bottom));
}
//---------------- drawPolyLineFile ------------------
void drawPolylineFile(const char* fileName) {
		fstream inStream;
		inStream.open(fileName, ios::in); // open the file
		if (inStream.fail())
			return;
		glClear(GL_COLOR_BUFFER_BIT); // clear the screen
		GLint numpolys, numLines, x, y;
		inStream >> numpolys; // read the number of polylines
		for (int j = 0; j < numpolys; j++) // read each polyline
		{
			inStream >> numLines;
			glBegin(GL_LINE_STRIP); // draw the next polyline
			for (int i = 0; i < numLines; i++)
			{
				inStream >> x >> y; // read the next x, y pair
				glVertex2i(x, y);
			}
			glEnd();
		}
		glFlush();
		inStream.close();
	}

//---------------- myDisplay ------------------
void myDisplay(void)
{
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
		{
			if ((i + j) % 2 == 0) { // if (i + j) is even
				setWindow(0.0, 640.0, 0.0, 480.0); // right side up window
			}
			else {
				setWindow(0.0, 640.0, 480.0, 0.0); // upside down window
			}
			glViewport(i * 64, j * 44, 64, 44); // set the next viewport
			drawPolylineFile("dino.dat"); // draw it again
		}
	}

}
//---------------- myInit ------------------
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
	glColor3f(1.0f, 0.0f, 0.0f); // set the drawing color
	glPointSize(1.0); // a ‘dot’ is 4 by 4 pixels
}
//---------------- main ------------------
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(640, 480); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Plotting the sinc function – revisited"); // open the screen window
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}