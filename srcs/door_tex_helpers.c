/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_tex_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 22:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 22:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	adjust_tex_x_by_ray(t_ray *r, int base_x, int off)
{
	int	tex_x;

	tex_x = base_x;
	if (r->side == 0)
	{
		if (r->dir.x > 0)
			tex_x += off;
		else
			tex_x -= off;
	}
	else
	{
		if (r->dir.y > 0)
			tex_x += off;
		else
			tex_x -= off;
	}
	return (tex_x);
}

int	sample_door_color(t_game *g, t_ray *r, t_texture *t, int tex_y)
{
	int	tex_x;
	int	off;

	if (g->door_prog == NULL || g->door_mask == NULL)
		return (get_texture_color(t, r->tex_x, tex_y));
	off = (int)(g->door_prog[(int)r->map.y][(int)r->map.x] * t->width);
	tex_x = adjust_tex_x_by_ray(r, r->tex_x, off);
	if (tex_x < 0 || tex_x >= t->width)
		return (-1);
	return (get_texture_color(t, tex_x, tex_y));
}
