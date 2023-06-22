#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define Pi 3.14159265358979323846

int lastMouseX;
int lastMouseY;
float cameraRotationX = 0.0f;
float cameraRotationY = 0.0f;
float ang_perna = 90.0f;
float ang_braco = 35.0f;
float ang_gravata = 45.0f;
float cameraX = 0.0;
float cameraY = 0.0;
float cameraZ = 5.0;

void drawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC){
	float tStep = (Pi) / (float)uiSlices;
	float sStep = (Pi) / (float)uiStacks;
	
	//Essa linha desenha em modo wireframe, caso queiram ver os polígonos criados pela função
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	for(float t = -Pi/2; t <= (Pi/2)+.0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -Pi; s <= Pi+.0001; s += sStep)
		{
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glVertex3f(fA * cos(t+tStep) * cos(s), fB * cos(t+tStep) * sin(s), fC * sin(t+tStep));
		}
		glEnd();
	}
}    

void drawSolidCylinder(float radius, float height, int slices, int stacks) {
    float sliceAngle = 2.0 * M_PI / slices;
    float stackHeight = height / stacks;

    // Desenhar lados do cilindro
    for (int i = 0; i < stacks; i++) {
        float stackTop = i * stackHeight;
        float stackBottom = (i + 1) * stackHeight;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; j++) {
            float angle = j * sliceAngle;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            glVertex3f(x, stackTop, y);
            glVertex3f(x, stackBottom, y);
        }
        glEnd();
    }

    // Desenhar bases do cilindro
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0);
    for (int j = 0; j <= slices; j++) {
        float angle = j * sliceAngle;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, 0.0, y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, height, 0.0);
    for (int j = slices; j >= 0; j--) {
        float angle = j * sliceAngle;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, height, y);
    }
    glEnd();
}

//Aqui se capturam as teclas especiais (Alt, Control, Shift, F1, F2, etc.)
void myKeyboardSpecial(int key, int x, int y ) {
  switch ( key ) {
    case GLUT_KEY_UP:                   // Quando a seta para cima é teclada...
      glutFullScreen ( );               // Vá para o modo tela cheia...
      break;
    case GLUT_KEY_DOWN:                 // Quando a seta para baixo for teclada...
      glutReshapeWindow ( 640, 480 );   // Vá para modo em janela de 640 por 480
      break;
    default:
      printf("Você apertou a tecla especial código: %d\n", key);  // ...para ajudar você a debugar...       
      break;
  }
}

// Função de callback para atualização do movimento do mouse
void handleMouseMovement(int x, int y) {
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;
    
    // Atualiza as rotações da câmera
    cameraRotationY += deltaX * 0.3f;
    cameraRotationX += deltaY * 0.3f;
    
    // Atualiza as posições do mouse
    lastMouseX = x;
    lastMouseY = y;
    
    glutPostRedisplay(); // Solicita o redesenho da cena
}

void init(void) 
{
  // Define a cor de fundo da janela de visualização como preto
  glClearColor (0.27, 0.61, 0.82, 0.0);
  // Define o modo de rastreio de cor utilizado para misturar a cor do material nos pontos da face (smoothing)
  glShadeModel (GL_SMOOTH);
  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);

  //Parâmetros para a luz ambiente, difusa e especular, definindo também a posição da luz
  GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

  // Passa os parâmetros definidos acima para a OpenGL
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  // Habilita a luz ambiente, a luz zero e o depth buffer
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  //Primeira cor, para depois mudarmos com os eventos
  glColor3f(0.5, 1.0, 0.5);

}

