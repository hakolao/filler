/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:35:03 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/08 16:42:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			draw_grid(t_app *app)
{
	int		y;
	int		x;
	int		cols;
	int		rows;
	t_rect	cell_bounds;

	if (app->cols <= 0 || app->rows <= 0 ||
		app->grid_bounds.y <= 0 || app->grid_bounds.x <= 0)
		return (void)(log_err("Invalid grid draw input", strerror(5)));
	y = app->grid_bounds.y;
	rows = app->rows;
	while (y < app->grid_bounds.y + app->grid_bounds.h - app->cell_size &&
		y >=0 && y < app->window->screen_height && rows-- > 0)
	{
		x = app->grid_bounds.x;
		cols = app->cols + 1;
		while (x < app->grid_bounds.x + app->grid_bounds.w - app->cell_size &&
			x >=0 && x < app->window->screen_width && --cols > 0)
		{
			cell_bounds = (t_rect){.w = app->cell_size, .h = app->cell_size,
				.x = x + 1, .y = y + 1};
			draw_rectangle(app, &cell_bounds, COLOR(100, 100, 100, 0));
			x += cell_bounds.w + 1;
		}
		y += cell_bounds.h + 1;
	}
}

static void				draw_player_cached_cell(t_app *app, int player_i)
{
	int		color;
	int		x;
	int		y;
	t_rect	cell_bounds;

	x = app->info_bounds.x + 10;
	y = app->info_bounds.y + 50 + player_i * (app->cell_size + 1);
	if (player_i == 0)
		color = COLOR(255, 0, 0, 0);
	else
		color = COLOR(0, 255, 0, 0);
	cell_bounds = (t_rect){.w = app->cell_size, .h = app->cell_size,
		.x = x, .y = y};
	draw_pyramid_shape(app, &cell_bounds, color);
}

void				draw_game(t_app *app)
{
	int		i;
	
	draw_grid(app);
	i = 0;
	while (i < app->num_players)
	{
		draw_player_cached_cell(app, i);
		i++;
	}
}