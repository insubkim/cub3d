/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:12:22 by heson             #+#    #+#             */
/*   Updated: 2023/08/07 18:50:57 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/my_types_bonus.h"
#include "../../library/libft/libft.h"

int	free_map(char ***map, int h)
{
	int	i;

	i = 0;
	while (i < h && (*map)[i])
		free((*map)[i++]);
	if (*map)
		free(*map);
	*map = NULL;
	return (ERROR_INT);
}

int	free_timer(double ***map, int h)
{
	int	i;

	i = 0;
	while (i < h && (*map)[i])
		free((*map)[i++]);
	if (*map)
		free(*map);
	*map = NULL;
	return (ERROR_INT);
}

int	print_error(int error, int return_code)
{
	if (error == ERROR_MAP_NAME)
		ft_putstr_fd("Error\nInvalid map name\n", 2);
	else if (error == ERROR_MALLOC)
		ft_putstr_fd("Error\nMalloc failed\n", 2);
	else if (error == ERROR_OPEN)
		ft_putstr_fd("Error\nOpen failed\n", 2);
	else if (error == ERROR_MLX_XPM_FILE_TO_IMAGE)
		ft_putstr_fd("Error\nmlx_xpm_file_to_image failed\n", 2);
	else if (error == ERROR_INVALID_TEXTURE)
		ft_putstr_fd("Error\nInvalid texture\n", 2);
	else if (error == ERROR_INVALID_COLOR)
		ft_putstr_fd("Error\nInvalid color\n", 2);
	else if (error == ERROR_INVALID_MAP)
		ft_putstr_fd("Error\nInvalid map\n", 2);
	else if (error == ERROR_TEXTURE_NOT_SET)
		ft_putstr_fd("Error\nTexture not set\n", 2);
	else if (error == ERROR_COLOR_NOT_SET)
		ft_putstr_fd("Error\nColor not set\n", 2);
	else if (error == ERROR_ARG_NUM)
		ft_putstr_fd("Error\nInvalid argument number\n", 2);
	else if (error == ERROR_IMPOSSIBLE_CHAR)
		ft_putstr_fd("Error\nImpossible char\n", 2);
	else if (error == ERROR_NO_PLAYER)
		ft_putstr_fd("Error\nNo player in map\n", 2);
	return (return_code);
}

int	check_file_name(char *file_name)
{
	if (!ft_strrchr(file_name, '.') || \
		ft_strncmp(ft_strrchr(file_name, '.'), ".cub", 4))
		return (ERROR_INT);
	if (!ft_strrchr(file_name, '/'))
	{
		if (ft_strlen(file_name) < 5)
			return (ERROR_INT);
		return (SUCCESS);
	}
	if (ft_strlen(ft_strrchr(file_name, '/')) < 6)
		return (ERROR_INT);
	return (SUCCESS);
}
