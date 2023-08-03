/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:35:39 by inskim            #+#    #+#             */
/*   Updated: 2023/08/03 17:58:55 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../library/mlx/mlx.h"

static int	set_xpm_info(void *mlx, t_img *img, char *file_name)
{
	img->img = mlx_xpm_file_to_image(mlx, file_name, \
			&img->width, &img->height);
	if (!img->img)
		return (print_error(ERROR_MLX_XPM_FILE_TO_IMAGE, ERROR_INT));
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	return (TRUE);
}

int	set_texture(char *s, void *mlx, t_map *map)
{
	int		i;
	t_img	img;

	if (ft_strlen(s) < 4)
		return (print_error(ERROR_INVALID_TEXTURE, ERROR_INT));
	i = 2;
	if (s[i++] != ' ')
		return (print_error(ERROR_INVALID_TEXTURE, ERROR_INT));
	while (s[i] && s[i] == ' ')
		i++;
	if ((&s[i])[ft_strlen(&s[i]) - 1] == '\n')
		(&s[i])[ft_strlen(&s[i]) - 1] = 0;
	if (set_xpm_info(mlx, &img, &s[i]) == ERROR_INT)
		return (ERROR_INT);
	if (!ft_strncmp(s, "NO", 2) && !map->north_texture.img)
		ft_memcpy(&map->north_texture, &img, sizeof(t_img));
	else if (!ft_strncmp(s, "SO", 2) && !map->south_texture.img)
		ft_memcpy(&map->south_texture, &img, sizeof(t_img));
	else if (!ft_strncmp(s, "WE", 2) && !map->west_texture.img)
		ft_memcpy(&map->west_texture, &img, sizeof(t_img));
	else if (!ft_strncmp(s, "EA", 2) && !map->east_texture.img)
		ft_memcpy(&map->east_texture, &img, sizeof(t_img));
	else if (!ft_strncmp(s, "DO", 2) && !map->door_texture.img)
		ft_memcpy(&map->door_texture, &img, sizeof(t_img));
	else
		return (print_error(ERROR_INVALID_TEXTURE, ERROR_INT));
	return (TRUE);
}

static int	convert_rgb(char *s, int i, int cnt)
{
	int	rgb;
	int	rtn;

	rgb = 0;
	while (s[i] && ft_isdigit(s[i]) && rgb < 256)
		rgb = rgb * 10 + s[i++] - '0';
	if (ft_isdigit(s[i - 1]) == FALSE)
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	while (s[i] && s[i] == ' ')
		i++;
	if (rgb > 255 || \
		(cnt != 2 && s[i] != ',') || (cnt == 2 && s[i] != '\n'))
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	i++;
	while (s[i] && s[i] == ' ')
		i++;
	rtn = 0;
	if (cnt != 2)
		rtn = convert_rgb(s, i, cnt + 1);
	if (rtn == ERROR_INT)
		return (ERROR_INT);
	while (cnt++ < 2)
		rgb = rgb << 8;
	return (rgb + rtn);
}

int	set_color(char *s, t_map *map)
{
	int		i;
	int		color;

	if (ft_strlen(s) < 3)
		return (ERROR_INT);
	i = 1;
	if (s[i++] != ' ')
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	while (s[i] && s[i] == ' ')
		i++;
	color = convert_rgb(&s[i], 0, 0);
	if (color == ERROR_INT)
		return (ERROR_INT);
	if (*s == 'F' && map->floor_color == ERROR_INT)
		map->floor_color = color;
	else if (*s == 'C' && map->ceil_color == ERROR_INT)
		map->ceil_color = color;
	else
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	return (TRUE);
}

int	set_width_height(t_list *list, t_map *map)
{
	char	*s;
	int		len;

	while (list)
	{
		s = list->content;
		len = ft_strlen(s);
		if (s[len - 1] == '\n')
			s[--len] = 0;
		if (len == 0)
			return (print_error(ERROR_INVALID_MAP, ERROR_INT));
		if (map->width < len)
			map->width = len;
		map->height++;
		list = list->next;
	}
	if (map->height == 0 || map->width == 0)
		return (print_error(ERROR_INVALID_MAP, ERROR_INT));
	return (TRUE);
}
