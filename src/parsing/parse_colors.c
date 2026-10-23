/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:30:10 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/23 12:08:04 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

static int	validate_rgb_syntax(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == ',')
		return (error_msg("Leading comma in color definition\n"), 0);
	while (str[i])
	{
		if (str[i] == ',')
		{
			commas++;
			if (str[i + 1] == ',')
				return (error_msg("Consecutive commas in color\n"), 0);
		}
		else if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (error_msg("Invalid character in color definition\n"), 0);
		i++;
	}
	if (commas != 2)
		return (error_msg("Color must contain exactly 2 commas\n"), 0);
	return (1);
}

static int	parse_single_component(char *str, int *val)
{
	char	*trimmed;
	int		i;
	long	num;

	trimmed = ft_strtrim(str, " \t\r\n\v\f");
	if (!trimmed || !*trimmed)
	{
		if (trimmed)
			free(trimmed);
		return (error_msg("Empty color component\n"), 0);
	}
	i = 0;
	while (trimmed[i])
	{
		if (!ft_isdigit(trimmed[i]))
			return (free(trimmed), error_msg("Non-digit in color\n"), 0);
		i++;
	}
	num = ft_atol(trimmed);
	free(trimmed);
	if (num < 0 || num > 255)
		return (error_msg("Color component out of range (0-255)\n"), 0);
	*val = (int)num;
	return (1);
}

static int	convert_rgb_to_hex(char *line, int *color)
{
	char	**split;
	int		rgb[3];

	if (!validate_rgb_syntax(line))
		return (0);
	split = ft_split(line, ',');
	if (!split)
		return (0);
	if (!split[0] || !split[1] || !split[2] || split[3])
	{
		free_array(split);
		return (error_msg("RGB must have exactly 3 values\n"), 0);
	}
	if (!parse_single_component(split[0], &rgb[0])
		|| !parse_single_component(split[1], &rgb[1])
		|| !parse_single_component(split[2], &rgb[2]))
	{
		free_array(split);
		return (0);
	}
	free_array(split);
	*color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

int	parse_color_line(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == 'F' && ft_isspace(line[i + 1]))
	{
		if (map->floor_color != -1)
			return (error_msg("Duplicate floor color\n"), 0);
		return (convert_rgb_to_hex(line + i + 1, &map->floor_color));
	}
	if (line[i] == 'C' && ft_isspace(line[i + 1]))
	{
		if (map->ceiling_color != -1)
			return (error_msg("Duplicate ceiling color\n"), 0);
		return (convert_rgb_to_hex(line + i + 1, &map->ceiling_color));
	}
	return (-1);
}

int	check_colors_complete(t_map *map)
{
	if (map->floor_color == -1 || map->ceiling_color == -1)
		return (error_msg("Missing floor or ceiling color\n"), 0);
	return (1);
}
