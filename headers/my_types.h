/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:32:55 by heson             #+#    #+#             */
/*   Updated: 2023/07/31 18:21:57 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_TYPES_H
# define MY_TYPES_H

# include <stdlib.h>
# include <fcntl.h>

# define ERROR_INT -1
# define ERROR_POINTER NULL

# define ERROR_MAP_NAME 0
# define ERROR_MALLOC 1
# define ERROR_OPEN 2
# define ERROR_MLX_XPM_FILE_TO_IMAGE 3
# define ERROR_INVALID_TEXTURE 4
# define ERROR_INVALID_COLOR 5
# define ERROR_INVALID_MAP 6
# define ERROR_INVALID_MAP_CHAR 7
# define ERROR_TEXTURE_NOT_SET 8
# define ERROR_COLOR_NOT_SET 9
# define ERROR_ARG_NUM 10
# define ERROR_IMPOSSIBLE_CHAR 11
# define ERROR_NO_PLAYER 12

# define SUCCESS 1

# define TRUE 1
# define FALSE 0

# define PI 3.1415926535
# define ROTATE_DEGREE 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define TILESIZE 10

# define ON_KEYDOWN 2
# define ON_DESTROY 17

enum e_keycode {
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	KEY_ESC = 53
};

enum e_tile_type {
	EMPTY = '0',
	WALL = '1',
	SPACE = ' ',
	PLAYER = 'P'
};

enum e_direction {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT,
	DIR_CNT
};

typedef struct s_vector {
	double	x;
	double	y;
}	t_vector;

typedef struct s_player {
	t_vector	dir;
	t_vector	loc;
	t_vector	plane;
}	t_player;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map {
	char	**board;
	int		width;
	int		height;
	int		ceil_color;
	int		floor_color;
	t_img	north_texture;
	t_img	south_texture;
	t_img	west_texture;
	t_img	east_texture;
}	t_map;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_img		img;
	void		*img_copy;
	t_map		map;
	t_player	player;
}	t_game;

#endif