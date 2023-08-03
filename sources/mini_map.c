/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:40:12 by inskim            #+#    #+#             */
/*   Updated: 2023/08/03 18:47:17 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/cub3d.h"
#include "../headers/drawing_3d.h"

static void	set_map_white(t_img img)
{
	int	i;
	int	j;

	i = WIN_HEIGHT - 220;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < 220)
		{
			my_mlx_pixel_put(&img, j, i, 0x00FFFFFF);
			j++;
		}		
		i++;
	}
}

static void	draw_map_ray(t_vector dir, t_img img, double dist)
{
	int		i;
	double	x;
	double	y;
	double	radian;

	i = 0;
	radian = atan2(dir.y, dir.x);
	dist *= 20;
	x = 100;
	y = 100 + (WIN_HEIGHT - 220);
	while (i < dist)
	{
		x += cos(radian);
		y += sin(radian);
		if (x > 0 && x < 220 && y > 0 && y >= WIN_HEIGHT - 220)
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		i++;
	}
}

static void	init_side_data_of_ray_for_map(t_side_data_of_ray *ray, \
		double ray_dir, double ray_dir_another, double player_loc)
{
	ray->delta_dist = 1e30;
	if (ray_dir)
		ray->delta_dist = \
		sqrt(1 + (ray_dir_another * ray_dir_another) / (ray_dir * ray_dir));
	if (ray_dir < 0)
	{
		ray->step_size = -1;
		ray->side_dist = (player_loc - (int)player_loc) * ray->delta_dist;
	}
	else
	{
		ray->step_size = 1;
		ray->side_dist = ((int)player_loc + 1.0 - player_loc) * ray->delta_dist;
	}
}

void	raycast(t_player player, t_img img, t_map map)
{	
	int			x;
	double		dist;
	t_ray_data	ray;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_vars_for_raycasting(&ray, player, 2 * x / (double)WIN_WIDTH - 1);
		init_side_data_of_ray_for_map(&(ray.x), \
								ray.dir.x, ray.dir.y, player.loc.x);
		init_side_data_of_ray_for_map(&(ray.y), \
								ray.dir.y, ray.dir.x, player.loc.y);
		dist = get_dist_of_ray(&ray, map.board);
		draw_map_ray(ray.dir, img, dist);
	}
}

void	draw_map(t_player player, t_img img, t_map map)
{
	int		i;
	int		j;
	t_point	p;

	set_map_white(img);
	p.x = (int)(player.loc.x * 20);
	p.y = (int)(player.loc.y * 20);
	i = -1;
	while (++i < 220)
	{
		if (p.y + i - 100 < 0 || p.y + i - 100 >= map.height * 20)
			continue ;
		j = -1;
		while (++j < 220)
		{
			if (p.x + j - 100 < 0 || p.x + j - 100 >= map.width * 20)
				continue ;
			if (map.board[(p.y + i - 100) / 20][(p.x + j - 100) / 20] == WALL \
			|| map.board[(p.y + i - 100) / 20][(p.x + j - 100) / 20] == DOOR)
				my_mlx_pixel_put(&img, j, i + (WIN_HEIGHT - 220), 0x00808080);
			else if ((i - 100) * (i - 100) + (j - 100) * (j - 100) < 30)
				my_mlx_pixel_put(&img, j, i + (WIN_HEIGHT - 220), 0x00006400);
		}
	}
	raycast(player, img, map);
}
