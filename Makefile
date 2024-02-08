NAME = pipex

CC = gcc

SRCS =	pipex.c\
		pipex_utils.c
		
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): libft $(OBJS) 
	$(CC) -g $(FLAGS) $(OBJS) -o $(NAME) -I . -L ./libft -lft

libft:
	make -C ./libft

.c.o:
	$(CC) -g $(FLAGS) -c $< -o $@ -I . -L ./libft -lft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft
	rm -f a.out libft.a

re: fclean all

.PHONY: clean all re fclean libft
