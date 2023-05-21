import OpenGL.GL as gl
import OpenGL.GLUT as glut

def draw_house():
    gl.glBegin(gl.GL_TRIANGLES)
    # Triângulo do telhado
    gl.glVertex2f(0.0, 0.5)  # Vértice superior
    gl.glVertex2f(-0.5, 0.0)  # Vértice inferior esquerdo
    gl.glVertex2f(0.5, 0.0)  # Vértice inferior direito
    gl.glEnd()

    gl.glBegin(gl.GL_QUADS)
    # Parede da casa
    gl.glVertex2f(-0.5, 0.0)  # Vértice inferior esquerdo
    gl.glVertex2f(-0.5, -0.5)  # Vértice inferior direito
    gl.glVertex2f(0.5, -0.5)  # Vértice superior direito
    gl.glVertex2f(0.5, 0.0)  # Vértice superior esquerdo

    # Porta
    gl.glVertex2f(-0.2, -0.5)  # Vértice inferior esquerdo
    gl.glVertex2f(-0.2, -0.4)  # Vértice inferior direito
    gl.glVertex2f(0.2, -0.4)  # Vértice superior direito
    gl.glVertex2f(0.2, -0.5)  # Vértice superior esquerdo
    gl.glEnd()

def draw_scene():
    gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
    gl.glLoadIdentity()

    # Movendo a cena para a posição desejada
    gl.glTranslatef(0.0, 0.0, -5.0)

    # Desenho da casa
    gl.glPushMatrix()
    gl.glColor3f(0.8, 0.2, 0.2)  # Cor vermelha para a casa
    draw_house()
    gl.glPopMatrix()

    # Desenho do sol
    gl.glPushMatrix()
    gl.glRotatef(45.0, 0.0, 0.0, 1.0)  # Rotação do sol
    gl.glScalef(0.5, 0.5, 1.0)  # Escala do sol
    gl.glTranslatef(1.0, 1.0, 0.0)  # Translação do sol
    gl.glColor3f(1.0, 1.0, 0.0)  # Cor amarela para o sol
    glut.glutSolidSphere(0.2, 20, 20)  # Desenho do sol como uma esfera
    gl.glPopMatrix()

    gl.glFlush()

def main():
    glut.glutInit()
    glut.glutInitDisplayMode(glut.GLUT_SINGLE | glut.GLUT_RGB | glut.GLUT_DEPTH)
    glut.glutInitWindowSize(500, 500)
    glut
