/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyun <cyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:27:57 by cyun              #+#    #+#             */
/*   Updated: 2023/01/09 14:30:25 by cyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

// mlx를 init
void	init_minilibx(t_game *game)
{
	int	w;
	int	h;

	w = game->width;
	h = game->height;
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, w * TILES, \
	h * TILES, "[so_long]");
}

// game 구조체를 초기화
void	init_param(t_game *game)
{
	game->width = 0;
	game->height = 0;
	game->map_textures.wall = 0;
	game->map_textures.player = 0;
	game->map_textures.collectible = 0;
	game->map_textures.exit = 0;
	game->collected = 0;
	game->move = 0;
	game->map = NULL;
	game->position.x = 0;
	game->position.y = 0;
	game->valid_path = 0;
}

void	get_map_col(t_game *game, char *line, int l)
{
	int		i;

	i = 0;
	game->map[l] = (char *)malloc(sizeof(char) * game->width);
	while (line[i])
	{
		if (line[i] == 'P')
		{
			game->position.x = i;
			game->position.y = l;
		}
		game->map[l][i] = line[i];
		i++;
	}
}

// map의 마지막 줄을 체크
int	check_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
		{
			close_game_with_error(4);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_map(t_game *game, int fd)
{
	int		i;
	int		is_valid;
	char	*line;

	i = 0;
	is_valid = 1;
	game->map = (char **)malloc(sizeof(char *) * game->height);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		get_map_col(game, line, i);
		if (i + 1 == game->height)
			is_valid = check_last_line(line);
		if (!is_valid)
			close_game(game, 0);
		draw_map(game, line, i);
		free(line);
		i++;
	}
	check_path(game);
	ft_putstr_fd("------------------\n", 1);
	ft_putstr_fd("   Game start !   \n", 1);
	ft_putstr_fd("------------------\n", 1);
}
