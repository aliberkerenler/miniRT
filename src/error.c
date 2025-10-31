#include "../include/minirt.h"

void	exit_error(const char *message, int error_code)
{
	if (message)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd((char *)message, 2);
	}
	exit(error_code);
}

void	free_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
}

