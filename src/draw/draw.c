/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/12 15:49:06 by ohakola          ###   ########.fr       */
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

static void			draw_finish(t_app *app)
{
	(void)app;
	return ;
}

int					draw(t_app *app)
{
	mlx_clear_window(app->mlx, app->window->mlx_wdw);
	clear_frame(app);
	draw_info_panel(app);
	if (app->board != NULL)
	{
		if (!app->is_finished)
			draw_game(app);
		else
			draw_finish(app);
	}
	draw_frame(app);
	draw_texts(app);
	if (app->board != NULL)
		draw_scores(app);
	app->window->redraw = FALSE;
	return (1);
}
