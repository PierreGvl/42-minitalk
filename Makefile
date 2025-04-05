# Project names
SERVER_NAME = server
CLIENT_NAME = client

# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -Werror

# Sources and objects
SERVER_SRC = server.c utils.c
CLIENT_SRC = client.c utils.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Include directory
INCLUDE = -I.

# Rules
all: $(SERVER_NAME) $(CLIENT_NAME)

# Compile server
$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(SERVER_NAME)

# Compile client
$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(CLIENT_NAME)

# Compile objects
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Clean objects
clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

# Clean objects and executables
fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)

# Clean and rebuild
re: fclean all

# Bonus part
bonus: all

.PHONY: all clean fclean re bonus