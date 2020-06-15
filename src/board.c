/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:27:49 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 18:24:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		set_cell_colors(t_app *app, int x, int y, char cell)
{
	app->board->cells[y][x].id = cell;
	if (cell == PLAYER_1)
		app->board->cells[y][x].color = app->player1_color;
	else if (cell == PLAYER_2)
		app->board->cells[y][x].color = app->player2_color;
}

static int		set_grid_cell_render_dimensions(t_app *app)
{
	app->cell_size = (app->grid_bounds.w / app->board->width >
	app->grid_bounds.h / app->board->height ?
		app->grid_bounds.h / app->board->height :
			app->grid_bounds.w / app->board->width) - 1;
	app->player_1_cell_y = app->info_bounds.y + 100;
	app->player_2_cell_y = app->info_bounds.y + 100 + app->cell_size + 1;
	return (TRUE);
}

int				parse_board(t_app *app)
{
	int		y;
	int		i;
	int		x;
	char	*line;

	get_next_line(0, &line);
	ft_strdel(&line);
	while (get_next_line(0, &line) > 0)
	{
		y = ft_atoi(line);
		i = 4;
		x = 0;
		while (line[i])
		{
			set_cell_colors(app, x, y, line[i]);
			i++;
			x++;
		}
		ft_strdel(&line);
		if (y == app->board->height - 1)
			break ;
	}
	return (TRUE);
}

int				init_new_board(t_app *app, char *line)
{
	int			y;
	int			x;

	if (app->board == NULL)
	{
		if (!(app->board = malloc(sizeof(*app->board))) ||
			!parse_dimensions(&app->board->height,
				&app->board->width, 8, line) ||
			!set_grid_cell_render_dimensions(app) ||
			!(app->board->cells = malloc(sizeof(*app->board->cells) *
			app->board->height)))
			return (FALSE);
		y = -1;
		while (++y < app->board->height)
		{
			if (!(app->board->cells[y] =
				malloc(sizeof(**app->board->cells) * app->board->width)))
				return (FALSE);
			x = -1;
			while (++x < app->board->width)
				init_new_cell(&app->board->cells[y][x], x, y);
		}
	}
	return (TRUE);
}
