/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:48:23 by inskim            #+#    #+#             */
/*   Updated: 2023/07/26 15:19:59 by inskim           ###   ########.fr       */
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
		return (ERROR_INT);
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
		return (ERROR_POINTER);
	}
	return (list);
}

int	set_texture(char *s, void *mlx, t_map *map)
{
	int		i;
	t_img	img;
	
	if (ft_strlen(s) < 3)
		return (ERROR_INT);
	i = 2;
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i])
		return (ERROR_INT);
	img.img = mlx_png_file_to_image(mlx, &(s[i]))
	// if (!ft_strncmp(s, "NO", 2))
	// 	
	// else if (!ft_strncmp(s, "SO", 2))

	// else if (!ft_strncmp(s, "WE", 2))

	// else if (!ft_strncmp(s, "EA", 2))

	// else
	// 	return (ERROR_INT);
}

int	check1(t_list *list, t_map *map, void *mlx)
{
	char	*s;
	
	while (list)
	{
		s = list->content;
		while (*s && *s == ' ')
			s++;
		if ((*s == 'N' || *s == 'S' || *s == 'W' || *s == 'E') && \
		set_texture(s, mlx, map) == ERROR_INT)
			return (ERROR_INT);
		else if (*s == 'F' || *s == 'C' && set_color(s, mlx, map) == ERROR_INT)
			return (ERROR_INT);
		else if (*s == '1')
			break ;
		else if (*s != '\n')
			return (ERROR_INT);
		list = list->next;
	}
	if (map->ceil_color == ERROR_INT || map->floor_color == ERROR_INT || \
		map->north_texture.img == ERROR_POINTER || \
		map->south_texture.img == ERROR_POINTER || \
		map->west_texture.img == ERROR_POINTER || \
		map->east_texture.img == ERROR_POINTER)
		return (ERROR_INT);
	return (true);
}

int	init(char *file_name, t_game *game_info)
{
	int		fd;
	t_list	*list;
	
	if (check_file_name(file_name) == ERROR_INT)
		return (ERROR_INT);
	ft_memset(game_info, 0, sizeof(game_info));
	game_info->mlx = mlx_init();
	game_info->win = mlx_new_window(game_info->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	game_info->img.img = 0;//이미지 교체 할 떄 마다 img_copy를 destory 하기 위해. 복사본 없을때 구분을 위해 0 초기화.
	fd = open(file_name, O_RDONLY, 644);
	if (fd == -1)
		return (ERROR_INT);
	list = read_file(fd, &(game_info->map));
	if (!list)// || check1(&list, &(game_info->map)) == ERROR_INT || check2(list, game_info) == ERROR_INT )
	{
		ft_lstclear(&list, free);
		return (ERROR_INT);
	}
	return (true);
}