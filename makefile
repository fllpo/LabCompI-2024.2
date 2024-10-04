OBJS = main.c
CC= gcc
OBJ_NAME = main

all : src/$(OBJS)
	clear
	$(CC) src/$(OBJS) -lSDL2 -lSDL2_ttf -lSDL2_image -o src/bin/$(OBJ_NAME) -Wall
	./src/bin/$(OBJ_NAME)
	rm ./src/bin/$(OBJ_NAME)

