/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 23:07:08 by heson             #+#    #+#             */
/*   Updated: 2023/07/28 16:11:03 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/my_types.h"
#include "../headers/raycasting.h"
#include "../library/libft/libft.h"

/* init_side_data_or_ray
 * : 광선이 세로선(x) 또는 가로선(y)에 닿았을 때의 거리를 계산하기 위해 필요한 정보를 초기화
 *
 * parameters - ray: 초기화 대상, 광선이 가로/새로선에 닿았을 때 거리를 계산하기 위해 필요한 정보
 *            - ray_loc: map board에서의 광선 좌표(세로선 - x좌표, 가로선 - y좌표)
 *            - ray_dir: 광선의 방향 벡터(세로선 - x, 가로선 - y)
 *            - player_loc: 플레이어의 위치, 광선이 뻗어나오는 시작점
 * return: none
 */
static void	init_side_data_of_ray(t_side_data_of_ray *ray, int ray_loc, double ray_dir, double player_loc, double rayDirAnother)
{
	ray->delta_dist = 1e30;
	if (ray_dir)
		ray->delta_dist = fabs(1 / ray_dir);
		
	if (ray_dir < 0)
	{
		ray->step_size = -1;
		ray->side_dist = (player_loc - ray_loc) * ray->delta_dist;
	}
	else
	{
		ray->step_size = 1;
		ray->side_dist = (ray_loc + 1.0 - player_loc) * ray->delta_dist;
	}
}

/* init_vars_for_raycasting
 * : 각 광선이 벽에 다을 때까지의 거리를 측정하기 위해 필요한 정보(ray data)를 초기화
 *
 * parameters - ray: 초기화 대상, 각 광선이 벽에 다을 때까지의 거리를 측정하기 위해 필요한 정보 
 *            - player: 플레이어 정보(현재 위치, 바라보고 있는 방향, 시야에 잡히는 화면의 크기)
 *            - camera_x: 광선이 시야에 잡히는 화면에 닿은 지점, most left = -1, mid = 0, most right = 1
 * return: none
 */
static void	init_vars_for_raycasting(t_ray_data *ray, t_player player, double camera_x)
{
	t_vector	ray_dir_vec;

	ray_dir_vec.x = player.dir.x + (player.plane.x * camera_x);
	ray_dir_vec.y = -(player.dir.y + (player.plane.y * camera_x));

	ray->loc.x = (int)(player.loc.x);
	ray->loc.y = (int)(player.loc.y);

	init_side_data_of_ray(&(ray->x), ray->loc.x, ray_dir_vec.x, player.loc.x, ray_dir_vec.y);
	init_side_data_of_ray(&(ray->y), ray->loc.y, ray_dir_vec.y, player.loc.y, ray_dir_vec.x);

	ray->is_hit = 0;
}

/* jump_to_next_side
 * : 광선의 현재 위치를 가장 가까운 다음 가로/세로선으로 이동
 *
 * parameters - side: 광선이 닿은 선이 가로선인지 세로선인지
 *            - side_data: 광선의 side data
 *            - ray_loc: 광선의 현재 위치
 *            - ray_side: 광선이 마지막으로 닿은 선이 가로선인지 세로선인지
 * return: none
 */
static void	jump_to_next_side(int side, t_side_data_of_ray *side_data, int *ray_loc, int *ray_side)
{
	side_data->side_dist += side_data->delta_dist;
	*ray_loc += side_data->step_size;
	*ray_side = side;
}

/* do_raycasting
 * : 플레이어의 현재 위치에서 시야에 잡히는 화면에 광선을 쑌다고 했을 때, 화면/벽까지의 광선의 거리를 구함
 *
 * parameters - dist_of_rays: 구하고자 하는 대상, 각 광선의 거리
 *            - player: 플레이어 정보
 *            - screen_width: 시야에 잡히는 화면의 크기
 *            - map_board: 맵 보드(2차원)
 * return: none
 */
