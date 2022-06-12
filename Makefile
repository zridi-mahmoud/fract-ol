$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
all:	
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit main.c -o test_load.out
	./test_load.out

clean: 
	rm -rf *.out
