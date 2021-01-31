objects = sleep.o segment.o snake.o main.o

snake : $(objects)
	gcc -o build/snake $(objects) -lncurses
main.o : src/main.c src/segment.h src/sleep.h
	gcc -c src/main.c
segment.o : src/segment.c src/segment.h
	gcc -c src/segment.c
snake.o : src/snake.c src/segment.h
	gcc -c src/snake.c
sleep.o : src/sleep.c src/sleep.h
	gcc -c src/sleep.c
clean :
	\rm snake $(objects)
