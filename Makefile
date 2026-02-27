NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux -I./libft

MLX = -L./minilibx-linux -lmlx -lXext -lX11 -lm
LIBFT = -L./libft -lft

SRCS = src/main.c src/error.c src/mlx_utils.c \
       src/parser/parser.c src/parser/parser_utils.c \
       src/parser/parser_elements.c src/parser/parser_scene.c \
       src/parser/parser_objects.c src/parser/parser_plane.c \
       src/parser/parser_cylinder.c src/parser/parser_light.c \
       src/parser/get_next_line.c src/parser/parser_validate.c \
       src/parser/parser_validate2.c src/parser/parser_validate3.c \
       src/parser/parser_validate4.c \
       src/render/render.c src/render/camera.c src/render/lighting.c \
       src/render/intersect.c src/render/ray.c \
       src/geometry/hit_sphere.c src/geometry/hit_plane.c \
       src/geometry/hit_cylinder.c src/geometry/cylinder_utils.c \
       src/math/vec3_create.c src/math/vec3_operations.c \
       src/math/vec3_properties.c src/math/color.c

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

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft mlx