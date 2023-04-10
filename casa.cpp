#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>


float grausParaRadianos(float angulo_graus) {
    return (angulo_graus * 2 * M_PI)/360.0;
}

void desenharCirculo(float raio, float x0, float y0, int definicao, float vermelho, float verde, float azul) {
    int i;
    float passo = grausParaRadianos(360.0/definicao);
    float angulo = passo;
    float x = 0.0, y = 0.0;

    //modo de pintura do objeto
    glShadeModel(GL_FLAT);

    glBegin(GL_POLYGON);
        glColor3f(vermelho, verde, azul);
        for (i = 0; i < definicao; i++) {
            x = raio * cos(angulo) + x0;
            y = raio * sin(angulo) + y0;

            glVertex2f(x, y);

            angulo += passo;
        }
    glEnd();
}

void init(){
	//display cor da janela
	glClearColor(1.0, 1.0, 1.0, 0.0);
	//parâmetro de projeção
	glMatrixMode(GL_PROJECTION);
	//transformação 2d 
	gluOrtho2D(0.0, 1200, 0.0, 900);
}

void home(){

	//Telhado da casa
	glClear(GL_COLOR_BUFFER_BIT);
	
	//definir a cor do telhado
	glColor3f(0.9, 0.6, 0.1);
	glBegin(GL_POLYGON);	   
	glVertex2i(200, 500);
	glVertex2i(600, 500);
	glVertex2i(700, 350);
	glVertex2i(300, 350);
	glEnd();
	
	// Parte superior do telhado frontal
	glColor3f(0.8, 0.4, 0.1);
	glBegin(GL_TRIANGLES);	
	glVertex2i(200, 500);
	glVertex2i(100, 350);
	glVertex2i(300, 350);
	glEnd();
	
	//parede frontal
	       // ( R,  G ,  B)
	glColor3f(0.9, 0.8, 0.2);
	glBegin(GL_POLYGON);
		    //( X , Y)
	glVertex2i(100, 350);
	glVertex2i(300, 350);
	glVertex2i(300, 100);
	glVertex2i(100, 100);
	glEnd();
	
	//parede lateral
	glColor3f(0.9, 0.9, 0.3);
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
	desenharCirculo(10.0, 170, 170, 30, 0.8, 0.3, 0.1);
	glEnd();

	//janela frontal
	desenharCirculo(35.0, 200, 400, 30, 0.3, 0.3, 0.8);
	glEnd();
	
	 //janela 1
    	glColor3f(0.3, 0.3, 0.8);
   	glBegin(GL_POLYGON);
    	glVertex2i(330, 320);
    	glVertex2i(450, 320);
    	glVertex2i(450, 230);
    	glVertex2i(330, 230);
    	glEnd();
    	
    	//janela 2
    	glColor3f(0.3, 0.3, 0.8);
    	glBegin(GL_POLYGON);
    	glVertex2i(530, 320);
    	glVertex2i(650, 320);
    	glVertex2i(650, 230);
    	glVertex2i(530, 230);
    	glEnd();
	
	//chaminé
    	glColor3f(0.5, 0.2, 0.0);
    	glBegin(GL_POLYGON);
 	glVertex2i(375, 530);
    	glVertex2i(425, 530);
    	glVertex2i(425, 500);
    	glVertex2i(375, 500);
    	glEnd();
    	
	//chaminé topo
    	glColor3f(0.5, 0.2, 0.0);
    	glBegin(GL_POLYGON);
	glVertex2i(435, 550);
    	glVertex2i(365, 550);
 	glVertex2i(365, 530);
    	glVertex2i(435, 530);
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
	
	glutDisplayFunc(home);
	
	init();
	
	
	glutMainLoop();

}

// para compilar:
// g++ casa.cpp -o casa -lGL -lGLU -lglut -lm

// para executar:
// ./casa
