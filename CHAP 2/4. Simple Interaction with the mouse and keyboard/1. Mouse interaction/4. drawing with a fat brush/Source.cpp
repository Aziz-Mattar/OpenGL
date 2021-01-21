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
//<<<<<<<<<<<<<<<<<<<<<<<< myMovedMouse >>>>>>>>>>>>>>>>>
void myMovedMouse(int mouseX, int mouseY)
{
	GLint x = mouseX; //grab the mouse position
	GLint y = screenHeight - mouseY; // flip it as usual
	GLint brushSize = 10;
	glRecti(x, y, x + brushSize, y + brushSize);
	glFlush();
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
	glutMotionFunc(myMovedMouse);
	glutDisplayFunc(myDisplay); // register redraw function
	myInit();
	glutMainLoop(); // go into a perpetual loop
}