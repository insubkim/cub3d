/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:48:23 by inskim            #+#    #+#             */
/*   Updated: 2023/07/31 16:45:03 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"
#include "../headers/get_next_line.h"
#include "../library/libft/libft.h"

int	check_file_name(char *file_name)
{
	char	*format;

	format = ft_strrchr(file_name, '.');
	if (!format || ft_strncmp(format, ".cub", 4) || ft_strlen(format) != 4)
		return (print_error(ERROR_MAP_NAME, ERROR_INT));
	return (true);
}

t_list	*read_file(int fd, t_map *map)
{
	char	*line;
	t_list	*list;
	t_list	*tmp;
	int		is_eof;

	is_eof = 0;
	list = 0;
	while (1)
	{
		line = get_next_line(fd, &is_eof);
		if (line == ERROR_POINTER)
			break ;
		tmp = ft_lstnew(line);
		if (!tmp)
			break ;
		ft_lstadd_back(&list, tmp);
	}
	if (!is_eof || !tmp)
	{
		ft_lstclear(&list, free);
		print_error(ERROR_MALLOC, ERROR_INT);
		return (ERROR_POINTER);
	}
	return (list);
}

int	set_xpm_info(void *mlx, t_img *img, char *file_name)
{
	img->img = mlx_xpm_file_to_image(mlx, file_name, \
			&img->width, &img->height);
	if (!img->img)
		return (print_error(ERROR_MLX_XPM_FILE_TO_IMAGE, ERROR_INT));
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	return (true);
}

int	set_texture(char *s, void *mlx, t_map *map)
{
	int		i;
	t_img	img;

	if (ft_strlen(s) < 4)
		return (print_error(ERROR_INVALID_TEXTURE, ERROR_INT));
	i = 2;
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
	else
		return (print_error(ERROR_INVALID_TEXTURE, ERROR_INT));
	return (true);
}

int	convert_rgb(char *s)
{
	int	color;
	int	rgb;

	rgb = 0;
	while (*s && ft_isdigit(*s) && rgb < 256)
		rgb = rgb * 10 + *s++ - '0';
	if (rgb > 255 || *s++ != ',')
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	color = rgb;
	rgb = 0;
	while (*s && ft_isdigit(*s) && rgb < 256)
		rgb = rgb * 10 + *s++ - '0';
	if (rgb > 255 || *s++ != ',')
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	color = (color << 8) + rgb;
	rgb = 0;
	while (*s && ft_isdigit(*s) && rgb < 256)
		rgb = rgb * 10 + *s++ - '0';
	if (rgb > 255 || (*s && *s != '\n') || *(s - 1) == ',')
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	color = (color << 8) + rgb;
	return (color);
}

int	set_color(char *s, t_map *map)
{
	int		i;
	int		color;
	int		rgb;		

	if (ft_strlen(s) < 3)
		return (ERROR_INT);
	i = 1;
	while (s[i] && s[i] == ' ')
		i++;
	color = convert_rgb(&s[i]);
	if (color == ERROR_INT)
		return (ERROR_INT);
	if (*s == 'F' && map->floor_color == ERROR_INT)
		map->floor_color = color;
	else if (*s == 'C' && map->ceil_color == ERROR_INT)
		map->ceil_color = color;
	else
		return (print_error(ERROR_INVALID_COLOR, ERROR_INT));
	return (true);
}

int	is_texture_set(t_map *map)
{
	if (map->ceil_color == ERROR_INT || map->floor_color == ERROR_INT)
		return (print_error(ERROR_COLOR_NOT_SET, ERROR_INT));
	if (map->north_texture.img == ERROR_POINTER || \
			map->south_texture.img == ERROR_POINTER || \
			map->west_texture.img == ERROR_POINTER || \
			map->east_texture.img == ERROR_POINTER)
		return (print_error(ERROR_TEXTURE_NOT_SET, ERROR_INT));
	return (true);
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
	return (true);
}

int	is_valid_char(char c)
{
	if (c == '\n' || c == 'F' || c == 'C' || \
			c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

int	set_map_info(t_list *list, t_map *map, void *mlx, t_game *game_info)
{
	char	*s;

	while (list)
	{
		s = list->content;
		while (*s && *s == ' ')
			s++;
		if (*s == '1')
			break ;
		list = list->next;
		if ((*s == 'N' || *s == 'S' || *s == 'W' || *s == 'E') && set_texture(s, mlx, map) == ERROR_INT)
			return (ERROR_INT); 
		else if ((*s == 'F' || *s == 'C') && set_color(s, map) == ERROR_INT)
			return (ERROR_INT);
		else if (*s && !is_valid_char(*s))
			return (print_error(ERROR_IMPOSSIBLE_CHAR, ERROR_INT));
	}
	map->width = 0;
	map->height = 0;
	if (is_texture_set(map) == ERROR_INT || \
			set_width_height(list, map) == ERROR_INT || \
			map_parsing(list, game_info) == ERROR_INT)
		return (ERROR_INT);
	return (true);
}

int	init(char *file_name, t_game *game_info)
{
	int		fd;
	t_list	*list;

	if (check_file_name(file_name) == ERROR_INT)
		return (ERROR_INT);
	ft_memset(game_info, 0, sizeof(t_game));
	game_info->map.ceil_color = ERROR_INT;
	game_info->map.floor_color = ERROR_INT;
	game_info->mlx = mlx_init();
	game_info->win = mlx_new_window(game_info->mlx, \
			WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	fd = open(file_name, O_RDONLY, 644);
	if (fd == -1)
		return (print_error(ERROR_OPEN, ERROR_INT));
	list = read_file(fd, &(game_info->map));
	if (list == ERROR_POINTER)
		return (ERROR_INT);
	if (set_map_info(list, &game_info->map, \
				game_info->mlx, game_info) == ERROR_INT)
	{
		ft_lstclear(&list, free);
		return (ERROR_INT);
	}
	ft_lstclear(&list, free);
	return (true);
}
