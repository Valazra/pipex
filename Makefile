NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c errors.c split.c utils.c utils2.c
INC = pipex.h
OBJ = objs
OBJS = $(addprefix $(OBJ)/, $(SRCS:.c=.o))

$(NAME):	$(OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ):
	@mkdir -p $(OBJ)

$(OBJ)/%.o: ./%.c
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re make
