/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:56:19 by inskim            #+#    #+#             */
/*   Updated: 2023/07/31 17:02:38 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "my_types.h"
#include "../library/libft/libft.h"

int		map_parsing(t_list *target, t_game *game_data);

void	print_img(t_game *game_info);

int	print_error(int error, int return_code);

#endif