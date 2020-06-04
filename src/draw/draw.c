/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 23:00:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			draw_frame(t_app *app)
{
	mlx_put_image_to_window(app->window->mlx, app->window->mlx_wdw,
	app->window->frame, 0, 0);
}

static void			clear_frame(t_app *app)
{
	int		x;
	int		y;
	int		pixel;
	int		color;

	color = app->window->bg_color;
	y = 0;
	while (y < app->window->screen_height)
	{
		x = 0;
		while (x <  app->window->screen_width)
		{
			pixel = y * app->window->line_bytes + x * 4;
			app->window->frame_buf[pixel] = BLUE(color);
			app->window->frame_buf[pixel + 1] = GREEN(color);
			app->window->frame_buf[pixel + 2] = RED(color);
			app->window->frame_buf[pixel + 3] = ALPHA(color);
			x++;
		}
		y++;
	}
}

int					draw(t_app *app)
{
	mlx_clear_window(app->window->mlx, app->window->mlx_wdw);
	clear_frame(app);
	// Draw here
	//
	draw_frame(app);
	draw_ui(app);
	app->window->redraw = FALSE;
	return (1);
}
