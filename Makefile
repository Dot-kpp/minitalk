NAME = minitalk.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra -o minitalk

SRCS = 	src/minitalk.c

OBJ = $(SRCS:%c=%o)

LIBFT = ./libft/libft.a

$(NAME): $(OBJ)
	@echo "Your shit is compiling"
	@echo ""
	@ar rcs $(NAME) $(OBJ)
	@echo ""
	@$(CC) $(CFLAGS) $(NAME) $(LIBFT)
	@mkdir -p objs && mv ./src/*.o ./objs/
	@mkdir -p bin && mv minitalk.a ./bin
	@echo "Your shit is compiled"
	@echo ""


clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) *.out *.exe ./objs ./bin ./libft/*.o 
	@echo ""
	@echo "Your shit is clean af!"
	@echo ""
	@echo "(👍 ͡❛ ͜ʖ ͡❛)👍"
	@echo ""

re:	fclean all