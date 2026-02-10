#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define ERR_MALLOC 1
# define ERR_MLX_INIT 2
# define ERR_MLX_WINDOW 3
# define ERR_ARGS 4
# define ERR_FILE 5

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define WIN_TITLE "miniRT"

# define KEY_ESC 65307

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

void	exit_error(const char *message, int error_code);
void	free_mlx(t_mlx *mlx);

int		init_mlx(t_mlx *mlx);
int		close_window(t_mlx *mlx);
int		handle_keypress(int keycode, t_mlx *mlx);

#endif