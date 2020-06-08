/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:09:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/08 15:23:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int					scene_render_params(t_app *app, t_window *window)
{
	window->pixel_bits = 32;
	window->line_bytes = window->screen_width * 4;
	window->pixel_endian = TRUE;
	window->redraw = TRUE;
	window->ui_color = UI_COLOR;
	if (!(window->cell =
		mlx_new_image(app->mlx, app->cell_size,  app->cell_size)) ||
		!(window->cell_buf =
		mlx_get_data_addr(window->cell,
			&window->pixel_bits, &window->line_bytes, &window->pixel_endian)))
		return (FALSE);
	if (!(window->frame =
		mlx_new_image(app->mlx, window->screen_width, window->screen_height)) ||
		!(window->frame_buf =
		mlx_get_data_addr(window->frame,
			&window->pixel_bits, &window->line_bytes, &window->pixel_endian)))
		return (FALSE);
	return (TRUE);
}

t_window					*new_window(t_app *app)
{
	t_window		*window;

	if (!(window = (t_window*)malloc(sizeof(*window))))
		return (NULL);
	window->screen_width = WIDTH;
	window->screen_height = HEIGHT;
	if (!(window->mlx_wdw = mlx_new_window(app->mlx, window->screen_width,
			window->screen_height, "Filler")) ||
			!scene_render_params(app, window))
		return (NULL);
	return (window);
}
