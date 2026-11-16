/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 19:53:04 by manmaria          #+#    #+#             */
/*   Updated: 2026/11/16 20:18:21 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H 
# define ENGINE_H 

# include "stdbool.h"

typedef struct s_ray
{
	double	camera_x;			/* Position on camera plane (-1 to 1) */
	double	dir_x;				/* Ray direction X */
	double	dir_y;				/* Ray direction Y */
	int		map_x;				/* Current map tile X */
	int		map_y;				/* Current map tile Y */
	double	delta_dist_x;		/* Ray distance to next X gridline */
	double	delta_dist_y;		/* Ray distance to next Y gridline */
	double	side_dist_x;		/* Initial distance to first X gridline */
	double	side_dist_y;		/* Initial distance to first Y gridline */
	int		side_x;				/* Direction to step in X (+1 or -1) */
	int		side_y;				/* Direction to step in Y (+1 or -1) */
	bool	hit;				/* true if wall hit, 0 otherwise */
	int		side;				/* 0 for North/South, 1 for East/West */
	double	perp_wall_dist;		/* Perpendicular distance to wall */
	int		line_height;		/* Projected slice height in pixels */
	int		draw_start;			/* Screen Y where wall slice starts */
	int		draw_end;			/* Screen Y where wall slice ends */
}				t_ray;

#endif
