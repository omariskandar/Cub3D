/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tex_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 10:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_door_texture(t_game *g, t_texture *t)
{
	if (t == &g->door_tex)
		return (1);
	return (0);
}

int			compute_tex_y(t_game *g, t_ray *r, t_texture *t, int y)
{
	double		step;
	double		pos;
	double		start_unclipped;
	int			line_h;
	int			tex_y;

	line_h = r->line_height;
	if (line_h < 1)
		line_h = 1;
	step = (double)t->height / (double)line_h;
	start_unclipped = (double)g->mlx.current_height * 0.5
		- (double)line_h * 0.5 + (double)g->pitch;
	pos = ((double)y + 0.5 - start_unclipped) * step;
	if (pos < 0.0)
		pos = 0.0;
	tex_y = (int)pos;
	if (tex_y >= t->height)
		tex_y = t->height - 1;
	return (tex_y);
}

int			sample_wall_color(t_game *g, t_ray *r, t_texture *t, int tex_y)
{
	if (is_door_texture(g, t))
		return (sample_door_color(g, r, t, tex_y));
	return (get_texture_color(t, r->tex_x, tex_y));
}
