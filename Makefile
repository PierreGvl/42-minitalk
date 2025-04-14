NAME_CLIENT = client
NAME_SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror

DIR_SRC = src/
DIR_LIB = lib/
DIR_INC = inc/

SRC_CLIENT =	$(DIR_SRC)client.c
SRC_SERVER =	$(DIR_SRC)server.c

SRC_LIB =	$(DIR_LIB)ft_putchar_fd.c \
        	$(DIR_LIB)ft_putstr_fd.c \
        	$(DIR_LIB)ft_putnbr_fd.c \
        	$(DIR_LIB)ft_putendl_fd.c \
        	$(DIR_LIB)ft_isdigit.c \
        	$(DIR_LIB)ft_atoi.c \
        	$(DIR_LIB)ft_strlen.c \
        	$(DIR_LIB)ft_error.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_LIB = $(SRC_LIB:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(OBJ_LIB)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(OBJ_LIB)

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_LIB)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(OBJ_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_LIB)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re