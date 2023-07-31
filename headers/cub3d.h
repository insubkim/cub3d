/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:32:55 by heson             #+#    #+#             */
/*   Updated: 2023/07/31 17:27:57 by heson            ###   ########.fr       */
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

// moving
void	move_player(enum e_direction dir, t_game *game_info);
void	move_dir(enum e_direction dir, t_player *player);

// error utils
int		free_map(char ***map, int h);
int		print_error(int error, int return_code);



void	print_img(t_game *game_info);

#endif
