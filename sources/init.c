/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:48:23 by inskim            #+#    #+#             */
/*   Updated: 2023/07/25 19:06:56 by inskim           ###   ########.fr       */
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

	list = ERROR_POINTER;
	while (1)
	{
		line = get_next_line(fd);
		if (line == ERROR_POINTER)
			break ;
		tmp = ft_lstnew(line);
		if (!tmp)
		{
			ft_lstclear(&list, free);
			return (ERROR_POINTER);
		}
		if (list)
			ft_lstadd_back(&list, tmp);
		else
			list = tmp;
	}
}

void	ft_put(void *s)
{
	write(1, s, ft_strlen((char*)s));
}

int	init(char *file_name, t_game *game_info)
{
	int		fd;
	t_list	*list;
	
	if (check_file_name(file_name) == ERROR_INT)
		return (ERROR_INT);
	game_info->mlx = mlx_init();
	game_info->win = mlx_new_window(game_info->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	game_info->img.img = 0;//이미지 교체 할 떄 마다 img_copy를 destory 하기 위해. 복사본 없을때 구분을 위해 0 초기화.
	fd = open(file_name, O_RDONLY, 644);
	if (fd == -1)
		return (ERROR_INT);
	list = read_file(fd, &(game_info->map));
	if (!list)// && check1(list, game_info) == ERROR_INT )
	{
		ft_lstclear(&list, free);
		return (ERROR_INT);
	}
	ft_lstiter(list, ft_put);
	//check2
	return (true);
}