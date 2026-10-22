/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/9 22:25:00 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/22 22:22:26 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

int	is_config_identifier(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (!ft_strncmp(line + i, "NO", 2) && ft_isspace(line[i + 2]))
		return (1);
	if (!ft_strncmp(line + i, "SO", 2) && ft_isspace(line[i + 2]))
		return (1);
	if (!ft_strncmp(line + i, "WE", 2) && ft_isspace(line[i + 2]))
		return (1);
	if (!ft_strncmp(line + i, "EA", 2) && ft_isspace(line[i + 2]))
		return (1);
	if (!ft_strncmp(line + i, "F", 1) && ft_isspace(line[i + 1]))
		return (1);
	if (!ft_strncmp(line + i, "C", 1) && ft_isspace(line[i + 1]))
		return (1);
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map_data(t_map *map)
{
	if (!map)
		return ;
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->grid)
		free_array(map->grid);
	ft_bzero(map, sizeof(t_map));
}

int	is_map_line(char *line)
{
	int	i;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}
