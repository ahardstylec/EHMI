CXX=clang++
# CXXFLAGS=-std=c++11 -mtune=native -march=native -O2 -g -Weverything -ferror-limit=1 -I /usr/include/opencv2/
CXXFLAGS=-std=c++11 -mtune=native -march=native -O2 -g -Weverything -ferror-limit=1 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -fopenmp -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/include/ImageMagick-6
# LDFLAGS=-lm -lopencv_core -lopencv_imgproc -lopencv_highgui
LDFLAGS=-lm -lMagick++-6.Q16HDRI -lMagickWand-6.Q16HDRI -lMagickCore-6.Q16HDRI
SRC=painter.cpp
INC=$(SRC,.cpp=.h)

all: $(SRC) $(INC)
	$(CXX) $(CXXFLAGS) $(SRC) main.cpp -o prog $(LDFLAGS)

run: all
	./prog

clean:
	rm -f prog
