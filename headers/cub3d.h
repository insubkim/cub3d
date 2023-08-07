/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:32:55 by heson             #+#    #+#             */
/*   Updated: 2023/08/07 12:16:54 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "my_types.h"
# include "../library/libft/libft.h"

// init
int		init(char *file_name, t_game *game_info);
int		map_parsing(t_list *target, t_game *game_data);
int		is_valid_map(t_map *map, t_vector *player_loc, char *player_dir);
int		set_color(char *s, t_map *map);
int		set_texture(char *s, void *mlx, t_map *map);
int		set_width_height(t_list *list, t_map *map);

// error utils
int		free_map(char ***map, int h);
int		print_error(int error, int return_code);
int		free_timer(double ***map, int h);

// moving
void	move_player(enum e_direction dir,
			t_game *game_info, char **board, t_vector loc);
void	move_dir(enum e_direction dir, t_player *player);

// door
void	handle_door(t_game *game_info);
int		init_door_timer(t_game *game_info);
void	run_door_timer(t_game *game_info);

// img
void	print_img(t_game *game_info);

#endif
