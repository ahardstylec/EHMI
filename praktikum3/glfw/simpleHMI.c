#include "simpleHMI.h"
#include <stdio.h>

// "private" declarations
void shmi_init(void);
void shmi_cleanup(void);
void shmi_create_window(void);
void shmi_load_gl_functions(void);

// "private" definitions
void shmi_init() { glfwInit(); }

void shmi_cleanup(void) { glfwTerminate(); }

void shmi_create_window() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  shmi_window = glfwCreateWindow(800, 600, "OpenGL", 0, 0); // Windowed

  glfwMakeContextCurrent(shmi_window);
}

void shmi_load_gl_functions() {
  glewExperimental = GL_TRUE;
  glewInit();
}

// "public" definitions
void shmi_run() {
  shmi_init();

  shmi_create_window();

  shmi_load_gl_functions();

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  printf("%u\n", vertexBuffer);

  while (!glfwWindowShouldClose(shmi_window)) {
    glfwSwapBuffers(shmi_window);
    glfwPollEvents();
    if (glfwGetKey(shmi_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(shmi_window, GL_TRUE);
  }

  shmi_cleanup();
}
