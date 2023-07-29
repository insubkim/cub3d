/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:17:45 by heson             #+#    #+#             */
/*   Updated: 2023/07/28 21:23:11 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_3D_H
# define DRAWING_3D_H

# include "my_types.h"

enum side {
	NS = 0,	// 세로선, x
	WE = 1	// 가로선, y
};

// 맵 좌표, 2차원 map board의 한 칸의 위치
typedef	struct s_point
{
	int	x;
	int	y;
}	t_point;

// 광선이 세로선(x) 또는 가로선(y)에 닿았을 때의 거리를 계산하기 위해 필요한 정보
typedef struct	s_side_data_of_ray
{
	double	side_dist;	// 광선의 현재 위치에서 가장 가까운 선, 현재 광선 위치 포함
	double	delta_dist;	// 광선의 현재 위치에서 광선 방향으로 뻗었을 때 두 번째로 닿는 선
	int		step_size;	// 광선이 뻗아나가는 방향 (가로선: E - 1, W - -1, 세로선: N - 1, S - -1)
}	t_side_data_of_ray;

// 광선이 벽에 다을 때까지의 거리를 측정하기 위해 필요한 정보
typedef struct	s_ray_data
{
	t_point				loc;
	t_vector			dir;
	t_side_data_of_ray	x;
	t_side_data_of_ray	y;
	int					is_hit;
	int					side;
}	t_ray_data;

typedef struct	s_drawing_line_data
{
	int		line_x;
	int		line_height;
	int		draw_start; // start point of line in window
	int		draw_end;	// end point of line in window
	int		tex_x;
	t_img	tex_img;	// textrue image 
	double	tex_step;	// How much to increase the texture coordinate per screen pixel
}	t_drawing_line_data;

// raycasting
void	init_vars_for_raycasting(t_ray_data *ray, t_player player, double camera_x);
double	get_dist_of_ray(int x, t_ray_data *ray, t_player player, char **map_board);

// wall_drawing
void	init_vars_for_drawing_line(t_drawing_line_data *data, double dist_of_ray, int x);
void	init_texture_data_for_drawing_line(t_drawing_line_data *data, double dist_of_ray, t_ray_data ray, t_game game_info);
void	draw_line(t_drawing_line_data data, t_img *window_img);

// drawing_uils
int				get_texture_x(t_vector player_loc, t_ray_data ray, double dist, int texture_width);
t_img			get_texture_img(int hit_side, t_point hitpoint, t_map map, t_vector player_loc);
unsigned int	get_color(t_img img, int x, int y);

#endif
