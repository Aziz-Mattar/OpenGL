#include <stdio.h>   
#include <gl\glut.h>   
#include <gl\GL.h>
#include <iostream>
using namespace std;


const int screenWidth = 640;
const int screenHeight = 480;

class GLintPoint {
public:
	GLint x, y;
};

#define NUM1 50
static GLintPoint List[NUM1];
static int last = -1; // last index used so far
bool flag = false;
int NUM = 0;
GLint ymin, ymax;
float x_line, y_line; 
GLint a, b, c, d;
 
class Edge {
public:
	GLint ymin;
	GLint  ymax;
	float x;
	float slope;
};

void ScanLine(Edge e[]) {
	float* xArray = new float[last]; 
	for (y_line = ymin; y_line < ymax; ++y_line) {
		int newX = 0;
		for (int i = 0; i < NUM; ++i)
			if (y_line >= e[i].ymin && y_line <= e[i].ymax) {
				x_line = e[i].x;
				e[i].x += e[i].slope;
				int j = 0;
				while (j<newX && x_line>xArray[j]) ++j;
				for (d = newX; d > j; --d) xArray[d] = xArray[d - 1];
				xArray[j] = x_line;
				++newX;
			}

		for (int i = 0; i < newX; i += 2) {
			int x;
			glBegin(GL_LINE_LOOP); // redraw the polygon
			for (int i = 0; i <= last; i++)
				glVertex2i(List[i].x, List[i].y);
			glEnd();
			glFlush();
			for (x = xArray[i]; x <= xArray[i + 1]; ++x)
			{
				glBegin(GL_POINTS);
				glVertex2i(x, y_line);
				glEnd();
				glFlush();
			}
				
		}
	}
	glEnd();
}

void Calc(GLintPoint* line) {
	Edge e[50];
	if (last == -1) { last = 0;}

	ymin = line[0].y;
	ymax = ymin;

	for (int i = 0; i < last; ++i) {
		// Finding ymax and ymin
		if (line[i].y > ymax) { ymax = line[i].y; }
		if (line[i].y < ymin) { ymin = line[i].y; }
		
		a = i;
		b = a + 1;
		if (b == last) { b = 0; }
		if (line[a].y < line[b].y) {			
			c = b + 1;
			if (c == last) { c = 0; }
		}
		else {			
			c = a - 1;
			if (c == -1) { c = last - 1; }
			int itmp;
			itmp = a;
			a = b;
			b = itmp;
		}

		e[NUM].ymin = line[a].y;
		e[NUM].ymax = line[b].y;
		e[NUM].x = line[a].x;

		//finding Slope of a line
		e[NUM].slope = (float)(line[b].x - line[a].x) / (float)(line[b].y - line[a].y);
		if (line[c].y > line[b].y) { --e[NUM].ymax; }
		cout << " " << NUM << " ";
		++NUM;
	}		
	//filling
	ScanLine(e);
}

void Draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	if (flag) {		
		Calc(List);
		//ScanLine(e);
	}
	glFlush();
}

void myMouse(int button, int state, int x, int y) {
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last < NUM1 - 1)
	{
		if (flag) {
			flag = false;
			last = -1;
		}
		List[++last].x = x;
		List[last].y = screenHeight - y;
		++last;
		List[last].x = x;
		List[last].y = screenHeight - y;


		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= last; ++i)
			glVertex2i(List[i].x, List[i].y);
		glEnd();
		glFlush();

	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		last = -1;
}

void mykeyboard(unsigned char thekey, int mousex, int mousey)
{
	switch (thekey)
	{
	case 'f':
		flag = true;
		NUM = 0;
		Draw();
		break;
	case 'e':
		exit(-1); //terminate the program

	}
}

void myinit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
	glColor3f(1.0f, 0.0f, 0.0f); // set the drawing color
	glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	glFlush(); // send all output to display
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(640, 480); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("(Polygon Filling) algorithm"); // open the screen window
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay); // register redraw function
	glutKeyboardFunc(mykeyboard);
	myinit();
	glutMainLoop(); // go into a perpetual loop
}