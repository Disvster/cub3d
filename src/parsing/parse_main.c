/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 17:10:00 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/20 17:15:00 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	read_raw_lines(int fd, t_list **raw)
{
	char	*line;
	t_list	*node;

	line = get_next_line(fd);
	while (line)
	{
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			ft_lstclear(raw, free);
			close(fd);
			return (0);
		}
		ft_lstadd_back(raw, node);
		line = get_next_line(fd);
	}
	close(fd);
	if (!*raw)
		return (error_msg("Map file is empty\n"), 0);
	return (1);
}

static void	free_lists(t_list **raw, t_list **cfg, t_list **map)
{
	if (raw && *raw)
		ft_lstclear(raw, free);
	if (cfg && *cfg)
		ft_lstclear(cfg, free);
	if (map && *map)
		ft_lstclear(map, free);
}

static int	parse_all_configs(t_map *map, t_list *configs)
{
	char	*line;
	int		res;

	map->floor_color = -1;
	map->ceiling_color = -1;
	while (configs)
	{
		line = (char *)configs->content;
		res = parse_texture_line(map, line);
		if (res == 0)
			return (0);
		if (res == -1)
		{
			res = parse_color_line(map, line);
			if (res == 0)
				return (0);
			if (res == -1)
				return (error_msg("Unknown configuration element\n"), 0);
		}
		configs = configs->next;
	}
	if (!check_textures_complete(map) || !check_colors_complete(map))
		return (0);
	return (1);
}

int	parse_cub(t_game *game, char *path)
{
	int		fd;
	t_list	*raw;
	t_list	*configs;
	t_list	*map_lines;

	raw = NULL;
	configs = NULL;
	map_lines = NULL;
	fd = open_cub_file(path);
	if (fd < 0 || !read_raw_lines(fd, &raw))
		return (0);
	if (!split_lines(raw, &configs, &map_lines)
		|| !parse_all_configs(&game->map, configs)
		|| !parse_map_grid(game, map_lines)
		|| !check_map_enclosed(&game->map))
	{
		free_lists(&raw, &configs, &map_lines);
		free_map_data(&game->map);
		return (0);
	}
	free_lists(&raw, &configs, &map_lines);
	return (1);
}
