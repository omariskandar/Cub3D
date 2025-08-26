/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap_border_pixel(t_game *game, int x, int y, int center_x)
{
	int	center_y;

	center_y = game->mlx.current_height - MINIMAP_RADIUS - MINIMAP_MARGIN;
	if (is_in_minimap_circle(x - center_x, y - center_y, MINIMAP_RADIUS + 3))
	{
		if (is_in_minimap_circle(x - center_x, y - center_y, MINIMAP_RADIUS))
			put_pixel(game, x, y, MINIMAP_BG);
		else
			put_pixel(game, x, y, MINIMAP_BORDER);
	}
}
