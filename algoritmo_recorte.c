#include <stdio.h>
#include <GL/glut.h>

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

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

// Função para desenhar uma linha
void desenharLinha(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

// Função para realizar o recorte de Cohen-Sutherland
void cortarLinha(float x1, float y1, float x2, float y2)
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
    desenharLinha(x1, y1, x2, y2, 0.0f, 1.0f, 0.0f);
}

// Função para exibir os resultados na tela
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Limpa a janela de visualização com a cor de fundo especificada
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenhar a área de recorte retangular em preto
    desenharLinha(xmin, ymin, xmin, ymax, 0.0f, 0.0f, 0.0f);
    desenharLinha(xmin, ymax, xmax, ymax, 0.0f, 0.0f, 0.0f);
    desenharLinha(xmax, ymax, xmax, ymin, 0.0f, 0.0f, 0.0f);
    desenharLinha(xmax, ymin, xmin, ymin, 0.0f, 0.0f, 0.0f);

    // Desenhar as linhas de teste
    desenharLinha(36, 86, 14, 165, 1.0f, 0.0f, 0.0f);
    desenharLinha(157, 104, 87, 79, 1.0f, 0.0f, 0.0f);
    desenharLinha(153, 244, 114, 160, 1.0f, 0.0f, 0.0f);
    desenharLinha(213, 167, 145, 20, 1.0f, 0.0f, 0.0f);
    desenharLinha(227, 65, 36, 65, 1.0f, 0.0f, 0.0f);
    desenharLinha(63, 240, 63, 34, 1.0f, 0.0f, 0.0f);
    desenharLinha(242, 57, 185, 12, 1.0f, 0.0f, 0.0f);
    desenharLinha(142, 176, 195, 107, 1.0f, 0.0f, 0.0f);
    desenharLinha(97, 50, 50, 95, 1.0f, 0.0f, 0.0f);
    desenharLinha(125, 0, 125, 50, 1.0f, 0.0f, 0.0f);

    // Realizar o recorte de Cohen-Sutherland para cada linha de teste
    cortarLinha(36, 86, 14, 165);
    cortarLinha(157, 104, 87, 79);
    cortarLinha(153, 244, 114, 160);
    cortarLinha(213, 167, 145, 20);
    cortarLinha(227, 65, 36, 65);
    cortarLinha(63, 240, 63, 34);
    cortarLinha(242, 57, 185, 12);
    cortarLinha(142, 176, 195, 107);
    cortarLinha(97, 50, 50, 95);
    cortarLinha(125, 0, 125, 50);

    glFlush();

    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa()
{
    // Define a cor de fundo da janela de visualização como branco
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Algoritmo de recorte de Cohen-Sutherland");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutMainLoop();
    return 0;
}


// para compilar:
// g++ algoritmo_recorte.c -o algoritmo_recorte -lGL -lGLU -lglut -lm

// para executar:
// ./algoritmo_recorte
