/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmaria <manmaria@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 19:33:34 by manmaria          #+#    #+#             */
/*   Updated: 2026/11/16 20:44:34 by manmaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"
#include "../../incs/engine.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	ray->hit = false;
}

void	step_side_dist(t_game *g, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->side_x = -1;
		ray->side_dist_x = (g->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->side_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->side_y = -1;
		ray->side_dist_y = (g->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->side_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->player.pos_y) * ray->delta_dist_y;
	}
}

void	wall_height(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = false;
	//ray->is_door = false;
	while (ray->hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->side_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->side_y;
			ray->side = 1;
		}
		//check_collision(ray, game);
		if (!ray->hit)// && ray->is_door)
			continue ;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = -1;
	while (y < WIN_HEIGHT)
	{
	  //  TODO:
	  // • Draw pixels from y = 0 to WIN_HEIGHT - 1:
	  //    • If y < ray->draw_start: put game->map.ceiling_color.
	  //    • If y >= ray->draw_start && y <= ray->draw_end:
	  //        • Put a wall color. (E.g., 0xFF0000 if side == 0, 
		//        and a darker 0x880000 if side == 1 to create shading!).
	  //    • If y > ray->draw_end: put game->map.floor_color.
	}
}

int	cast_rays(t_game *game)
{
	t_ray	ray;
	int		i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		init_ray(game, &ray, i);
		step_side_dist(game, &ray);
		perform_dda(game, &ray);
		wall_height(&ray);
		draw_column(game, &ray, i);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
	return (0);
}
