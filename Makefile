NAME_CLIENT = client
NAME_SERVER = server
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
LIB_DIR = lib/
INCLUDES = inc/

SRC_CLIENT = $(SRC_DIR)client.c
SRC_SERVER = $(SRC_DIR)server.c

LIB_SRC = $(LIB_DIR)ft_putchar_fd.c \
          $(LIB_DIR)ft_putstr_fd.c \
          $(LIB_DIR)ft_putnbr_fd.c \
          $(LIB_DIR)ft_putendl_fd.c \
          $(LIB_DIR)ft_isdigit.c \
          $(LIB_DIR)ft_atoi.c \
          $(LIB_DIR)ft_strlen.c \
          $(LIB_DIR)ft_error.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_LIB = $(LIB_SRC:.c=.o)

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