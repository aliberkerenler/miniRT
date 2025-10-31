#include "../include/minirt.h"

int	main(void)
{
	t_mlx	mlx;

	init_mlx(&mlx);
	mlx_hook(mlx.win_ptr, 17, 0, close_window, &mlx);
	mlx_key_hook(mlx.win_ptr, handle_keypress, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
