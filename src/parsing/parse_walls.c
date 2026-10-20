/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 14:10:00 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/20 16:30:00 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static char	**allocate_padded_grid(t_map *map)
{
	char	**padded;
	int		y;

	padded = ft_calloc(map->height + 3, sizeof(char *));
	if (!padded)
		return (NULL);
	y = 0;
	while (y < map->height + 2)
	{
		padded[y] = ft_calloc(map->width + 3, sizeof(char));
		if (!padded[y])
		{
			free_array(padded);
			return (NULL);
		}
		ft_memset(padded[y], ' ', map->width + 2);
		y++;
	}
	return (padded);
}

static void	fill_padded_grid(t_map *map, char **padded)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			padded[y + 1][x + 1] = map->grid[y][x];
			x++;
		}
		y++;
	}
}

static int	is_surrounded(char **padded, int x, int y)
{
	if (padded[y - 1][x] == ' ' || padded[y + 1][x] == ' '
		|| padded[y][x - 1] == ' ' || padded[y][x + 1] == ' '
		|| padded[y - 1][x - 1] == ' ' || padded[y - 1][x + 1] == ' '
		|| padded[y + 1][x - 1] == ' ' || padded[y + 1][x + 1] == ' ')
		return (0);
	return (1);
}

static int	validate_enclosure(char **padded, int height)
{
	int	x;
	int	y;

	y = 1;
	while (y <= height)
	{
		x = 1;
		while (padded[y][x])
		{
			if (padded[y][x] == '0')
			{
				if (!is_surrounded(padded, x, y))
					return (error_msg("Map is not enclosed by walls\n"), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_enclosed(t_map *map)
{
	char	**padded;

	padded = allocate_padded_grid(map);
	if (!padded)
		return (0);
	fill_padded_grid(map, padded);
	if (!validate_enclosure(padded, map->height))
	{
		free_array(padded);
		return (0);
	}
	free_array(padded);
	return (1);
}
