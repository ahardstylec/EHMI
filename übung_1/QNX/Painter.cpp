/*
 * Painter.cpp
 *
 *  Created on: 30.10.2014
 *      Author: istancoll
 */

#include "Painter.h"
#include <gf/gf.h>
#include <sys/mman.h>
#include <string.h>

Painter::Painter() {
	// TODO Auto-generated constructor stub

}

void Painter::init() {

	gf_dev_attach(&gf_device, GF_DEVICE_INDEX(0), &gf_device_info);

	gf_display_attach(&gf_display, gf_device, 0, &gf_display_info);

	// layer 0 erstellen
	gf_layer_attach(&gf_layer, gf_display, 0, 0);

	// mit layer 0 verknüpftes surface erstellen

	gf_surface_create_layer(&gf_surface, &gf_layer, gf_display_info.nlayers, 0,
			gf_display_info.xres, gf_display_info.yres, gf_display_info.format,
			0, 0);

	// setze aktuelles surface
	gf_layer_set_surfaces(gf_layer, &gf_surface, 1);
	// context erstellen
	gf_context_create(&gf_context);

	// context mit surface verknüpfen
	gf_context_set_surface(gf_context, gf_surface);

	gf_surface_get_info(gf_surface, &gf_surface_info);

	// größe des Surface speicherbereichs berechnen
	mem_length = gf_surface_info.w * gf_surface_info.h *
				((gf_surface_info.format & GF_FORMAT_BPP) / 8);

	// Physischen Addressbereich des Surface in Application abbilden
	mem_surface = (unsigned short *) mmap(0, mem_length, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_PHYS, NOFD, gf_surface_info.paddr);

}

void Painter::draw(){
	// lock the graphic adapter
	gf_draw_begin(gf_context);

	// todo draw things
	memset(mem_surface, 0x00, mem_length);

	const int x1 = gf_surface_info.w,
			  x2 = x1 / 2,
			  y1 = gf_surface_info.h,
			  y2 = y1 / 2,
			  y4 = y1 / 4,
			  x2y2 = x1 * y2 + x2,
			  x2y4 = x1 * y4 + x2;

	float xy = x1 / (float) y1;

	int y_pos = 0;
	for(int offset = x2y4; offset < x2y2; offset += x1, y_pos++ ){

		const int current_line_length = y_pos * xy;

		for (int xpos = 0; xpos < current_line_length; xpos ++){
			unsigned short * pixel = mem_surface + offset + xpos;
			*pixel = 0b000001111100000;
		}
	}


	gf_draw_flush(gf_context);
	// unlock graphics adapter
	gf_draw_end(gf_context);

	sleep(3);
}

Painter::~Painter() {
	// TODO Auto-generated destructor stub
	// resources freigeben
	gf_context_free( gf_context);

	gf_surface_free( gf_surface);

	gf_layer_detach( gf_layer);

	gf_display_detach( gf_display);

	gf_dev_detach( gf_device);
}
