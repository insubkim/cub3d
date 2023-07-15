/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:32:55 by heson             #+#    #+#             */
/*   Updated: 2023/07/15 22:19:05 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_TYPES_H
# define MY_TYPES_H

# include <stdbool.h>
# include <stdlib.h>
#include <math.h>

# define ERROR_BOOL 0
# define ERROR_INT -1
# define ERROR_POINTER NULL

# define PI 3.1415926535
# define ROTATE_DEGREE 10

# define WIN_WIDTH 200
# define WIN_HEIGHT 300

# define TILESIZE 4

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

typedef struct s_map {
	char	**board;
	int		width;
	int		height;
}		t_map;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		*img_copy;
	t_map		map;
	t_player	player;
}	t_game;

#endif