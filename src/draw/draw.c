/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 17:24:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			draw_frame(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->window->mlx_wdw,
	app->window->frame, 0, 0);
}

static void			clear_frame(t_app *app)
{
	draw_rectangle(app,
		&(t_rect){.w = app->window->screen_width,
			.h = app->window->screen_height, .x = 0, .y = 0},
		app->window->bg_color);
}

static void			finish_colors(t_app *app)
{
	int		pixel;
	int		y;
	int		x;

	y = 0;
	while (y < app->window->screen_height)
	{
		x = 0;
		while (x < app->window->screen_width)
		{
			pixel = y * app->window->line_bytes + x * 4;
			app->window->frame_buf[pixel] =
				app->window->frame_buf[pixel] * 5 / 3 % 255;
			app->window->frame_buf[pixel + 1] =
				app->window->frame_buf[pixel + 1] * 5 / 3 % 255;
			app->window->frame_buf[pixel + 2] =
				app->window->frame_buf[pixel + 2] * 5 / 3 % 255;
			app->window->frame_buf[pixel + 3] = 0;
			x++;
		}
		y++;
	}
}

int					draw(t_app *app)
{
	mlx_clear_window(app->mlx, app->window->mlx_wdw);
	clear_frame(app);
	draw_info_panel(app);
	if (app->board != NULL)
		draw_game(app);
	if (app->is_finished)
		finish_colors(app);
	draw_frame(app);
	draw_texts(app);
	app->window->redraw = FALSE;
	return (1);
}