void	do_raycasting(double **dist_of_rays, t_player player, int screen_width, char **map_board)
{	
	int		x;
	t_ray_data	ray;

	x = -1;
	while(++x < screen_width)
	{
		// init
		init_vars_for_raycasting(&ray, player, 2 * x / (double)screen_width - 1);

		// perform DDA
		while (!ray.is_hit)
		{
			//Check if ray has hit a wall
			// if(map_board[ray.loc.y][ray.loc.x] == WALL) ray.is_hit = 1;
		
			if(ray.x.side_dist < ray.y.side_dist)
				jump_to_next_side(NS, &(ray.x), &(ray.loc.x), &(ray.side));
			else
				jump_to_next_side(WE, &(ray.y), &(ray.loc.y), &(ray.side)); 

			//Check if ray has hit a wall
			if(map_board[ray.loc.y][ray.loc.x] == WALL) ray.is_hit = 1;
			
		}

		// calculate dist of ray 
		if(ray.side == NS) 
			(*dist_of_rays)[x] = (ray.x.side_dist - ray.x.delta_dist);
		else
			(*dist_of_rays)[x] = (ray.y.side_dist - ray.y.delta_dist);
	}
}

void	get_real_pixel_to_draw2(int *start, int *end, double dist_of_ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)(WIN_HEIGHT / dist_of_ray);
	draw_start = (-line_height / 2) + (WIN_HEIGHT / 2);
	
	if(draw_start < 0)
		draw_start = 0;
	draw_end = (line_height / 2) + (WIN_HEIGHT / 2);
	if(draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
    *start = draw_start;
    *end = draw_end;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

unsigned int	get_color(t_img img, int x, int y)
{
	char *dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return *(unsigned int*)dst;
}

int get_texX(t_vector player_loc, t_ray_data ray, t_vector ray_dir, double dist, int texture_width)
{
	//calculate value of wallX
    double wallX; //where exactly the wall was hit
    if (ray.side == NS) wallX = player_loc.y + dist * ray_dir.y;
    else           wallX = player_loc.x + dist * ray_dir.x;
    wallX -= floor((wallX));
	//x coordinate on the texture
	int	texWidth = texture_width;
    int texX = wallX * texWidth;
    if(ray.side == NS && ray_dir.x < 0) texX = texWidth - texX - 1;//??
    if(ray.side == WE && ray_dir.y > 0) texX = texWidth - texX - 1;//??
	return texX;
}

void	draw_line(t_game *game_info, t_ray_data ray, t_vector ray_dir, double dist, int x)
{
	int	draw_start;
	int	draw_end;
	int texX;

	get_real_pixel_to_draw2(&draw_start, &draw_end, dist);
	texX = get_texX(game_info->player.loc, ray, ray_dir, dist, game_info->map.east_texture.width);
	int	texHeight = game_info->map.east_texture.height;
	int line_height = (int)(WIN_HEIGHT / dist);
	double step = 1.0 * texHeight / line_height;
    // Starting texture coordinate
    double texPos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
    for(int y = draw_start; y<draw_end; y++)
    {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos;
        texPos += step;
        unsigned int	color = get_color(game_info->map.east_texture, texX, texY);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        my_mlx_pixel_put(&game_info->img, x, y, color);
    }
}

t_vector	get_ray_dir(t_player player, double camera_x)
{
	t_vector	ray_dir;
		
	ray_dir.x = player.dir.x + (player.plane.x * camera_x);
	ray_dir.y = -(player.dir.y + (player.plane.y * camera_x));
	return (ray_dir);
}

void	do_raycasting2(t_player player, char **map_board, t_game *game_info)
{	
	int			x;
	t_ray_data	ray;
	double		dist;
	t_vector	ray_dir;


	x = -1;
	while(++x < WIN_WIDTH)
	{
		init_vars_for_raycasting(&ray, player, 2 * x / (double)WIN_WIDTH - 1);
		while (!ray.is_hit)
		{
			if(ray.x.side_dist < ray.y.side_dist)
				jump_to_next_side(NS, &(ray.x), &(ray.loc.x), &(ray.side));
			else
				jump_to_next_side(WE, &(ray.y), &(ray.loc.y), &(ray.side)); 
			if(map_board[ray.loc.y][ray.loc.x] == WALL) ray.is_hit = 1;
		}
		if(ray.side == NS) 
			dist = (ray.x.side_dist - ray.x.delta_dist);
		else
			dist = (ray.y.side_dist - ray.y.delta_dist);
		ray_dir = get_ray_dir(player, 2 * x / (double)WIN_WIDTH - 1);
		draw_line(game_info, ray, ray_dir, dist, x);
	}
}