void display(void)
{
  // Limpa a janela de visualização com a cor de fundo especificada, e limpa também o depth buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Entra no modo de definição de matriz de visualização
  glMatrixMode(GL_MODELVIEW);
  // Carrega a matriz identidade
  glLoadIdentity();
  // Define a posição da câmera, para onde ela aponta e qual o vetor UP
  gluLookAt(15.0f, 25.0f, 30.0f, 25.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  
  // Realiza a rotação da câmera
    glRotatef(cameraRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraRotationY, 0.0f, 1.0f, 0.0f);
  
  //===================================
  // BOB ESPONJA
  // Corpo
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
  	glScalef(10.0, 10.0, 4.0);  
  	glutSolidCube(1.0);
  glPopMatrix();
  
  glTranslatef(0.0, -5.75, 0.0);
  
  // Blusa
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
  	glScalef(10.25, 1.5, 4.25);
	glutSolidCube(1.0);
  glPopMatrix();

  glTranslatef(0.0, -2.0, 0.0);

  // Calça
  glPushMatrix();
    glColor3f(0.6, 0.3, 0.0);
  	glScalef(10.25, 2.5, 4.25);
	glutSolidCube(1.0);
  glPopMatrix();

  // Calça Esquerda
  glPushMatrix();
    glColor3f(0.6, 0.3, 0.0);
    glTranslatef(-2.0, -0.50, 2.0);
    glRotatef(ang_perna, 1.0, 0.0, 0.0);
  	glScalef(1.0, 3.0, 1.0);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Calça Direita
  glPushMatrix();
    glColor3f(0.6, 0.3, 0.0);
    glTranslatef(2.0, -0.50, 2.0);
    glRotatef(ang_perna, 1.0, 0.0, 0.0);
  	glScalef(1.0, 3.0, 1.0);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

   // Perna Esquerda
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-2.0, -0.50, 5.0);
    glRotatef(ang_perna, 1.0, 0.0, 0.0);
  	glScalef(0.65, 3.0, 0.65);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Perna Direita
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(2.0, -0.50, 5.0);
    glRotatef(ang_perna, 1.0, 0.0, 0.0);
  	glScalef(0.65, 3.0, 0.65);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Sapato Esquerdo
  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-2.0, 0.0, 8.25);
  	glScalef(1.5, 2.5, 1.5);
	glutSolidCube(1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.8, 0.6, 0.8);
    glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  // Sapato Direito
  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(2.0, 0.0, 8.25);
  	glScalef(1.5, 2.5, 1.5);
	glutSolidCube(1.0);
    glTranslatef(0.0, 0.5, 0.0);
    glScalef(0.8, 0.6, 0.8);
    glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glTranslatef(0.0, 5.75, 0.0);

  // Blusa Esquerda
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-6.0, -3.0, 0.0);
    glRotatef(-ang_braco, 0.0, 0.0, 1.0);
  	glScalef(1.0, 3.0, 1.0);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Blusa Direita
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(6.0, -3.0, 0.0);
    glRotatef(ang_braco, 0.0, 0.0, 1.0);
  	glScalef(1.0, 3.0, 1.0);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Braço Esquerdo
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-7.5, -5.2, 0.0);
    glRotatef(-ang_braco, 0.0, 0.0, 1.0);
  	glScalef(0.65, 3.0, 0.65);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Braço Direito
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(7.5, -5.2, 0.0);
    glRotatef(ang_braco, 0.0, 0.0, 1.0);
  	glScalef(0.65, 3.0, 0.65);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Mão Esquerda
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-7.5, -5.2, 0.0);
  	glScalef(0.9, 0.9, 0.9);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(-1.0, -1.0, 0.0);
  	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(1.5, -0.5, 0.0);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(-2.0, 1.6, 0.0);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(0.7, 2.0, 0.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  // Mão Direita
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(7.5, -5.2, 0.0);
    glScalef(0.9, 0.9, 0.9);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(1.0, -1.0, 0.0);
  	glScalef(0.6, 0.6, 0.6);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(-1.5, -0.5, 0.0);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(2.0, 1.6, 0.0);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(-0.7, 2.0, 0.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glTranslatef(0.0, 1.5, 0.0);

   // Olho Esquerdo
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-1.5, 1.0, 1.0);
    glScalef(2.0, 2.0, 2.0);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(0.0, 0.0, 0.7);
    glColor3f(0.17, 0.41, 0.92);
    glScalef(0.4, 0.4, 0.4);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(0.0, 0.0, 0.7);
    glColor3f(0.0, 0.0, 0.0);
    glScalef(0.4, 0.4, 0.4);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

   // Olho Direito
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(1.5, 1.0, 1.0);
    glScalef(2.0, 2.0, 2.0);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(0.0, 0.0, 0.7);
    glColor3f(0.17, 0.41, 0.92);
    glScalef(0.4, 0.4, 0.4);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(0.0, 0.0, 0.7);
    glColor3f(0.0, 0.0, 0.0);
    glScalef(0.4, 0.4, 0.4);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  // Marcas
  glPushMatrix();
    glColor3f(0.8, 1.0, 0.0);
    glTranslatef(-3.0, 4.0, -2.15);
    glRotatef(ang_perna, 1.0, 0.0, 0.0);
  	glScalef(0.8, 4.30, 0.8);
	drawSolidCylinder(1.0, 1.0, 20, 20);
    glTranslatef(8.0, 0.0, 9.0);
    glScalef(0.9, 1.0, 0.9);
	drawSolidCylinder(1.0, 1.0, 20, 20);
    glTranslatef(-10.0, 0.0, -7.50);
    glScalef(0.5, 1.0, 0.5);
	drawSolidCylinder(1.0, 1.0, 20, 20);
    glTranslatef(-0.5, 0.0, 15.50);
    glScalef(1.5, 1.0, 1.5);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Cílios
  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-1.5, 3.0, 2.0);
  	glScalef(0.3, 1.0, 0.5);
	glutSolidCube(1.0);
    glTranslatef(2.2, -0.3, 0.0);
    glRotatef(-ang_braco+10.0, 0.0, 0.0, 1.0);
	glutSolidCube(1.0);
    glTranslatef(-4.4, -2.0, 0.0);
    glRotatef(-ang_braco-10.0, 0.0, 0.0, 1.0);
	glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(1.5, 3.0, 2.0);
  	glScalef(0.3, 1.0, 0.5);
	glutSolidCube(1.0);
    glTranslatef(-2.2, -0.3, 0.0);
    glRotatef(ang_braco-10.0, 0.0, 0.0, 1.0);
	glutSolidCube(1.0);
    glTranslatef(4.4, -2.0, 0.0);
    glRotatef(ang_braco+10.0, 0.0, 0.0, 1.0);
	glutSolidCube(1.0);
  glPopMatrix();

  // Dentes
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.75, -2.7, 2.0);
  	glScalef(1.2, 1.5, 0.5);
	glutSolidCube(1.0);
    glTranslatef(-1.15, 0.0, 0.0);
	glutSolidCube(1.0);
  glPopMatrix();

   // Bochechas
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(3.0, -1.2, 1.7);
    glScalef(1.0, 1.0, 1.0);
	glutSolidSphere(1.0, 20, 6);
    glTranslatef(-6.0, 0.0, 0.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();
  
  // Sorriso
  glColor3f(0.0, 0.0, 0.0); // cor da linha
  glTranslatef(0.0, -1.0, 2.1);
  glScalef(3.0, 2.8, 1.0);
    GLfloat ctrlpoints[4][3] = {
        { -1.0,  0.0, 0.0 },
        { -0.5, -0.5, 0.0 },
        {  0.5, -0.5, 0.0 },
        {  1.0,  0.0, 0.0 }
    };

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 30; i++) {
        glEvalCoord1f((GLfloat)i / 30.0);
    }
    glEnd();

  // gravata
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.5, 0.0);
  	glScalef(0.35, 0.5, 0.3);
    glRotatef(ang_gravata, 0.0, 0.0, 1.0);
	glutSolidCube(1.0);
  glPopMatrix();  
  
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, -2.0, 0.0);
  	glScalef(0.35, 0.7, 0.3);
    glRotatef(ang_gravata, 0.0, 0.0, 1.0);
	glutSolidCube(1.0);
  glPopMatrix();  

   // Nariz
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(ang_perna, 1.0, 0.0, 0.0);
  	glScalef(0.2, 1.5, 0.2);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0, 0.0, 1.5);
    glScalef(0.2, 0.2, 0.7);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  //===================================

  // CASA ABACAXI

  //Chão
  glTranslatef(0.0, -12.7, -5.0);
  glColor3f(0.80, 0.90, 0.4);

  glPushMatrix();
  	glScalef(100.0, 20.0, 200.0);  
  	glutSolidCube(1.0);
  glPopMatrix();

  // Base
  glTranslatef(12.0, 15.0, -5.0);
  glColor3f(1.0, 0.5, 0.0);
 
  glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
  	glScalef(1.5, 3.0, 9.0);  
  	drawEllipsoid(30, 20, 5.0, 5.0, 2.5);
  glPopMatrix();

  glTranslatef(0.0, 5.0, 8.0);

  // Porta
  glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.0, -5.5, 12.0);
    glScalef(5.0, 9.0, 5.0);
    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.0, -1.5, 9.45);
    glRotatef(ang_perna, 1.0, 0.0, 0.0);
  	glScalef(2.51, 5.0, 2.51);
	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Janelas
  glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-3.0, 3.5, 2.5);
  	glScalef(2.0, 2.0, 6.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.17, 0.41, 0.92);
    glTranslatef(-3.8, 4.0, 4.7);
  	glScalef(1.0, 1.0, 4.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(4.0, -2.5, 5.0);
  	glScalef(2.0, 2.0, 6.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.17, 0.41, 0.92);
    glTranslatef(4.8, -2.5, 8.0);
  	glScalef(1.0, 1.0, 3.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  // Chaminé
  glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(6.0, 6.0, -2.0);
    glRotatef(ang_perna, 0.0, 0.0, 1.0);
    glScalef(0.5, 4.0, 1.5);
    drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(6.0, 7.5, -2.0);
    glScalef(1.0, 2.0, 1.5);
    glRotatef(ang_perna, 0.0, 0.0, -1.0);
    drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Maçaneta
  glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(1.3, -4.5, 15.0);
  	glScalef(0.4, 0.4, 1.2);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  // Coroa
  glTranslatef(0.0, 12.0, -8.0);

      // Definição dos vértices da pirâmide
    GLfloat vertices[][3] = {
        {-1.0, -1.0, -1.0},  // base: vértice 1
        {1.0, -1.0, -1.0},   // base: vértice 2
        {1.0, -1.0, 1.0},    // base: vértice 3
        {-1.0, -1.0, 1.0},   // base: vértice 4
        {0.0, 1.0, 0.0}      // topo: vértice 5
    };

    // Definição das faces da pirâmide
    GLint faces[][3] = {
        {0, 1, 4},  // face frontal
        {1, 2, 4},  // face direita
        {2, 3, 4},  // face traseira
        {3, 0, 4},  // face esquerda
        {3, 2, 1},  // base: triângulo 1
        {3, 1, 0}   // base: triângulo 2
    };

    glColor3f(0.0, 0.65, 0.0);
    glScalef(2.0, 5.0, 6.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        glVertex3fv(vertices[faces[i][0]]);
        glVertex3fv(vertices[faces[i][1]]);
        glVertex3fv(vertices[faces[i][2]]);
    }
    glEnd();

    glColor3f(0.0, 0.4, 0.0);
    glTranslatef(-1.5, 0.0, 0.0);
    glScalef(0.8, 0.8, 0.8);
    glRotatef(20.0, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        glVertex3fv(vertices[faces[i][0]]);
        glVertex3fv(vertices[faces[i][1]]);
        glVertex3fv(vertices[faces[i][2]]);
    }
    glEnd();

    glTranslatef(3.5, -1.3, 0.0);
    glRotatef(-40.0, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        glVertex3fv(vertices[faces[i][0]]);
        glVertex3fv(vertices[faces[i][1]]);
        glVertex3fv(vertices[faces[i][2]]);
    }
    glEnd();

    glTranslatef(-1.75, -1.0, -1.5);
    glRotatef(20.0, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        glVertex3fv(vertices[faces[i][0]]);
        glVertex3fv(vertices[faces[i][1]]);
        glVertex3fv(vertices[faces[i][2]]);
    }
    glEnd();

    glTranslatef(0.0, 0.0, 3.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        glVertex3fv(vertices[faces[i][0]]);
        glVertex3fv(vertices[faces[i][1]]);
        glVertex3fv(vertices[faces[i][2]]);
    }
    glEnd();

    glTranslatef(-1.5, 0.0, 0.0);
    glRotatef(20.0, 1.0, 0.0, 1.0);
    glColor3f(0.0, 0.8, 0.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        glVertex3fv(vertices[faces[i][0]]);
        glVertex3fv(vertices[faces[i][1]]);
        glVertex3fv(vertices[faces[i][2]]);
    }
    glEnd();

    glTranslatef(3.0, -1.0, -0.2);
    glRotatef(-40.0, 1.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        glVertex3fv(vertices[faces[i][0]]);
        glVertex3fv(vertices[faces[i][1]]);
        glVertex3fv(vertices[faces[i][2]]);
    }
    glEnd();

  //===================================

  // GARY
  glRotatef(40.0, 1.0, 0.0, 1.0);
  glTranslatef(-8.0, -1.9, 6.0);
  glRotatef(-20.0, 0.4, 1.0, 0.8);
  
  // Casco
  glPushMatrix();
    glColor3f(0.92, 0.51, 0.68);
  	glScalef(1.0, 1.0, 1.0);  
  	drawEllipsoid(30, 20, 1.4, 1.0, 1.0);
  glPopMatrix();

  glTranslatef(1.8  , 0.0, 0.4);
  glRotatef(-10.0, 1.0, 0.0, 0.0);

  // Olhos
  glPushMatrix();
    glColor3f(0.27, 0.41, 0.72);
  	glScalef(0.15, 1.1, 0.15);  
  	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0, 0.0, -0.7);
    glColor3f(0.27, 0.41, 0.72);
  	glScalef(0.15, 1.1, 0.15);  
  	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  // Cabeça
  glPushMatrix();
    glColor3f(0.27, 0.41, 0.72);
    glTranslatef(-0.15, 0.0, -0.4);
  	glScalef(1.2, 0.5, 1.0);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  // Olhos 2
  glPushMatrix();
    glColor3f(0.5, 0.7, 0.0);
    glTranslatef(0.0, 1.0, 0.0);
  	glScalef(0.3, 0.15, 0.3);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.2, 1.0, 0.0);
  	glScalef(0.2, 0.1, 0.2);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0.3, 1.0, 0.0);
  	glScalef(0.13, 0.05, 0.13);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.5, 0.7, 0.0);
    glTranslatef(0.0, 1.0, -0.7);
  	glScalef(0.3, 0.15, 0.3);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.2, 1.0, -0.7);
  	glScalef(0.2, 0.1, 0.2);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0.3, 1.0, -0.7);
  	glScalef(0.13, 0.05, 0.13);
	glutSolidSphere(1.0, 20, 6);
  glPopMatrix();

  // Marcas
  glPushMatrix();
    glTranslatef(-1.7, 0.7, -1.3);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(1.0, 0.2, 0.3);
  	glScalef(0.25, 1.8, 0.15);  
  	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2.2, 0.5, -1.3);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(1.0, 0.2, 0.3);
  	glScalef(0.2, 1.85, 0.1);  
  	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-2.2, 0.7, -1.2);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glColor3f(1.0, 0.2, 0.3);
  	glScalef(0.1, 1.6, 0.05);  
  	drawSolidCylinder(1.0, 1.0, 20, 20);
  glPopMatrix();

