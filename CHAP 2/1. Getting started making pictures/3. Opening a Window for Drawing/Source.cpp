// appropriate #includes go here – see Appendix 1
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(640, 480); // set window size
	glutInitWindowPosition(100, 150); // set the window position on screen
	glutCreateWindow("my first attempt"); // open the screen window
	// register the callback functions
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	myInit(); // additional initializations as necessary
	glutMainLoop(); // go into a perpetual loop
}