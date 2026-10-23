/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/9 22:30:00 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/22 22:22:26 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	check_cub_extension(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (0);
	if (path[len - 5] == '/')
		return (0);
	return (1);
}

int	open_cub_file(char *path)
{
	int	fd;

	if (!check_cub_extension(path))
	{
		error_msg("Invalid file extension (must be .cub)\n");
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error_msg("Could not open file\n");
		return (-1);
	}
	return (fd);
}

static int	append_line(t_list **list, char *line)
{
	char	*dup;
	t_list	*node;

	dup = ft_strdup(line);
	if (!dup)
		return (0);
	node = ft_lstnew(dup);
	if (!node)
	{
		free(dup);
		return (0);
	}
	ft_lstadd_back(list, node);
	return (1);
}

static int	classify_line(char *line, int *in_map, t_list **cfg, t_list **map)
{
	if (!*in_map && is_config_identifier(line))
		return (append_line(cfg, line));
	*in_map = 1;
	return (append_line(map, line));
}

int	split_lines(t_list *raw, t_list **configs, t_list **map)
{
	int		in_map;
	int		map_ended;
	char	*line;

	in_map = 0;
	map_ended = 0;
	while (raw)
	{
		line = (char *)raw->content;
		if (in_map && is_empty_line(line))
			map_ended = 1;
		else if (map_ended && !is_empty_line(line))
			return (error_msg("Invalid line inside or after map\n"), 0);
		else if (!is_empty_line(line)
			&& !classify_line(line, &in_map, configs, map))
			return (0);
		raw = raw->next;
	}
	if (!*configs || !*map)
		return (error_msg("Missing configuration or map content\n"), 0);
	return (1);
}