//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//===================================

  // Executa os comandos OpenGL, e depois troca os buffers de vídeo
  glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

void reshape (int w, int h)
{
  // Define o viewport como o tamanho da janela
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  // Entra no modo de definição de matriz de projeção
  glMatrixMode (GL_PROJECTION);
  // Carrega a matriz identidade
  glLoadIdentity();
  // Define a projeção ortogonal
  if (w <= h)
    // Se a largura for menor que a altura, a projeção é feita para manter a proporção da janela
    glOrtho (-50, 50, -50*(GLfloat)h/(GLfloat)w, 50*(GLfloat)h/(GLfloat)w, -100.0, 100.0);
  else
    // Se a altura for menor que a largura, a projeção é feita para manter a proporção da janela
    glOrtho (-50*(GLfloat)w/(GLfloat)h, 50*(GLfloat)w/(GLfloat)h, -50, 50, -100.0, 100.0);
   
}

int main(int argc, char** argv)
{
  // Inicializa a biblioteca GLUT e negocia uma seção com o gerenciador de janelas
  glutInit(&argc, argv);
  // Inicializa o display, indicando que usará:
  // - um buffer de imagem (single buffer);
  // - buffer de profundidade;
  // - padrão de cores RGB)
  glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
  // Especifica as dimensões da janela de exibição
  glutInitWindowSize (500, 500); 
  // Especifica a posição inicial da janela de exibição
  glutInitWindowPosition (100, 100);
  // Cria a janela de exibição
  glutCreateWindow("Bob Esponja e a Fenda do Biquini");
  // Chama a função init
  init ();
  // Estabelece a função "display" como a função callback de exibição.
  glutDisplayFunc(display); 
  // Estabelece a função "reshape" como a função callback de redimensionamento da janela de exibição.
  glutReshapeFunc(reshape);
  // Estabelece a função "keyboardSpecial" como a função callback de evento de teclado especial.
  glutSpecialFunc(myKeyboardSpecial);
  // Registra a função de callback para o movimento do mouse
  glutMotionFunc(handleMouseMovement);
  // Entra no loop de eventos, não retorna
  glutMainLoop();
  return 0;
}

// para compilar:
// g++ bob.c -o bob -lGL -lGLU -lglut -lm

// para executar:
// ./bob
