/*
 * Painter.h
 *
 *  Created on: 30.10.2014
 *      Author: istancoll
 */

#ifndef PAINTER_H_
#define PAINTER_H_

#include <gf/gf.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sys/mman.h>

class Painter {
public:
	Painter();
	void init();
	void draw();
	virtual ~Painter();
private:
	gf_dev_t gf_device;
	gf_dev_info_t gf_device_info;
	gf_display_t gf_display;
	gf_display_info_t gf_display_info;
	gf_layer_t gf_layer;
	gf_surface_t gf_surface;
	gf_context_t gf_context;
	gf_surface_info_t gf_surface_info;
	unsigned short * mem_surface;
	size_t mem_length;
};

#endif /* PAINTER_H_ */
