/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_anim_bonus.c                                  :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani                           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 10:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

double	now_seconds(void)
{
	struct timeval	v;

	gettimeofday(&v, NULL);
	return ((double)v.tv_sec + (double)v.tv_usec / 1e6);
}

int	init_doors_anim(t_game *game)
{
	alloc_door_arrays(game);
	init_door_rows(game);
	game->door_last_ts = now_seconds();
	return (0);
}

static void	update_row(t_game *g, int y, double dt)
{
	int	x;

	x = 0;
	while (x < (int)ft_strlen(g->map.grid[y]))
	{
		process_cell(g, x, y, dt);
		x++;
	}
}

void	update_doors(t_game *game)
{
	double	now;
	double	dt;
	int		y;

	now = now_seconds();
	dt = now - game->door_last_ts;
	if (dt > DOOR_DT_CAP)
		dt = DOOR_DT_CAP;
	game->door_last_ts = now;
	if (now - game->door_last_interact > DOOR_CLOSE_DELAY)
		update_auto_close_targets(game);
	y = 0;
	while (game->map.grid[y])
	{
		update_row(game, y, dt);
		y++;
	}
}
