#include<GL/glut.h>

void init(){
	//display cor da janela
	glClearColor(0.5, 0.9, 0.4, 0.0);
	//parâmetro de projeção
	glMatrixMode(GL_PROJECTION);
	//transformação 2d 
	gluOrtho2D(0.0, 1200, 0.0, 900);
}

void home(){

	//Telhado da casa
	glClear(GL_COLOR_BUFFER_BIT);
	
	//definir a cor do telhado
	glColor3f(0.3, 0.5, 0.8);
	glBegin(GL_POLYGON);	   
	glVertex2i(200, 500);
	glVertex2i(600, 500);
	glVertex2i(700, 350);
	glVertex2i(300, 350);
	glEnd();
	
	// Parte superior do telhado frontal
	glColor3f(0.5, 0.2, 0.0);
	glBegin(GL_TRIANGLES);	
	glVertex2i(200, 500);
	glVertex2i(100, 350);
	glVertex2i(300, 350);
	glEnd();
	
	//parede frontal
	       // ( R,  G ,  B)
	glColor3f(0.04, 0.1, 0.2);
	glBegin(GL_POLYGON);
		    //( X , Y)
	glVertex2i(100, 350);
	glVertex2i(300, 350);
	glVertex2i(300, 100);
	glVertex2i(100, 100);
	glEnd();
	
	//parede lateral
	glColor3f(0.1, 0.2, 0.3);
	glBegin(GL_POLYGON);
		   // ( X , Y)
	glVertex2i(300,350);
	glVertex2i(700, 350);
	glVertex2i(700, 100);
	glVertex2i(300, 100);
	glEnd();
	
	//porta
	glColor3f(0.5, 0.2, 0.0);
	glBegin(GL_POLYGON);
		    //( X , Y)
	glVertex2i(150, 250);
	glVertex2i(250, 250);
	glVertex2i(250, 100);
	glVertex2i(150, 100);
	glEnd();
	
	//maçaneta da porta da frente
        glColor3f(0.3, 0.7, 0.9);
        glPointSize(15);
        glBegin(GL_POINTS);
        glVertex2i(170, 170);
        glEnd();
	
	 //janela 1
    	glColor3f(0.8, 0.8, 0.1);
   	glBegin(GL_POLYGON);
    	glVertex2i(330, 320);
    	glVertex2i(450, 320);
    	glVertex2i(450, 230);
    	glVertex2i(330, 230);
    	glEnd();
    	//linha da janela 1
    	glColor3f(0.1, 0.1, 0.1);
    	glLineWidth(5);
    	glBegin(GL_LINES);
    	glVertex2i(390, 320);
    	glVertex2i(390, 230);
    	glVertex2i(330, 273);
    	glVertex2i(450, 273);
    	glEnd();
    	//janela 2
    	glColor3f(0.8, 0.8, 0.1);
    	glBegin(GL_POLYGON);
    	glVertex2i(530, 320);
    	glVertex2i(650, 320);
    	glVertex2i(650, 230);
    	glVertex2i(530, 230);
    	glEnd();
    	//linha da janela 2
    	glColor3f(0.1, 0.1, 0.1);
    	glLineWidth(5);
    	glBegin(GL_LINES);
    	glVertex2i(590, 320);
    	glVertex2i(590, 230);
    	glVertex2i(530, 273);
    	glVertex2i(650, 273);
    	glEnd();

    	//caminho de entrada
    	glColor3f(0.3, 0.5, 0.7);
    	glLineWidth(3);
    	glBegin(GL_POLYGON);
    	glVertex2i(150, 100);
    	glVertex2i(250, 100);
    	glVertex2i(210, 0);
    	glVertex2i(40, 0);
    	glEnd();
	
	
	glFlush();
}

int main(int argc, char ** argv){
	//inicializa glut
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowPosition(100, 100);
	
	glutInitWindowSize(800, 600);
	
	glutCreateWindow("Casa 2D");
	
	
	init();
	glutDisplayFunc(home);
	
	glutMainLoop();

}

// para compilar no ubuntu :
// gcc house.c -lglut -lGL -lGLU -lm

// para executar :
// ./a.out
