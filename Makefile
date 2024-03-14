CC = gcc
S_NAME = server
C_NAME = client
FLAG = -Wall -Wextra -Werror
S_SRC = server.c
C_SRC = client.c
RM = rm
S_OBJ = $(S_SRC:.c=.o)
C_OBJ = $(C_SRC:.c=.o)


all: $(S_NAME) $(C_NAME)

$(S_NAME): $(S_OBJ)
	$(CC) $(FLAG) $(S_SRC) -o $(S_NAME)
$(C_NAME): $(C_OBJ)
	$(CC) $(FLAG) $(C_SRC) -o $(C_NAME)

bonus: $(S_NAME) $(C_NAME)

clean:
	$(RM) -f $(S_OBJ) $(C_OBJ)

fclean: clean 
	$(RM) -f $(S_OBJ) $(C_OBJ) $(S_NAME) $(C_NAME)


re: fclean all

.phony: all clean fclean re bonus