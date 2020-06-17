/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:35:03 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/17 15:46:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			set_frame_pixel_from_cache(t_app *app,
					int pixel, int cache_pixel)
{
	app->window->frame_buf[pixel] = app->window->frame_buf[cache_pixel];
	app->window->frame_buf[pixel + 1] =
		app->window->frame_buf[cache_pixel + 1];
	app->window->frame_buf[pixel + 2] =
		app->window->frame_buf[cache_pixel + 2];
	app->window->frame_buf[pixel + 3] =
		app->window->frame_buf[cache_pixel + 3];
}

static void			draw_player_cell(t_app *app,
					t_rect *cell_bounds, int id)
{
	int		y;
	int		x;
	int		cache_x;
	int		cache_y;

	y = cell_bounds->y;
	cache_y = id == PLAYER_1 ? app->player_1_cell_y : app->player_2_cell_y;
	while (y < cell_bounds->y + cell_bounds->h &&
			y >= 0 && y < app->window->screen_height)
	{
		x = cell_bounds->x;
		cache_x = app->info_bounds.x + 10;
		while (x < cell_bounds->x + cell_bounds->w &&
				x >= 0 && x < app->window->screen_width)
		{
			set_frame_pixel_from_cache(app,
				y * app->window->line_bytes + x * 4,
				cache_y * app->window->line_bytes + cache_x * 4);
			x++;
			cache_x++;
		}
		y++;
		cache_y++;
	}
}

static void			draw_cells(t_app *app)
{
	int		x;
	int		y;
	t_rect	cell_bounds;

	y = -1;
	cell_bounds.y = app->grid_bounds.y;
	while (++y < app->board->height)
	{
		x = -1;
		cell_bounds.x = app->grid_bounds.x - app->cell_size;
		while (++x < app->board->width)
		{
			cell_bounds = (t_rect){.w = app->cell_size, .h = app->cell_size,
				.x = cell_bounds.x + app->cell_size + 1, .y = cell_bounds.y};
			if (app->board->cells[y][x].id == EMPTY)
				draw_rectangle(app, &cell_bounds,
					app->board->cells[y][x].color);
			else
				draw_player_cell(app, &cell_bounds, app->board->cells[y][x].id);
		}
		cell_bounds.y += app->cell_size + 1;
	}
}

/*
** Draw cache cells of pyramid shapes (triangle calculation is heavy so
** we want to rather copy the pixels to the game board)
*/

static void			draw_player_cached_cell(t_app *app, int player_i)
{
	int		color;
	int		x;
	int		y;
	t_rect	cell_bounds;

	x = app->info_bounds.x + 10;
	if (player_i == 0)
	{
		color = app->player1_color;
		y = app->player_1_cell_y;
	}
	else
	{
		color = app->player2_color;
		y = app->player_2_cell_y;
	}
	cell_bounds = (t_rect){.w = app->cell_size, .h = app->cell_size,
		.x = x, .y = y};
	draw_pyramid_shape(app, &cell_bounds, color);
}

void				draw_game(t_app *app)
{
	int		i;

	if (app->board == NULL)
		return ;
	i = 0;
	while (i < 2)
	{
		draw_player_cached_cell(app, i);
		i++;
	}
	draw_cells(app);
}
