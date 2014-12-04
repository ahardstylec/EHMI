CC = clang
P = shmi
CFLAGS = -std=c11 -mtune=native -flto -O3 -Weverything
OBJ = button.o shmi.o
LDFLAGS = -flto -O3 -s -lglfw -lGL

$(P): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(P) $(LDFLAGS)

clean:
	rm -f $(P) $(OBJ)
