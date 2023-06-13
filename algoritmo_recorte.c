#include <stdio.h>
#include <GLFW/glfw3.h>

#define INSIDE 0 // Código para pontos dentro do retângulo de recorte
#define LEFT 1   // Código para pontos à esquerda do retângulo de recorte
#define RIGHT 2  // Código para pontos à direita do retângulo de recorte
#define BOTTOM 4 // Código para pontos abaixo do retângulo de recorte
#define TOP 8    // Código para pontos acima do retângulo de recorte

// Dimensões da janela
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Coordenadas do retângulo de recorte
const int X_MIN = 50;
const int Y_MIN = 50;
const int X_MAX = 300;
const int Y_MAX = 300;

// Função para calcular o código de região de um ponto
int calculateCode(int x, int y) {
    int code = INSIDE;

    if (x < X_MIN)      // Verificar se o ponto está à esquerda do retângulo
        code |= LEFT;
    else if (x > X_MAX) // Verificar se o ponto está à direita do retângulo
        code |= RIGHT;

    if (y < Y_MIN)      // Verificar se o ponto está abaixo do retângulo
        code |= BOTTOM;
    else if (y > Y_MAX) // Verificar se o ponto está acima do retângulo
        code |= TOP;

    return code;
}

// Função para realizar o recorte de uma linha utilizando o algoritmo de Cohen-Sutherland
void cohenSutherland(int x1, int y1, int x2, int y2) {
    int code1 = calculateCode(x1, y1);
    int code2 = calculateCode(x2, y2);
    int accept = 0;
    int done = 0;

    while (!done) {
        if ((code1 == 0) && (code2 == 0)) { // Linha completamente dentro do retângulo
            accept = 1;
            done = 1;
        } else if (code1 & code2) {         // Linha completamente fora do retângulo
            done = 1;
        } else {
            int x, y;
            int code = code1 ? code1 : code2;

            if (code & TOP) {                // Ponto acima do retângulo
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (code & BOTTOM) {      // Ponto abaixo do retângulo
                x = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                y = Y_MIN;
            } else if (code & RIGHT) {       // Ponto à direita do retângulo
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else if (code & LEFT) {        // Ponto à esquerda do retângulo
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (code == code1) {
                x1 = x;
                y1 = y;
                code1 = calculateCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = calculateCode(x2, y2);
            }
        }
    }

    if (accept) {
        glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);  // Linha verde para a linha recortada
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    } else {
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);  // Linha vermelha para a linha completamente fora do retângulo
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
}

void drawRectangle() {
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 1.0f);  // Retângulo azul
    glVertex2i(X_MIN, Y_MIN);
    glVertex2i(X_MAX, Y_MIN);
    glVertex2i(X_MAX, Y_MAX);
    glVertex2i(X_MIN, Y_MAX);
    glEnd();
}

void renderScene(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle();
    cohenSutherland(20, 60, 200, 400); // Exemplo de linha a ser recortada
    cohenSutherland(0, 0, 49, 49);
    glfwSwapBuffers(window);
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        printf("Falha ao inicializar GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Recorte de Cohen-Sutherland", NULL, NULL);
    if (!window) {
        printf("Falha ao criar janela GLFW\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        renderScene(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


// para compilar:
// g++ algoritmo_recorte.c -o algoritmo_recorte -lGL -lGLU -lglut -lm -lGLEW -lglfw3 -lX11

// para executar:
// ./algoritmo_recorte
