/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:17:45 by heson             #+#    #+#             */
/*   Updated: 2023/07/31 15:53:29 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_3D_H
# define DRAWING_3D_H

# include "my_types.h"

enum e_side {
	NS = 0,
	WE = 1
};

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_side_data_of_ray {
	double	side_dist;
	double	delta_dist;
	int		step_size;
}	t_side_data_of_ray;

typedef struct s_ray_data {
	t_point				loc;
	t_vector			dir;
	t_side_data_of_ray	x;
	t_side_data_of_ray	y;
	int					is_hit;
	int					side;
}	t_ray_data;

typedef struct s_drawing_line_data {
	int		line_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	t_img	tex_img;
	double	tex_step;
}	t_drawing_line_data;

// raycasting
void	init_side_data_of_ray(t_side_data_of_ray *ray, int ray_loc,
			double ray_dir, double player_loc);
double	get_dist_of_ray(int x, t_ray_data *ray, t_player player,
			char **map_board);

// wall_drawing
void	init_vars_for_drawing_line(t_drawing_line_data *data,
			double dist_of_ray, int x);
void	init_texture_data_for_drawing_line(t_drawing_line_data *data,
			double dist_of_ray, t_ray_data ray, t_game game_info);
void	draw_line(t_drawing_line_data data, t_img *window_img);

#endif
