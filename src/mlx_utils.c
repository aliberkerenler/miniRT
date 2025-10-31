#include "../include/minirt.h"

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit_error("MLX initialization failed", ERR_MLX_INIT);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			WIN_TITLE);
	if (!mlx->win_ptr)
	{
		free_mlx(mlx);
		exit_error("Window creation failed", ERR_MLX_WINDOW);
	}
	return (0);
}

int	close_window(t_mlx *mlx)
{
	free_mlx(mlx);
	exit(0);
	return (0);
}

int	handle_keypress(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		close_window(mlx);
	return (0);
}

