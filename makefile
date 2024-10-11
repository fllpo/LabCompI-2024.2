OBJS = main.c
CC = gcc
OBJ_NAME = main
LD_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image

all : src/$(OBJS)
	clear
	$(CC) src/$(OBJS) $(LD_FLAGS) -o bin/$(OBJ_NAME) -Wall
	./bin/$(OBJ_NAME)
	rm ./bin/$(OBJ_NAME)
	
