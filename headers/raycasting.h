/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:17:45 by heson             #+#    #+#             */
/*   Updated: 2023/07/17 02:22:57 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

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
	t_point	loc;
	t_side_data_of_ray x;
	t_side_data_of_ray y;
	int	is_hit;
	int side;
}	t_ray_data;

#endif
