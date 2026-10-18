/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 15:20:00 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/18 17:45:00 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static char	*clean_map_line(char *raw_line)
{
	int		len;
	char	*clean;

	if (!raw_line)
		return (NULL);
	len = ft_strlen(raw_line);
	while (len > 0 && (raw_line[len - 1] == '\n' || raw_line[len - 1] == '\r'))
		len--;
	clean = ft_substr(raw_line, 0, len);
	return (clean);
}

static int	build_map_grid(t_map *map, t_list *map_lines)
{
	int	i;
	int	len;

	map->height = ft_lstsize(map_lines);
	map->grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (0);
	i = 0;
	while (map_lines)
	{
		map->grid[i] = clean_map_line((char *)map_lines->content);
		if (!map->grid[i])
			return (0);
		len = (int)ft_strlen(map->grid[i]);
		if (len > map->width)
			map->width = len;
		i++;
		map_lines = map_lines->next;
	}
	return (1);
}

static void	set_player_orientation(t_player *player, char c)
{
	if (c == 'N' || c == 'S')
	{
		player->dir_x = 0.0;
		player->plane_y = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		if (c == 'N')
		{
			player->dir_y = -1.0;
			player->plane_x = 0.66;
		}
	}
	else if (c == 'E' || c == 'W')
	{
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->dir_x = 1.0;
		player->plane_y = 0.66;
		if (c == 'W')
		{
			player->dir_x = -1.0;
			player->plane_y = -0.66;
		}
	}
}

static int	check_tile(t_game *game, int x, int y, int *count)
{
	char	c;

	c = game->map.grid[y][x];
	if (c != '0' && c != '1' && c != ' ' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
		return (error_msg("Invalid character in map grid\n"), 0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*count > 0)
			return (error_msg("Multiple player positions in map\n"), 0);
		(*count)++;
		game->player.pos_x = (double)x + 0.5;
		game->player.pos_y = (double)y + 0.5;
		set_player_orientation(&game->player, c);
		game->map.grid[y][x] = '0';
	}
	return (1);
}

int	parse_map_grid(t_game *game, t_list *map_lines)
{
	int	x;
	int	y;
	int	count;

	if (!build_map_grid(&game->map, map_lines))
		return (0);
	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (!check_tile(game, x, y, &count))
				return (0);
			x++;
		}
		y++;
	}
	if (count == 0)
		return (error_msg("No player found on map\n"), 0);
	return (1);
}
