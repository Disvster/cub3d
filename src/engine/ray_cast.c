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
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = true;
		if (!ray->hit)// && ray->is_door)
			continue ;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
	// NOTE:
	//    • y * img->line_len: Moves the pointer down y rows of pixels.
    //    • x * (img->bpp / 8): Moves x pixels across the row (bpp / 8 = 4 bytes per pixel in 32-bit color).
	//    • *(unsigned int *)dst = color: Writes the 4-byte hex color (0xRRGGBB).
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	wall_color;

	if (ray->side == 1)
		wall_color = 0x880000;
	else
		wall_color = 0xFF0000;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		if (y < ray->draw_start)
			put_pixel(&game->frame, x, y, game->map.ceiling_color);
		else if (y <= ray->draw_end)
			put_pixel(&game->frame, x, y, wall_color);
		else
			put_pixel(&game->frame, x, y, game->map.floor_color);
	}
	//NOTE:
	//Alternative: 3 sequential loops
  // │ You can also split it into three separate while-loops:
  // │
  // │ 1. while (y < ray->draw_start) → draw ceiling.
  // │ 2. while (y <= ray->draw_end) → draw wall.
  // │ 3. while (y < WIN_HEIGHT) → draw floor.
  // │
  // │ This avoids checking if / else if / else on every single pixel.
	  //  TODO:
	  // • Draw pixels from y = 0 to WIN_HEIGHT - 1:
	  //    • If y < ray->draw_start: put game->map.ceiling_color.
	  //    • If y >= ray->draw_start && y <= ray->draw_end:
	  //        • Put a wall color. (E.g., 0xFF0000 if side == 0, 
		//        and a darker 0x880000 if side == 1 to create shading!).
	  //    • If y > ray->draw_end: put game->map.floor_color.
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
// Resume with -c (or command below):
// agy --conversation=064daf8d-9a8a-4ab2-a385-5fb6bb2240
