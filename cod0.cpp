
// g++ cod0.cpp -o cod0 -lGL -lGLU -lglut -lm


#include <GL/glut.h>

void
reshape(int w, int h)
{
	if (w == 0) w = 1;
	
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100*h/w, 100*h/w, -10, 10);
		
	glMatrixMode(GL_MODELVIEW);
}

void
display(void)
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1.00f, 0.00f, 0.00f);
	
	glBegin(GL_POLYGON);
		//Desenha
		glColor3f(1.00f, 0.00f, 1.00f);
		glVertex3f(80.0f, 60.0f, 0.0f);
		glColor3f(0.00f, 1.00f, 1.00f);
		glVertex3f(30.0f, 40.0f, 0.0f);
		glColor3f(1.00f, 1.00f, 0.00f);
		glVertex3f(60.0f, 40.0f, 0.0f);
	glEnd();	
	
	glutSwapBuffers();
}

void meuInit(int w, int h)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100*h/w, 100*h/w, -10, 10);
		
	glMatrixMode(GL_MODELVIEW);
}

int
main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(650, 200);
	glutCreateWindow("Hello World!");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	meuInit(640, 480);
	
	//glutFullScreen();
	glutMainLoop();
	return 0;						/* ANSI C requires main to return int. */
}
