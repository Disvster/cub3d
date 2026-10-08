/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 19:11:43 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/08 19:26:52 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../libft/incs/libft.h"
# include "../minilibx-linux/mlx.h"
/* Window settings */
# define WIN_WIDTH	1280
# define WIN_HEIGHT	720
# define WIN_TITLE	"cub3D"
/* Linux Key codes */
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
/* MLX Event codes */
# define ON_KEYDOWN	2
# define ON_DESTROY	17
/* Texture indexes */
# define TEX_NO		0
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3

/* Image buffer for MLX */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Player position and view vectors */
typedef struct s_player
{
	double	pos_x;			/* Player grid X coordinate */
	double	pos_y;			/* Player grid Y coordinate */
	double	dir_x;			/* Direction vector X */
	double	dir_y;			/* Direction vector Y */
	double	plane_x;		/* Camera plane X (field of view) */
	double	plane_y;		/* Camera plane Y */
}	t_player;

/* Parsed scene information (Teammate A fills this!) */
typedef struct s_map
{
	char	*no_path;			/* Path to North texture */
	char	*so_path;			/* Path to South texture */
	char	*we_path;			/* Path to West texture */
	char	*ea_path;			/* Path to East texture */
	int		floor_color;		/* Hex integer: 0xRRGGBB */
	int		ceiling_color;		/* Hex integer: 0xRRGGBB */
	char	**grid;				/* 2D array of map rows */
	int		width;				/* Maximum row width */
	int		height;				/* Number of map rows */
}	t_map;

/* Main Game struct */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		tex[4];
	t_map		map;
	t_player	player;
}	t_game;

/* Function prototypes */
int		clean_exit(t_game *game);
int		error_msg(char *msg);
void	init_window(t_game *game);

#endif
