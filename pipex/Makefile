NAME = pipex

SRCS = ft_utils.c pipex.c pipex_2.c

OBJS = $(SRCS:.c=.o)

GCC = clang

FLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(GCC) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	clang $(FLAGS) -o $(NAME) $(OBJS) -L libft -lft

bonus: all

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C ./libft

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re: fclean all

norm:

	norminette ./libft/*.c
	norminette ./libft/*.h
	norminette *.h
	norminette *.c

.PHONY:	all bonus clean fclean re norm
