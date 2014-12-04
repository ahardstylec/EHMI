#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "button.h"
#include "background.h"

static struct button_data button;
static struct background_color bg;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursor_pos_callback(GLFWwindow * window, double xpos, double ypos)
{
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    double x = (xpos - width/2) / height * 2;
    double y = (height/2 - ypos) / (height/2);
    shmi_button_hover(&button, x, y);
}

static void button_callback(GLFWwindow * window, int clicked_button, int action, int mods)
{
    if (GLFW_RELEASE == action) return;

    // get cursor position
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // get window size
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);

    // calculate openGL coordinates
    double x = (xpos - width/2) / height * 2;
    double y = (height/2 - ypos) / (height/2);

    // call on clicked function
    shmi_button_click(&button, x, y, &bg);
}

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);       
    glfwSetMouseButtonCallback(window, button_callback);

    shmi_button_init(& button);

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.red, bg.green, bg.blue, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        shmi_button_draw(&button);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

