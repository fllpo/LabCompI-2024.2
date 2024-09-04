OBJS = main.c

OBJ_NAME = main

all : $(OBJS)
	clear
	gcc $(OBJS) -lSDL2 -lSDL2_ttf -o $(OBJ_NAME)
	./main
