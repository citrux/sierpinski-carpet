// main.c

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

GLuint program;
void render();
char* readFile();

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Sierpinski carpet");
    glutDisplayFunc(render);
    glewInit();

    // компиляция и линковка шейдера
    program = glCreateProgram();
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* buffer = readFile("shader.glsl");
    glShaderSource(shader, 1, &buffer, 0);
    glCompileShader(shader);
    glAttachShader(program, shader);
    glLinkProgram(program);

    glutMainLoop();
}

void render() {
    glUseProgram(program);

    // рисуем квадрат на всё окно
    // именно его текстуру будет рисовать шейдер
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 0);
    glVertex2f(1, -1);
    glTexCoord2f(1, 1);
    glVertex2f(1, 1);
    glTexCoord2f(0, 1);
    glVertex2f(-1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(-1, -1);
    glEnd();

    glUseProgram(0);

    glutSwapBuffers();
}


char * readFile(const char* fname) {
    FILE* fp;
    long lSize;
    char* buffer;
    
    fp = fopen (fname, "r");
    if(!fp) {
        perror(fname);
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    /* выделяем память для текста + 1 для нулевого байта в конце */
    buffer = calloc(sizeof(char), lSize+1);
    if(!buffer) {
        fclose(fp);
        fputs("memory alloc fails", stderr);
        exit(1);
    }

    /* копируем содержимое файла в буфер */
    if(1!=fread(buffer, lSize, 1, fp)) {
      fclose(fp);
      free(buffer);
      fputs("entire read fails", stderr);
      exit(1);
    }

    fclose(fp);
    return buffer;
}