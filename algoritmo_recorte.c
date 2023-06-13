#include <stdio.h>
#include <GL/glut.h>

// Definindo os códigos de recorte
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Definindo a área de recorte retangular
const float xmin = 50;
const float ymin = 50;
const float xmax = 200;
const float ymax = 200;

// Função para desenhar uma linha usando OpenGL
void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// Função para realizar o recorte de Cohen-Sutherland
void clipLine(float x1, float y1, float x2, float y2)
{
    float x, y;
    int code1, code2, codeOut;

    // Determinar o código de recorte para o primeiro ponto
    code1 = (x1 < xmin) ? LEFT : ((x1 > xmax) ? RIGHT : INSIDE);
    code1 |= (y1 < ymin) ? BOTTOM : ((y1 > ymax) ? TOP : INSIDE);

    // Determinar o código de recorte para o segundo ponto
    code2 = (x2 < xmin) ? LEFT : ((x2 > xmax) ? RIGHT : INSIDE);
    code2 |= (y2 < ymin) ? BOTTOM : ((y2 > ymax) ? TOP : INSIDE);

    // Realizar o recorte
    while (code1 != INSIDE || code2 != INSIDE)
    {
        // Verificar se a linha está completamente fora da área de recorte
        if ((code1 & code2) != INSIDE)
        {
            return;
        }

        // Escolher um ponto fora da área de recorte
        codeOut = code1 != INSIDE ? code1 : code2;

        // Calcular a interseção com as arestas da área de recorte
        if (codeOut & TOP)
        {
            x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
            y = ymax;
        }
        else if (codeOut & BOTTOM)
        {
            x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
            y = ymin;
        }
        else if (codeOut & RIGHT)
        {
            y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
            x = xmax;
        }
        else if (codeOut & LEFT)
        {
            y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
            x = xmin;
        }

        // Atualizar o ponto fora da área de recorte
        if (codeOut == code1)
        {
            x1 = x;
            y1 = y;
            code1 = (x1 < xmin) ? LEFT : ((x1 > xmax) ? RIGHT : INSIDE);
            code1 |= (y1 < ymin) ? BOTTOM : ((y1 > ymax) ? TOP : INSIDE);
        }
        else
        {
            x2 = x;
            y2 = y;
            code2 = (x2 < xmin) ? LEFT : ((x2 > xmax) ? RIGHT : INSIDE);
            code2 |= (y2 < ymin) ? BOTTOM : ((y2 > ymax) ? TOP : INSIDE);
        }
    }

    // Desenhar a linha recortada
    drawLine(x1, y1, x2, y2, 0.0f, 1.0f, 0.0f);
}

// Função para exibir os resultados na tela usando OpenGL
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenhar a área de recorte retangular em preto
    drawLine(xmin, ymin, xmin, ymax, 0.0f, 0.0f, 0.0f);
    drawLine(xmin, ymax, xmax, ymax, 0.0f, 0.0f, 0.0f);
    drawLine(xmax, ymax, xmax, ymin, 0.0f, 0.0f, 0.0f);
    drawLine(xmax, ymin, xmin, ymin, 0.0f, 0.0f, 0.0f);

    // Desenhar as linhas de teste
    drawLine(100, 80, 150, 120, 1.0f, 0.0f, 0.0f);
    drawLine(80, 160, 220, 190, 1.0f, 0.0f, 0.0f);
    drawLine(50, 130, 250, 130, 1.0f, 0.0f, 0.0f);
    drawLine(170, 220, 170, 50, 1.0f, 0.0f, 0.0f);
    drawLine(120, 70, 220, 230, 1.0f, 0.0f, 0.0f);
    drawLine(180, 240, 240, 40, 1.0f, 0.0f, 0.0f);
    drawLine(60, 190, 200, 50, 1.0f, 0.0f, 0.0f);
    drawLine(160, 30, 210, 250, 1.0f, 0.0f, 0.0f);
    drawLine(90, 210, 250, 80, 1.0f, 0.0f, 0.0f);
    drawLine(30, 30, 30, 180, 1.0f, 0.0f, 0.0f);

    // Realizar o recorte de Cohen-Sutherland para cada linha de teste
    clipLine(100, 80, 150, 120);
    clipLine(80, 160, 220, 190);
    clipLine(50, 130, 250, 130);
    clipLine(170, 220, 170, 50);
    clipLine(120, 70, 220, 230);
    clipLine(180, 240, 240, 40);
    clipLine(60, 190, 200, 50);
    clipLine(160, 30, 210, 250);
    clipLine(90, 210, 250, 80);
    clipLine(30, 30, 30, 180);

    glFlush();
}

// Função de inicialização do OpenGL
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Recorte de Cohen-Sutherland");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


// para compilar:
// g++ algoritmo_recorte.c -o algoritmo_recorte -lGL -lGLU -lglut -lm

// para executar:
// ./algoritmo_recorte
