/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_anim_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 22:10:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 22:10:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	alloc_door_arrays(t_game *g)
{
	int		h;
	int		w;
	int		y;

	h = g->map.height;
	g->door_prog = (double **)malloc(sizeof(double *) * h);
	g->door_target = (char **)malloc(sizeof(char *) * h);
	g->door_mask = (char **)malloc(sizeof(char *) * h);
	y = 0;
	while (y < h)
	{
		w = (int)ft_strlen(g->map.grid[y]);
		g->door_prog[y] = (double *)malloc(sizeof(double) * w);
		g->door_target[y] = (char *)malloc(sizeof(char) * w);
		g->door_mask[y] = (char *)malloc(sizeof(char) * w);
		y++;
	}
}

void	init_door_rows(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (x < (int)ft_strlen(g->map.grid[y]))
		{
			g->door_mask[y][x] = (g->map.grid[y][x] == 'D'
					|| g->map.grid[y][x] == 'O');
			g->door_prog[y][x] = (g->map.grid[y][x] == 'O');
			g->door_target[y][x] = (g->map.grid[y][x] == 'O');
			x++;
		}
		y++;
	}
}

void	update_door_cell(t_game *g, int x, int y, double dt)
{
	double	p;
	int		t;
	double	s;

	p = g->door_prog[y][x];
	t = g->door_target[y][x];
	if (t)
		s = DOOR_SPEED_OPEN;
	else
		s = DOOR_SPEED_CLOSE;
	if (t && p < 1.0)
		p += s * dt;
	else if (!t && p > 0.0)
		p -= s * dt;
	if (p > 1.0)
		p = 1.0;
	if (p < 0.0)
		p = 0.0;
	g->door_prog[y][x] = p;
	if (p >= 1.0)
		g->map.grid[y][x] = 'O';
	else if (p <= 0.0)
		g->map.grid[y][x] = 'D';
}

void	process_cell(t_game *g, int x, int y, double dt)
{
	int	px;
	int	py;

	if (!g->door_mask[y][x])
		return ;
	px = (int)(g->player.pos.x / MAP_SCALE);
	py = (int)(g->player.pos.y / MAP_SCALE);
	if (px == x && py == y)
	{
		g->door_target[y][x] = 1;
		g->door_prog[y][x] = 1.0;
		g->map.grid[y][x] = 'O';
		return ;
	}
	update_door_cell(g, x, y, dt);
}
