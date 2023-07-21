/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 23:07:08 by heson             #+#    #+#             */
/*   Updated: 2023/07/21 19:13:07 by heson            ###   ########.fr       */
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
		// ray->delta_dist = sqrt(1 + (rayDirAnother * rayDirAnother) / (ray_dir * ray_dir));
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

	//init_side_data_of_ray(&(ray->x), ray->loc.x, ray_dir_vec.x, player.dir.x);
	//init_side_data_of_ray(&(ray->y), ray->loc.y, ray_dir_vec.y, player.dir.y);

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
