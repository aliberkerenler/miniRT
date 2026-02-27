/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerenler <aerenler@student.42istanbul.com.t+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:03:59 by aerenler          #+#    #+#             */
/*   Updated: 2026/02/22 15:05:14 by aerenler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define ERR_MALLOC 1
# define ERR_MLX_INIT 2
# define ERR_MLX_WINDOW 3
# define ERR_ARGS 4

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

#endif
