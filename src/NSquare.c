#include "NSquare.h"

#include "NShader.h"
#include "NGlobals.h"
#include "NSplu.h"
#include <GLKit/GLKMath.h>

GLuint square_id;

GLuint vao;
GLuint vbo;
GLuint ibo;

#define VERTICES 4
#define INDICES 6

typedef struct {
    GLfloat position[3];
    GLfloat texcoord[2];
} vertex;

void NSquare_init() {
    vertex vertexdata[VERTICES] = {
        { { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
        { { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
        { { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }
    };
    GLubyte indexdata[INDICES] = {0, 1, 2, 1, 3, 2};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, VERTICES * sizeof(vertex), vertexdata, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texcoord));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES * sizeof(GLubyte), indexdata, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    square_id = vao;
}

void NSquare_destroy() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);
}


void NSquare_draw_shape() {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, INDICES, GL_UNSIGNED_BYTE, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

void NSquare_draw(NPos2i pos, NPos2i size) {
    N_gl_model = Nsplu_calc_rect(GLKpos2i(pos), GLKpos2i(size));
    NShader_update_MVP(N_shader);
    NSquare_draw_shape();
    N_gl_model = GLKMatrix4Identity;
}
