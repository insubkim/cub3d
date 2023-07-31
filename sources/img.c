/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/07/31 14:30:18 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"
#include "../headers/drawing_3d.h"
#include "../library/libft/libft.h"


void    draw_map(t_player player, t_img img, t_map map);//test
void	__test_player_print(t_game *game_info);//test
void	do_raycasting(double **dist_of_rays, t_player player, int screen_width, char **map_board);//test
void	do_raycasting2(t_player player, char **map_board, t_game *game_info);


/* make_img
 * : mlx 이미지 초기화, 플레이어 이동시 변경 전, 변경 후 img 둘 을 가지게 됨. 
 *   변경 후 img를 화면에 표시하고 나서 변경 전 img를 파괴시키기 때문에,
 *   변경 전 img 사본을 img_copy에 저장시킴.
 * parameters - game_info: 게임 정보
 * return: none
 */
void    make_img(t_game *game_info)
{
    game_info->img_copy = game_info->img.img;
    game_info->img.img = mlx_new_image(game_info->mlx, WIN_WIDTH, WIN_HEIGHT);   
    game_info->img.addr = mlx_get_data_addr(game_info->img.img, \
                &(game_info->img.bits_per_pixel), &(game_info->img.line_length), \
                &(game_info->img.endian));
}

/* my_mlx_pixel_put
 * : img (x, y) 좌표에 color 픽셀 값을 넣음.
 *
 * parameter - img: 픽셀 넣을 이미지
 *           - x: x좌표
 *           - y: y좌표
 *           - color: 픽셀 색
 * return: none
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/* draw_floor_ceil
 * : 바닥과 천장을 img에 표시함.
 * parameters - game_info: 게임 정보
 *            - floor_color: 바닥 색
 *            - ceil_color: 천장 색
 * return: none
 */
void    draw_floor_ceil(t_game *game_info, int floor_color, int ceil_color)
{
    int i;
    int j;
    int color;

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
		dist = get_dist_of_ray(x, &ray, game_info->player,
				game_info->map.board);
		init_texture_data_for_drawing_line(&drawing_data, dist,
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
			my_mlx_pixel_put(&game_info->img, x - 10 + i, y, 0x00FFFFFF);
		if (y - 10 + i >= 0 && y - 10 + i < WIN_HEIGHT && x >= 0)
			my_mlx_pixel_put(&game_info->img, x, y - 10 + i, 0x00FFFFFF);
		i++;
	}

}

/* print_img
 * : mlx 이미지 생성 -> 천장 바닥 -> 벽 -> 맵 순으로 이미지 초기화 후, 화면에 표시
 * parameter - game_info: 게임정보
 * return: none
 */
void    print_img(t_game *game_info)
{
	make_img(game_info);
	draw_floor_ceil(game_info, 0x00000000, 0x00FF0000);
    draw_wall(game_info);//do_raycasting
	// do_raycasting2(game_info->player, game_info->map.board, game_info);
	
	draw_map(game_info->player, game_info->img, game_info->map);
	draw_mouse(game_info);
	mlx_put_image_to_window(game_info->mlx, game_info->win, game_info->img.img, 0, 0);
	if (game_info->img_copy)
		mlx_destroy_image(game_info->mlx, game_info->img_copy);
}