NAME = pipex

CC = cc

MANDATORY_DIR = mandatory/

BONUS_DIR = bonus/

SRCS =	pipex.c\
		pipex_utils.c\
		parsing.c\
		pipe.c\
		free.c

BONUS = pipex_bonus.c\
		pipex_utils_bonus.c\
		here_doc_bonus.c\
		parsing_bonus.c\
		pipe_bonus.c\
		free_bonus.c

OBJS = $(addprefix $(MANDATORY_DIR), $(SRCS:.c=.o))

OBJS_BONUS = $(addprefix $(BONUS_DIR), $(BONUS:.c=.o))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): libft $(OBJS) 
	$(CC) -g $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

bonus: libft $(OBJS_BONUS) 
	$(CC) -g $(FLAGS) $(OBJS_BONUS) libft/libft.a -o $(NAME)

libft:
	make -C ./libft

$(MANDATORY_DIR)%.o: $(MANDATORY_DIR)%.c
	$(CC) -g $(FLAGS) -c $< -o $@

$(BONUS_DIR)%.o: $(BONUS_DIR)%.c
	$(CC) -g $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft
	rm -f a.out libft.a

re: fclean all

.PHONY: clean all re fclean libft
