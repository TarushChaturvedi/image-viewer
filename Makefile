
all: build run

build: clean
	gcc -s src/main.c -lSDL2 -lSDL2_image -o bin/image-viewer

clean:
	rm -rf bin/
	mkdir bin

run:
	./bin/image-viewer sample.png