SERVER = server

CLIENT = client

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = 	src/client.c src/server.c src/error.c

OBJ = $(SRCS:%c=%o)

LIBFT = /libft/libft.a

all : $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT) :
	@echo "Your libft is compiling"
	@echo ""
	@$(MAKE) -C libft
	@echo ""

$(SERVER) : src/server.o src/error.o include/minitalk.h
	@echo "Compiling server"
	@echo ""
	@$(CC) src/server.o src/error.o libft/libft.a -o server
	@echo ""

$(CLIENT) : src/client.o src/error.o include/minitalk.h
	@echo "Compiling client"
	@$(CC) src/client.o src/error.o libft/libft.a -o client
	@echo "Your shit is compiled"
	@echo ""


clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf *.out *.exe server client ./objs ./bin ./libft/src/*.o 
	@echo ""
	@echo "Your shit is clean af!"
	@echo ""
	@echo "(👍 ͡❛ ͜ʖ ͡❛)👍"
	@echo ""

re:	fclean all