NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux -I./libft

MLX = -L./minilibx-linux -lmlx -lXext -lX11 -lm
LIBFT = -L./libft -lft

SRCS = src/error.c src/main.c src/mlx_utils.c \
       src/parser.c src/parser_utils.c src/parser_elements.c \
       src/parser_scene.c src/parser_objects.c src/get_next_line.c \
       src/render.c src/camera.c src/lighting.c src/intersect.c src/hit_cylinder.c \
       src/cylinder_utils.c \
       src/vec3_create.c src/vec3_operations.c src/vec3_properties.c \
       src/color.c src/ray.c \
       src/hit_sphere.c src/hit_plane.c

OBJS = $(SRCS:.c=.o)

all: libft mlx $(NAME)

libft:
	make -C libft

mlx:
	@make -C minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean
	@make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft mlx