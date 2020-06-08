/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:35:03 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/08 15:14:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		draw_rect_or_game_piece(t_app *app, t_rect *cell)
{
	draw_rectangle(app, cell, COLOR(100, 100, 100, 0));
}

void			draw_grid(t_app *app)
{
	int		y;
	int		x;
	int		c;
	t_rect	cell;

	if (app->cols <= 0 || app->rows <= 0 ||
		app->grid_bounds.y <= 0 || app->grid_bounds.x <= 0)
		return (void)(log_err("Invalid grid draw input", strerror(5)));
	y = app->grid_bounds.y;
	while (y < app->grid_bounds.y + app->grid_bounds.h - app->cell_size &&
		y >=0 && y < app->window->screen_height && app->rows-- > 0)
	{
		x = app->grid_bounds.x;
		c = app->cols + 1;
		while (x < app->grid_bounds.x + app->grid_bounds.w - app->cell_size &&
			x >=0 && x < app->window->screen_width && --c > 0)
		{
			cell = (t_rect){.w = app->cell_size, .h = app->cell_size,
				.x = x + 1, .y = y + 1};
			draw_rect_or_game_piece(app, &cell);
			x += cell.w + 1;
		}
		y += cell.h + 1;
	}
}
