#pragma once

#include "background.h"
typedef char bool;
enum {false = 'f', true = 't'};

struct button_data {
    struct {
        float red;
        float green;
        float blue;
    } color;

    struct {
        float x;
        float y;
    } position;

    struct {
        float x;
        float y;
    } size;

    bool checked;
};

void shmi_button_init(struct button_data *);
void shmi_button_draw(struct button_data *);
void shmi_button_hover(struct button_data * data, double xpos, double ypos);
void shmi_button_click(struct button_data * data, double xpos, double ypos, struct background_color * bg);

