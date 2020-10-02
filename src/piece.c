/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:07:02 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/02 15:47:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			destroy_current_piece_cells(t_app *app)
{
	int		y;

	y = -1;
	while (++y < app->current_piece->height)
		free(app->current_piece->cells[y]);
	free(app->current_piece->cells);
	app->current_piece->cells = NULL;
}

static int			init_first_piece_if_needed(t_app *app)
{
	if (app->current_piece == NULL)
	{
		if (!(app->current_piece = malloc(sizeof(*app->current_piece))))
			return (false);
		app->current_piece->cells = NULL;
	}
	return (true);
}

int					init_new_piece(t_app *app, char *line)
{
	int			y;
	int			x;

	if (!init_first_piece_if_needed(app))
		return (false);
	if (app->current_piece->cells != NULL)
		destroy_current_piece_cells(app);
	parse_dimensions(&app->current_piece->height,
		&app->current_piece->width, 6, line);
	if (!(app->current_piece->cells =
			malloc(sizeof(*app->current_piece->cells) *
				app->current_piece->height)))
		return (false);
	y = -1;
	while (++y < app->current_piece->height)
	{
		if (!(app->current_piece->cells[y] =
				malloc(sizeof(**app->current_piece->cells) *
				app->current_piece->width)))
			return (false);
		x = -1;
		while (++x < app->current_piece->width)
			init_new_cell(&app->current_piece->cells[y][x], x, y);
	}
	return (true);
}

int					parse_piece(t_app *app)
{
	int			y;
	int			x;
	char		*line;

	y = 0;
	while (get_next_line(0, &line) > 0)
	{
		x = 0;
		while (line[x] && x < app->current_piece->width)
		{
			if (line[x] == UNPLACED)
				app->current_piece->cells[y][x].id = UNPLACED;
			x++;
		}
		if (y >= app->current_piece->height - 1)
		{
			ft_strdel(&line);
			return (true);
		}
		y++;
		ft_strdel(&line);
	}
	return (true);
}
