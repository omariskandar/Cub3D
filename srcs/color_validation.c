/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_color_format(char *color_str)
{
	int	i;
	int	comma_count;

	if (!color_str)
		return (0);
	i = 0;
	comma_count = 0;
	while (color_str[i])
	{
		if (color_str[i] == ',')
			comma_count++;
		else if (color_str[i] < '0' || color_str[i] > '9')
			return (0);
		i++;
	}
	return (comma_count == 2);
}

static int	validate_color_range(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (0);
	if (g < 0 || g > 255)
		return (0);
	if (b < 0 || b > 255)
		return (0);
	return (1);
}

int	validate_color(char *color_str, char *color_name)
{
	int		r;
	int		g;
	int		b;
	char	**colors;

	(void)color_name;
	if (!validate_color_format(color_str))
		return (exit_error("Error: Invalid color format"));
	colors = ft_split(color_str, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		if (colors)
			free(colors);
		return (exit_error("Error: Invalid color format"));
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	if (!validate_color_range(r, g, b))
		return (exit_error("Error: Color values must be between 0 and 255"));
	return ((r << 16) | (g << 8) | b);
}
