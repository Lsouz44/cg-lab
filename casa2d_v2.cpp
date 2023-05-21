/*
#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenhar a base da casa
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glRectf(-0.5, -0.5, 0.5, 0.5);
    glPopMatrix();
    
    // Desenhar o telhado
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(45.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 0.5, 1.0);
    glRectf(-0.5, 0.5, 0.5, 1.5);
    glPopMatrix();
    
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Casa 2D");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
*/

#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenhar a base da casa
    glColor3f(0.8, 0.8, 0.8); // Cor cinza claro
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(1.5, 1.0, 1.0); // Ampliar a base horizontalmente
    glRectf(-0.6, -0.4, 0.6, 0.6);
    glPopMatrix();
    
    // Desenhar o telhado
    glColor3f(0.8, 0.4, 0.2); // Cor marrom claro
    glPushMatrix();
    glTranslatef(0.0, 0.35, 0.0); // Mover o telhado para cima
    glScalef(1.5, 0.6, 1.0); // Ampliar o telhado horizontalmente
    glRotatef(45.0, 0.0, 0.0, 1.0); // Girar o telhado em 45 graus
    glRectf(-0.6, -0.3, 0.6, 0.3);
    glPopMatrix();
    
    // Desenhar a porta
    glColor3f(0.4, 0.2, 0.0); // Cor marrom escuro
    glPushMatrix();
    glTranslatef(0.0, -0.3, 0.0); // Mover a porta para baixo
    glScalef(0.4, 0.6, 1.0); // Reduzir a altura da porta
    glRectf(-0.15, -0.3, 0.15, 0.3);
    glPopMatrix();
    
    // Desenhar a janela
    glColor3f(0.4, 0.6, 0.8); // Cor azul claro
    glPushMatrix();
    glTranslatef(-0.35, 0.0, 0.0); // Mover a janela para a esquerda
    glScalef(0.3, 0.3, 1.0); // Reduzir o tamanho da janela
    glRectf(-0.5, -0.5, 0.5, 0.5);
    glPopMatrix();
    
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Casa 2D");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
