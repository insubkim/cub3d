/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:03:37 by heson             #+#    #+#             */
/*   Updated: 2023/07/31 14:31:13 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/my_types.h"
#include "../library/libft/libft.h"

int	is_valid_map(t_map *map, t_vector *player_loc, char *player_dir);
int	free_map(char **map, int h);

static int	init_map_board(t_list *list_p, t_map *map)
{
	int		h;
	int		w;
	char	*p;

	map->board = (char **)malloc(sizeof(char *) * map->height);
	if (!map->board)
		return (free_map(map->board, 0));
	h = -1;
	while (++h < map->height)
	{
		map->board[h] = (char *)ft_calloc(map->width, sizeof(char));
		if (!map->board[h] || !list_p || !(char *)(list_p->content))
			return (free_map(map->board, h));
		p = (char *)list_p->content;
		w = -1;
		while (++w < map->width)
		{
			if (*p)
				map->board[h][w] = *p++;
			else
				map->board[h][w] = ' ';
		}
		list_p = list_p->next;
	}
	return (SUCCESS);
}

static void	init_player(t_player *player, t_vector loc, char dir)
{
	player->loc = loc;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (dir == 'N')
	{
		player->plane.x = 0.66;
		player->dir.y = 1;
	}
	else if (dir == 'S')
	{
		player->plane.x = -0.66;
		player->dir.y = -1;
	}
	else if (dir == 'E')
	{
		player->dir.x = 1;
		player->plane.y = -0.66;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1;
		player->plane.y = 0.66;
	}
}

int	map_parsing(t_list *target, t_game *game_data)
{
	t_vector	player_loc;
	char		player_dir;

	if (init_map_board(target, &(game_data->map)) == ERROR_INT)
		return (ERROR_INT);
	player_dir = 0;
	if (!is_valid_map(&(game_data->map), &player_loc, &player_dir))
		return (free_map(game_data->map.board, game_data->map.height));
	init_player(&(game_data->player), player_loc, player_dir);
	return (SUCCESS);
}

/*
#define test_height 14
#include <stdio.h>

int main() {

	t_list *head = NULL;
	t_game game_data;
	
	char* arrs[test_height] = {	"        1111111111111111111111111",
								"        1000000000110000000000001",
								"   111  1011000001110000000000001",
								"        1001000000000000000000001",
								"111111111011000001110000000000001",
								"100000000011000001110111110011111",
								"11110111111111011100000010001",
								"11110111111111000001010010001",
								"11000000110101011100000000001    ",
								"10000000000000001100000010001    ",
								"1000000000000000110101001000111  ",
								"11000001110101011111011010001    ",
								"11110111 1110101 100011000S01    ",
								"11111111 1111111 111111111111    "	};

	for (int i=0; i<test_height; i++) {
		char *content = ft_strdup(arrs[i]);
		t_list *new_node = ft_lstnew(content);
		ft_lstadd_back(&head, new_node);
	}
	game_data.map.height = test_height;
	game_data.map.width = 33;
	
	int ret = map_parsing(head, &game_data);
	printf("%s", ret == SUCCESS ? "SUCCESS" : "ERROR");
	printf("(%lf, %lf), (%lf, %lf), (%lf, %lf)\n", game_data.player.loc.x, game_data.player.loc.y, game_data.player.dir.x, game_data.player.dir.y, game_data.player.plane.x, game_data.player.plane.y);
}
*/