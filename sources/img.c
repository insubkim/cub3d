/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/07/31 15:44:52 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"
#include "../headers/drawing_3d.h"
#include "../library/libft/libft.h"

void	make_img(t_game *game_info)
{
	game_info->img_copy = game_info->img.img;
	game_info->img.img = mlx_new_image(game_info->mlx, WIN_WIDTH, WIN_HEIGHT);
	game_info->img.addr = mlx_get_data_addr(game_info->img.img, \
			&(game_info->img.bits_per_pixel), &(game_info->img.line_length), \
			&(game_info->img.endian));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_ceil(t_game *game_info, int floor_color, int ceil_color)
{
	int	i;
	int	j;
	int	color;

	color = ceil_color;
	i = 0;
	while (i < WIN_HEIGHT)
	{
		if (i == WIN_HEIGHT / 2)
			color = floor_color;
		j = 0;
		while (j < WIN_WIDTH)
		{
			my_mlx_pixel_put(&(game_info->img), j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_wall(t_game *game_info)
{	
	int					x;
	double				dist;
	t_ray_data			ray;
	t_drawing_line_data	drawing_data;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_vars_for_raycasting(&ray, game_info->player, \
						2 * x / (double)WIN_WIDTH - 1);
		dist = get_dist_of_ray(x, &ray, game_info->player,
				game_info->map.board);
		init_texture_data_for_drawing_line(&drawing_data, dist, \
						ray, *game_info);
		init_vars_for_drawing_line(&drawing_data, dist, x);
		draw_line(drawing_data, &(game_info->img));
	}
}

void	draw_mouse(t_game *game_info)
{
	int	x;
	int	y;
	int	i;

	mlx_mouse_get_pos(game_info->win, &x, &y);
	i = 0;
	while (i < 20)
	{
		if (x - 10 + i >= 0 && x - 10 + i < WIN_WIDTH && y >= 0)
			my_mlx_pixel_put(&game_info->img, x - 10 + i, y, 0X00800080);
		if (y - 10 + i >= 0 && y - 10 + i < WIN_HEIGHT && x >= 0)
			my_mlx_pixel_put(&game_info->img, x, y - 10 + i, 0X00800080);
		i++;
	}
}

void	print_img(t_game *game_info)
{
	make_img(game_info);
	draw_floor_ceil(game_info, game_info->map.floor_color, \
				game_info->map.ceil_color);
	draw_wall(game_info);
	draw_map(game_info->player, game_info->img, game_info->map);
	draw_mouse(game_info);
	mlx_put_image_to_window(game_info->mlx, game_info->win, \
				game_info->img.img, 0, 0);
	if (game_info->img_copy)
		mlx_destroy_image(game_info->mlx, game_info->img_copy);
}
