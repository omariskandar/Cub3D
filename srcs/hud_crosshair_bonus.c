/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_crosshair_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:20:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/10 13:20:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_crosshair_dot(t_game *game)
{
	int		cx;
	int		cy;
	int		key;
	int		i;

	if (!game->dot_tex.img)
		return ;
	cx = game->mlx.current_width / 2 - 52 / 2;
	cy = game->mlx.current_height / 2 - 52 / 2;
	key = get_texture_color(&game->dot_tex, 0, 0);
	i = 0;
	while (i < 52 * 52)
	{
		if (get_texture_color(&game->dot_tex,
				(i % 52) * game->dot_tex.width / 52,
				(i / 52) * game->dot_tex.height / 52) != key)
			put_pixel(game, cx + (i % 52), cy + (i / 52),
				get_texture_color(&game->dot_tex,
					(i % 52) * game->dot_tex.width / 52,
					(i / 52) * game->dot_tex.height / 52));
		i++;
	}
}
