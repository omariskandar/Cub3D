/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_texture_path(char *line, char *prefix, char **texture_ptr)
{
	char	*texture_path;

	texture_path = trim_spaces(line + ft_strlen(prefix));
	*texture_ptr = texture_path;
}

void	handle_color(char *line, char *prefix, int *color_ptr)
{
	char	*color_str;

	color_str = trim_spaces(line + ft_strlen(prefix));
	*color_ptr = validate_color(color_str, prefix);
}

void	free_textures(t_game *game)
{
	if (game->map.north_texture)
		free(game->map.north_texture);
	if (game->map.south_texture)
		free(game->map.south_texture);
	if (game->map.west_texture)
		free(game->map.west_texture);
	if (game->map.east_texture)
		free(game->map.east_texture);
}
