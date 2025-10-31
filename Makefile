NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux -I./libft

MLX = -L./minilibx-linux -lmlx -lXext -lX11

LIBFT = -L./libft -lft

SRCS = src/error.c src/main.c src/mlx_utils.c

OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft mlx