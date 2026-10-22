/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/9 22:35:00 by mafarsha          #+#    #+#             */
/*   Updated: 2026/10/22 22:22:26 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d.h"

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
	if (fd < 0)
		return (0);
	if (!read_raw_lines(fd, &raw))
		return (0);
	if (!split_lines(raw, &configs, &map_lines))
	{
		ft_lstclear(&raw, free);
		ft_lstclear(&configs, free);
		ft_lstclear(&map_lines, free);
		return (0);
	}
	ft_lstclear(&raw, free);
	ft_lstclear(&configs, free);
	ft_lstclear(&map_lines, free);
	(void)game;
	return (1);
}
