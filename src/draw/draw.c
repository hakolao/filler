/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:03:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/05 14:45:59 by ohakola          ###   ########.fr       */
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
	draw_rectangle(app,
		&(t_rect){.w = app->window->screen_width,
			.h = app->window->screen_height, .x = 0, .y = 0},
		app->window->bg_color);
}

int					draw(t_app *app)
{
	mlx_clear_window(app->window->mlx, app->window->mlx_wdw);
	clear_frame(app);
	// Draw here
	draw_grid(app,
		&(t_rect){
			.w = app->window->screen_width * 3 / 4,
			.h = app->window->screen_height * 3 / 4,
			.x = 100,
			.y = 100},
		100, 100
	);
	//
	draw_frame(app);
	draw_ui(app);
	app->window->redraw = FALSE;
	return (1);
}
