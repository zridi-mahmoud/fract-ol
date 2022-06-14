test: $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
all:	
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit main.c -o test_load.out fractal/julia.c complex/operations.c -I '.'
	./test_load.out

clean: 
	rm -rf *.out
