/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:09:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/05 00:29:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int					scene_render_params(t_window *window,
							void *mlx, void *mlx_wdw)
{
	window->mlx = mlx;
	window->mlx_wdw = mlx_wdw;
	window->pixel_bits = 32;
	window->line_bytes = window->screen_width * 4;
	window->pixel_endian = TRUE;
	window->redraw = TRUE;
	window->ui_color = UI_COLOR;
	if (!(window->frame =
		mlx_new_image(mlx, window->screen_width, window->screen_height)) ||
		!(window->frame_buf =
		mlx_get_data_addr(window->frame,
			&window->pixel_bits, &window->line_bytes, &window->pixel_endian)))
		return (FALSE);
	return (TRUE);
}

t_window					*new_window(void *mlx)
{
	t_window		*window;

	if (!(window = (t_window*)malloc(sizeof(*window))))
		return (NULL);
	window->screen_width = WIDTH;
	window->screen_height = HEIGHT;
	if (!(window->mlx_wdw = mlx_new_window(mlx, window->screen_width,
			window->screen_height, "Filler")) ||
			!scene_render_params(window, mlx, window->mlx_wdw))
		return (NULL);
	window->mlx = mlx;
	return (window);
}
