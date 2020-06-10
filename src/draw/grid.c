/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:35:03 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/10 15:21:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			draw_player_cell(t_app *app,
					t_rect *cell_bounds, int player_i)
{
	int		pixel;
	int		cache_pixel;
	int		y;
	int		x;
	int		cache_x;
	int		cache_y;

	y = cell_bounds->y;
	cache_y = player_i == 0 ? app->player_1_cell_y : app->player_2_cell_y;
	while (y < cell_bounds->y + cell_bounds->h &&
			y >= 0 && y < app->window->screen_height)
	{
		x = cell_bounds->x;
		cache_x = app->info_bounds.x + 10;
		while (x < cell_bounds->x + cell_bounds->w &&
				x >= 0 && x < app->window->screen_width)
		{
			pixel = y * app->window->line_bytes + x * 4;
			cache_pixel = cache_y * app->window->line_bytes + cache_x * 4;
			app->window->frame_buf[pixel] = app->window->frame_buf[cache_pixel];
			app->window->frame_buf[pixel + 1] = app->window->frame_buf[cache_pixel + 1];
			app->window->frame_buf[pixel + 2] = app->window->frame_buf[cache_pixel + 2];
			app->window->frame_buf[pixel + 3] = app->window->frame_buf[cache_pixel + 3];
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
			if (app->board->cells[y][x].player_i == EMPTY)
				draw_rectangle(app, &cell_bounds, app->board->cells[y][x].color);
			else
				draw_player_cell(app, &cell_bounds, app->board->cells[y][x].player_i);
		}
		cell_bounds.y += app->cell_size + 1;
	}
}

static void				draw_player_cached_cell(t_app *app, int player_i)
{
	int		color;
	int		x;
	int		y;
	t_rect	cell_bounds;

	x = app->info_bounds.x + 10;
	if (player_i == 0)
	{
		color = PLAYER_1_COLOR;
		y = app->player_1_cell_y;
	}
	else
	{
		color = PLAYER_2_COLOR;
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
	while (i < app->num_players)
	{
		draw_player_cached_cell(app, i);
		i++;
	}
	draw_cells(app);
}

void				set_grid_cell_render_dimensions(t_app *app)
{
	app->cell_size = (app->grid_bounds.w / app->board->width >
	app->grid_bounds.h / app->board->height ?
		app->grid_bounds.h / app->board->height :
			app->grid_bounds.w / app->board->width) - 1;
	app->player_1_cell_y = app->info_bounds.y + 100;
	app->player_2_cell_y = app->info_bounds.y + 100 + app->cell_size + 1;
}