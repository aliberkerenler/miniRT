#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parser.h"

static int	close_with_data(t_data *data)
{
	free_scene(data->scene);
	free_mlx(&data->mlx);
	exit(0);
}

static int	handle_key_with_data(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_with_data(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_error("Usage: ./miniRT <scene.rt>", ERR_ARGS);
	data.scene = parse_scene(argv[1]);
	init_mlx(&data.mlx);
	data.img.img_ptr = mlx_new_image(data.mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr,
			&data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	data.img.width = WIN_WIDTH;
	data.img.height = WIN_HEIGHT;
	render_scene(&data.mlx, &data.img, data.scene);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr,
		data.img.img_ptr, 0, 0);
	mlx_hook(data.mlx.win_ptr, 17, 0, close_with_data, &data);
	mlx_key_hook(data.mlx.win_ptr, handle_key_with_data, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
