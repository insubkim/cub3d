/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:56:58 by heson             #+#    #+#             */
/*   Updated: 2023/08/03 13:56:33 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/my_types.h"
#include "../headers/drawing_3d.h"

void	init_vars_for_drawing_line(t_drawing_line_data *data,
									double dist_of_ray, int x)
{
	data->line_height = (int)(WIN_HEIGHT / dist_of_ray);
	data->draw_start = (-data->line_height / 2) + (WIN_HEIGHT / 2);
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = (data->line_height / 2) + (WIN_HEIGHT / 2);
	if (data->draw_end >= WIN_HEIGHT)
		data->draw_end = WIN_HEIGHT - 1;
	data->line_x = x;
}

void	init_texture_data_for_drawing_line(t_drawing_line_data *data,
											double dist_of_ray, t_ray_data ray,
											t_game game_info)
{
	data->tex_img = get_texture_img(ray.side, ray.loc, game_info.map,
			game_info.player.loc);
	data->tex_step = 1.0 * data->tex_img.height / data->line_height;
	data->tex_x = get_texture_x(game_info.player.loc, ray,
			dist_of_ray, data->tex_img.width);
}

void	draw_line(t_drawing_line_data data, t_img *window_img)
{
	int		line_y;
	int		tex_y;
	double	tex_pos;

	tex_pos = (data.draw_start - WIN_HEIGHT / 2 + data.line_height / 2) \
				* data.tex_step;
	line_y = data.draw_start;
	while (line_y < data.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= data.tex_img.height)
			tex_y = data.tex_img.height - 1;
		my_mlx_pixel_put(window_img, data.line_x, line_y,
			get_color(data.tex_img, data.tex_x, tex_y));
		line_y++;
		tex_pos += data.tex_step;
	}
}
