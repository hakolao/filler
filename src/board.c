/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 13:27:49 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 18:09:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
			app->board->cells[y][x].id = line[i];
			if (line[i] == PLAYER_1)
				app->board->cells[y][x].color = app->player1_color;
			else if (line[i] == PLAYER_2)
				app->board->cells[y][x].color = app->player2_color;
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
