/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:27:49 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/10 14:35:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		init_new_cell(t_cell *cell, int x, int y)
{
	cell->color = EMPTY_COLOR;
	cell->x = x;
	cell->y = y;
	cell->player_i = EMPTY;
}

static void		parse_dimensions(int *width, int *height, int i, char *line)
{
	*width = ft_atoi(line + i);
	while (!ft_isdigit(line[i]))
		i++;
	*height = ft_atoi(line + i);
}

int				parse_board_line(t_app *app, char *line)
{
	int	y;
	int	i;
	int	x;

	y = ft_atoi(line);
	i = 4;
	x = 0;
	while (line[i])
	{
		if (line[i] == 'o' || line[i] == 'O')
		{
			app->board->cells[y][x].player_i = PLAYER_1;
			app->board->cells[y][x].color = PLAYER_1_COLOR;
		}
		else if (line[i] == 'x' || line[i] == 'X')
		{
			app->board->cells[y][x].player_i = PLAYER_2;
			app->board->cells[y][x].color = PLAYER_2_COLOR;
		}
		i++;
		x++;
	}
	return (TRUE);
}

int				init_new_board(t_app *app, char *line)
{
	int			y;
	int			x;

	parse_dimensions(&app->board->width, &app->board->height, 8, line);
	if (!(app->board = malloc(sizeof(*app->board))))
		return (FALSE);
	if (!(app->board->cells = malloc(sizeof(*app->board->cells) *
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
	return (TRUE);
}

int				init_new_piece(t_app *app, char *line)
{
	int			y;
	int			x;

	parse_dimensions(&app->current_piece->width,
		&app->current_piece->height, 6, line);
	if (app->current_piece->cells != NULL)
		free(app->current_piece->cells);
	if (!(app->current_piece->cells =
			malloc(sizeof(*app->current_piece->cells) *
			app->current_piece->height)))
		return (FALSE);
	y = -1;
	while (++y < app->current_piece->height)
	{
		if (!(app->current_piece->cells[y] =
				malloc(sizeof(**app->current_piece->cells) *
				app->current_piece->width)))
			return (FALSE);
		x = -1;
		while (++x < app->board->width)
			init_new_cell(&app->board->cells[y][x], x, y);
	}
	return (TRUE);
}