/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:07:25 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/27 16:20:34 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parser.h"

static int	close_with_data(t_data *data)
{
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->img.img_ptr);
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

static int	handle_expose(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->img.img_ptr, 0, 0);
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
	if (!data.img.img_ptr)
	{
		free_scene(data.scene);
		free_mlx(&data.mlx);
		exit_error("Failed to create image", ERR_MLX_INIT);
	}
	data.img.addr = mlx_get_data_addr(data.img.img_ptr,
			&data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	data.img.width = WIN_WIDTH;
	data.img.height = WIN_HEIGHT;
	render_scene(&data.img, data.scene);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr,
		data.img.img_ptr, 0, 0);
	mlx_hook(data.mlx.win_ptr, 12, 1L << 15, handle_expose, &data);
	mlx_hook(data.mlx.win_ptr, 17, 0, close_with_data, &data);
	mlx_key_hook(data.mlx.win_ptr, handle_key_with_data, &data);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
