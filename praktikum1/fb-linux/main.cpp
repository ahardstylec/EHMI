#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stropts.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <Magick++.h>

#include <exception>

#include "painter.h"

int main(int argc, char **argv) {
	InitializeMagick(*argv);
    try {
        Painter painter;
        painter.draw();

        return 0;
    } catch (std::exception & e) {
        printf("Error: %s", e.what());
        return 1;
    }
}

