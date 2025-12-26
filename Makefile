NAME = miniRT
TEST = test_vec3

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux -I./libft
CFLAGS_MATH = -Wall -Wextra -Werror -I./libft

MLX = -L./minilibx-linux -lmlx -lXext -lX11 -lm
LIBFT = -L./libft -lft

SRCS = src/error.c src/main.c src/mlx_utils.c \
       src/parser.c src/parser_utils.c src/parser_elements.c src/get_next_line.c \
       src/render.c src/camera.c src/lighting.c src/intersect.c src/hit_cylinder.c
VEC_SRCS = src/vec3_create.c src/vec3_operations.c src/vec3_properties.c \
           src/color.c src/ray.c
HIT_SRCS = src/hit_sphere.c src/hit_plane.c
TEST_VEC_SRCS = tests/test_vec3.c
TEST_SPHERE_SRCS = tests/test_hit_sphere.c
TEST_PLANE_SRCS = tests/test_hit_plane.c

OBJS = $(SRCS:.c=.o)
VEC_OBJS = $(VEC_SRCS:.c=.o)
HIT_OBJS = $(HIT_SRCS:.c=.o)

all: libft mlx $(NAME)

libft:
	make -C libft

mlx:
	@make -C minilibx-linux

$(NAME): $(OBJS) $(VEC_OBJS) $(HIT_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(VEC_OBJS) $(HIT_OBJS) $(MLX) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test_vec3: libft $(VEC_OBJS)
	$(CC) $(CFLAGS_MATH) $(TEST_VEC_SRCS) $(VEC_OBJS) $(LIBFT) -lm -o test_vec3

test_sphere: libft $(VEC_OBJS) $(HIT_OBJS)
	$(CC) $(CFLAGS_MATH) $(TEST_SPHERE_SRCS) $(VEC_OBJS) $(HIT_OBJS) $(LIBFT) -lm -o test_sphere

test_plane: libft $(VEC_OBJS) $(HIT_OBJS)
	$(CC) $(CFLAGS_MATH) $(TEST_PLANE_SRCS) $(VEC_OBJS) $(HIT_OBJS) $(LIBFT) -lm -o test_plane

test: test_vec3 test_sphere test_plane
	@echo "\n=== Running Vector Tests ==="
	./test_vec3
	@echo "\n=== Running Sphere Tests ==="
	./test_sphere
	@echo "\n=== Running Plane Tests ==="
	./test_plane

clean:
	rm -f $(OBJS) $(VEC_OBJS) $(HIT_OBJS)
	make -C libft clean
	@make -C minilibx-linux clean

fclean: clean
	rm -f $(NAME) test_vec3 test_sphere test_plane
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft mlx test