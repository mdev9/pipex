NAME = pipex

CC = cc

SRCS =	mandatory/pipex.c\
		mandatory/pipex_utils.c\
		mandatory/parsing.c\
		mandatory/pipe.c\
		mandatory/free.c

BONUS = bonus/pipex_bonus.c\
		bonus/pipex_utils_bonus.c\
		bonus/here_doc_bonus.c\
		bonus/parsing_bonus.c\
		bonus/pipe_bonus.c\
		bonus/free_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(BONUS:.c=.o)

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

all: $(NAME) libft

bonus: $(LIBFT) $(OBJS_BONUS) 
	$(CC) -g $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	$(CC) -g $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) -g $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C ./libft
	rm -f a.out libft.a

re: fclean all

.PHONY: clean all re fclean libft bonus
