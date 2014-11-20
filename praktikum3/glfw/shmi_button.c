#include "simpleHMI.h"
#include "shmi_button.h"

// private
static float shmi_button_vertices[4][2];
void shmi_button_upload(void);

static float shmi_button_vertices[4][2] = {
    {-0.5f, 0.5f}, // vertex1
    {0.5f, 0.5f},  // vertex2
    {0.5f, -0.5f}, // vertex3
    {-0.5f, -0.5f} // vertex4
};

void shmi_button_init() {
   shmi_button_upload();
}

void shmi_button_upload() {
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(shmi_button_vertices), shmi_button_vertices, GL_STATIC_DRAW);
}
