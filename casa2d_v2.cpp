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
