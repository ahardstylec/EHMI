#include <GL/gl.h>
#include "button.h"
#include "background.h"
#include <stdio.h>

void shmi_button_init(struct button_data * data)
{
    data->color.red = 0.0f;
    data->color.green = 1.0f;
    data->color.blue = 0.0f;

    data->position.x = -0.5f;
    data->position.y = -0.5f;

    data->size.x = 1.f;
    data->size.y = 1.f;

    data->checked = false;
}

void shmi_button_draw(struct button_data * data)
{
    glLoadIdentity();
    glBegin(GL_QUADS);
    glColor3f(data->color.red, data->color.green, data->color.blue);
    glVertex3f(
            data->position.x,
            data->position.y,
            0.f);
    glVertex3f(data->position.x + data->size.x,
            data->position.y,
            0.f);
    glVertex3f(
            data->position.x + data->size.x,
            data->position.y + data->size.y,
            0.f);
    glVertex3f(
            data->position.x,
            data->position.y + data->size.y,
            0.f);
    glEnd();
}

void shmi_button_hover(struct button_data * data, double xpos, double ypos)
{
    printf("cursor position: %f, %f\r", xpos, ypos);
    fflush(stdout);
    if (xpos >= data->position.x &&
            xpos <= data->position.x + data->size.x &&
            ypos >= data->position.y &&
            ypos <= data->position.y + data->size.y) {
        data->color.red = 1.0f;
        data->color.green = 0.0f;
    } else {
        data->color.red = 0.0f;
        data->color.green = 1.0f;
    }
}

void shmi_button_click(struct button_data * data, double xpos, double ypos, struct background_color * bg)
{
    if(xpos >= data->position.x &&
            xpos <= data->position.x + data->size.x &&
            ypos >= data->position.y &&
            ypos <= data->position.y + data->size.y) {

        if (data->checked == true) {
            bg->blue = 0.f;
            data->checked = false;
        } else {
            bg->blue = 1.f;
            data->checked = true;
        }
    }
}
