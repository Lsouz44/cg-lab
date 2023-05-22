#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

//Desenha um quadrado de lado 1 centrado na origem
void desenhaQuadrado() {
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
}

//Desenha um triângulo equilátero de lado 1 centrado na origem
void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, 0.5);
        glVertex2d(-0.5, -0.5);
        glVertex2d(0.5, -0.5);
    glEnd();
}

//Desenha um círculo de raio 1 centrado na origem
void desenhaCirculo() {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 30; i++) {
            glVertex2f(cos(i), sin(i));
        }
    glEnd();
}

//Faz o cisalhamento de um objeto em relação ao eixo X
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewX(GLfloat angle) {
    GLfloat m[16] = {
        1, 0, 0, 0,
        tan(angle), 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0 ,1
    };
    glMultMatrixf(m);
}

//Faz o cisalhamento de um objeto em relação ao eixo Y
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewY(GLfloat angle) {
    GLfloat m[16] = {
        1, tan(angle), 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0, 
        0, 0, 0, 1
    };
    glMultMatrixf(m);
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);

    // Aqui entra todo o seu código da casa 2D.
    //Vocês só pode usar as funções de desenho:
        // desenhaQuadrado, desenhaTriangulo, desenhaCirculo
    // as transformações geométricas:
        // glTranslatef, glRotatef, glScalef, skewX, skewY
    // e as funções de cor:
        // glColor3f
    // Não desenhe nenhuma primitiva utilizando glBegin/glEnd diretamente aqui.
    
    // PAREDES CASA
    
    // Parede Frontal
    // Define a cor de preenchimento da parede frontal
    glColor3f(0.9f, 0.8f, 0.2f);

    // Desenha a parede frontal da casa como um retângulo
    glPushMatrix();
    glTranslatef(60.0f, 65.0f, 0.0f);
    glScalef(80.0f, 90.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();
    
    // Parede Lateral
    // Define a cor de preenchimento da parede lateral
    glColor3f(0.9f, 0.9f, 0.3f);

    // Desenha a parede lateral como um retângulo
    glPushMatrix();
    glTranslatef(160.0f, 65.0f, 0.0f);
    glScalef(120.0f, 90.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();

	// TELHADO
	
	// Telhado Lateral
	// Define a cor de preenchimento do telhado lateral
    glColor3f(0.9f, 0.6f, 0.1f);

    // Desenha o corpo do telhado lateral como um retângulo
    glPushMatrix();
    glTranslatef(120.0f, 140.0f, 0.0f);
    glScalef(120.0f, 60.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();

	// Telhado traseiro
    // Define a cor de preenchimento do telhado traseiro
    glColor3f(0.9f, 0.6f, 0.1f);

    // Aplica uma translação para posicionar o telhado acima da parede da casa
    glPushMatrix();
    glTranslatef(180.0f, 140.0f, 0.0f);
    glScalef(80.0f, 60.0f, 1.0f);
    desenhaTriangulo();
    glPopMatrix();
	
	// Telhado Frontal
    // Define a cor de preenchimento do telhado frontal
    glColor3f(0.8f, 0.4f, 0.1f);

    // Aplica uma translação para posicionar o telhado acima da parede da casa
    glPushMatrix();
    glTranslatef(60.0f, 140.0f, 0.0f);
    glScalef(80.0f, 60.0f, 1.0f);
    desenhaTriangulo();
    glPopMatrix();

	// PORTA E JANELAS

	// Porta
    // Define a cor de preenchimento da porta
    glColor3f(0.5f, 0.2f, 0.0f);

    // Desenha a porta da casa como um retângulo
    glPushMatrix();
    glTranslatef(60.0f, 45.0f, 0.0f);
    glScalef(30.0f, 50.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();

	// Janelas
	// Define a cor de preenchimento das janelas
    glColor3f(0.3f, 0.3f, 0.8f);
    
    // Desenha as janelas da casa como retângulos
    glPushMatrix();
    glTranslatef(135.0f, 70.0f, 0.0f);
    glScalef(40.0f, 25.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(190.0f, 70.0f, 0.0f);
    glScalef(40.0f, 25.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();

	// CHAMINÉ
	
    // Define a cor de preenchimento da chaminé
    glColor3f(0.5f, 0.2f, 0.0f);
	
	// Chamine corpo
    // Desenha o corpo do chaminé da casa como um retângulo
    glPushMatrix();
    glTranslatef(125.0f, 177.5f, 0.0f);
    glScalef(20.0f, 15.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();
    
    // Chaminé topo
    // Desenha o topo chaminé da casa como um retângulo
    glPushMatrix();
    glTranslatef(125.0f, 187.5f, 0.0f);
    glScalef(30.0f, 7.5f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();
    
    // MAÇANETA E ÓCULO NO OITÃO
    
    // Óculo no oitão
    // Define a cor de preenchimento da janela frontal
    glColor3f(0.3f, 0.3f, 0.8f);

    // Aplica uma translação para posicionar a janela frontal no telhado frontal da casa
    glPushMatrix();
    glTranslatef(60.0f, 130.0f, 0.0f);
    glScalef(13.0f, 13.0f, 1.0f);
    desenhaCirculo();
    glPopMatrix();
    
    // Maçaneta
    // Define a cor de preenchimento da maçaneta
    glColor3f(0.8f, 0.3f, 0.1f);

    // Aplica uma translação para posicionar a maçaneta na porta da casa
    glPushMatrix();
    glTranslatef(50.0f, 42.0f, 0.0f);
    glScalef(3.0f, 3.0f, 1.0f);
    desenhaCirculo();
    glPopMatrix();
    
    // CHÃO
    // Define a cor de preenchimento do chão
    glColor3f(0.0f, 1.0f, 0.0f);

    // Desenha a chão como um retângulo
    glPushMatrix();
    glTranslatef(300.0f, 10.0f, 0.0f);
    glScalef(600.0f, 20.0f, 1.0f);
    desenhaQuadrado();
    glPopMatrix();
    
    // SOL
    // Define a cor de preenchimento do sol
    glColor3f(1.0f, 0.5f, 0.0f);

    // Aplica uma translação para posicionar o sol ao fundo da paisagem
    glPushMatrix();
    glTranslatef(250.0f, 215.0f, 0.0f);
    glScalef(22.0f, 22.0f, 1.0f);
    desenhaCirculo();
    glPopMatrix();
    
    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    // Define a cor de fundo da janela de visualização como azul
    glClearColor(0.5f, 0.95f, 1.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if(h == 0) h = 1;
                          
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    // Se a largura da janela, em pixels, for menor que a altura, a largura da viewport é fixada em 250 e a altura é escalada para o necessário
    if (w <= h)  {
    	windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
    }
    else  { 
    // Se a altura da janela, em pixels, for menor que a largura, a altura da viewport é fixada em 250 e a largura é escalada para o necessário
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
    }
     
    // As dimensões da janela vão de (0.0, 0.0) até (windowWidth, windowHeight), essas são as coordenadas da tela
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Programa Principal 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Casa 2D - Versao 2.0");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutMainLoop();
    return 0;
}

// para compilar:
// g++ casa2d_v2.c -o casa2d_v2 -lGL -lGLU -lglut -lm

// para executar:
// ./casa2d_v2
