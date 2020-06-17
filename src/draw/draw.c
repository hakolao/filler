/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/17 15:17:06 by ohakola          ###   ########.fr       */
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

static void			apply_pastel(t_app *app)
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
				app->window->frame_buf[pixel] * 3 / 4;
			app->window->frame_buf[pixel + 1] =
				app->window->frame_buf[pixel + 1] * 3 / 4;
			app->window->frame_buf[pixel + 2] =
				app->window->frame_buf[pixel + 2] * 3 / 4;
			app->window->frame_buf[pixel + 3] = 0;
			x++;
		}
		y++;
	}
}

static void			draw_finish_panel(t_app *app)
{
	int	width;
	int	height;

	width = 400;
	height = 200;
	draw_rectangle(app, &(t_rect){
		.x = app->window->screen_width / 2 - width / 2 + 10,
		.y = app->window->screen_height / 2 - height / 2 + 10,
		.w = width,
		.h = height
	}, COLOR(0, 0, 0, 0));
	draw_rectangle(app, &(t_rect){
		.x = app->window->screen_width / 2 - width / 2,
		.y = app->window->screen_height / 2 - height / 2,
		.w = width,
		.h = height
	}, COLOR(150, 150, 255, 0));
}

int					draw(t_app *app)
{
	mlx_clear_window(app->mlx, app->window->mlx_wdw);
	clear_frame(app);
	draw_rectangle(app, &app->info_bounds, COLOR(150, 150, 255, 0));
	if (app->board != NULL)
		draw_game(app);
	if (app->board != NULL)
		draw_scores(app);
	if (app->is_finished)
		draw_finish_panel(app);
	if (app->board)
		apply_pastel(app);
	draw_frame(app);
	if (app->is_finished)
		draw_finish_text(app);
	return (1);
}
