/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 14:15:20 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/15 17:30:10 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	validate_texture_path(char *path)
{
	int		fd;
	size_t	len;

	len = ft_strlen(path);
	if (len < 5)
		return (error_msg("Invalid texture path length\n"), 0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (error_msg("Texture must have .xpm extension\n"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Cannot open texture file\n"), 0);
	close(fd);
	return (1);
}

static int	set_texture(char **target, char *line, int offset)
{
	char	*path;

	if (*target != NULL)
		return (error_msg("Duplicate texture definition\n"), 0);
	path = ft_strtrim(line + offset, " \t\r\n\v\f");
	if (!path || !*path)
	{
		if (path)
			free(path);
		return (error_msg("Empty texture path\n"), 0);
	}
	if (!validate_texture_path(path))
	{
		free(path);
		return (0);
	}
	*target = path;
	return (1);
}

int	parse_texture_line(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (!ft_strncmp(line + i, "NO", 2) && ft_isspace(line[i + 2]))
		return (set_texture(&map->no_path, line + i, 2));
	if (!ft_strncmp(line + i, "SO", 2) && ft_isspace(line[i + 2]))
		return (set_texture(&map->so_path, line + i, 2));
	if (!ft_strncmp(line + i, "WE", 2) && ft_isspace(line[i + 2]))
		return (set_texture(&map->we_path, line + i, 2));
	if (!ft_strncmp(line + i, "EA", 2) && ft_isspace(line[i + 2]))
		return (set_texture(&map->ea_path, line + i, 2));
	return (-1);
}

int	check_textures_complete(t_map *map)
{
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path)
		return (error_msg("Missing one or more texture paths\n"), 0);
	return (1);
}
