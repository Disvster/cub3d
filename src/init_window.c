/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafarsha <mafarsha@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:50:25 by manmaria          #+#    #+#             */
/*   Updated: 2026/10/08 19:40:00 by mafarsha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	return (1);
}

int	clean_exit(t_game *game)
{
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game);
	return (0);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		error_msg("Could not initialize MLX\n");
		exit(1);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
		clean_exit(game);
	game->frame.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->frame.img)
		clean_exit(game);
	game->frame.addr = mlx_get_data_addr(game->frame.img,
			&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		clean_exit(game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		error_msg("Usage: ./cub3d <map.cub>\n");
		return (1);
	}
	(void)av;
	ft_bzero(&game, sizeof(t_game));
	init_window(&game);
	mlx_hook(game.win, ON_DESTROY, 0, clean_exit, &game);
	mlx_hook(game.win, ON_KEYDOWN, 1L << 0, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
