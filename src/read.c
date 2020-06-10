/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/10 14:50:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		parse_player_1(t_app *app, char *line)
{
	if (ft_match(line, app->name) && (app->is_player1 = TRUE) &&
		!(app->player1_name = ft_strdup(app->name)))
		return (FALSE);
	else if (!(app->player1_name =
				ft_strsub(line, 15, ft_strchr(line, ']') -
				ft_strchr(line, '['))))
		return (FALSE);
	return (TRUE);
}

static int		parse_player_2(t_app *app, char *line)
{
	if ((app->is_player1) &&
		!(app->player2_name =
				ft_strsub(line, 15, ft_strchr(line, ']') -
				ft_strchr(line, '['))))
		return (FALSE);
	else if (!(app->player2_name = ft_strdup(app->name)))
		return (FALSE);
	return (TRUE);
}

static int		parse_piece_line(t_app *app, char *line)
{
	static int	y;
	int			x;

	y = y > 0 ? y : 0;
	x = -1;
	while (line[++x] && y < app->current_piece->height)
		if (line[x] == '*')
			app->board->cells[y][x].player_i = UNPLACED;
	if (y == app->current_piece->height)
		y = 0;
	return (TRUE);
}

static int		read_stdin(t_app *app)
{
	char		*line;

	while (get_next_line(0, &line) > 0)
	{
		if (ft_match(line, "p1") && !parse_player_1(app, line))
			return (FALSE);
		else if (ft_match(line, "p2") && !parse_player_2(app, line))
			return (FALSE);
		else if (app->board == NULL && ft_match(line, "Plateau") &&
				!init_new_board(app, line))
			return (FALSE);
		else if (ft_match(line, "Piece") && !init_new_piece(app, line))
			return (FALSE);
		else if (ft_isdigit(line[0]) && !parse_board_line(app, line))
			return (FALSE);
		else if ((line[0] == '.' || line[0] == '*') &&
			!parse_piece_line(app, line))
			return (FALSE);
		else if (ft_match(line, "== 0"))
			app->player1_score = ft_atoi(line + 10);
		else if (ft_match(line, "== X"))
		{
			app->player2_score = ft_atoi(line + 10);
			app->is_finished = TRUE;
		}
		ft_strdel(&line);
	}
	return (TRUE);
}

int				read_filler_input(t_app *app)
{
	int	p1_score;
	int	p2_score;
	int	y;
	int	x;

	p1_score = 0;
	p2_score = 0;
	if (!read_stdin(app))
		return (FALSE);
	y = -1;
	while (++y < app->board->height)
	{
		x = -1;
		while (++x < app->board->width)
		{
			if (app->board->cells[y][x].player_i == PLAYER_1)
				p1_score++;
			else if (app->board->cells[y][x].player_i == PLAYER_2)
				p2_score++;
		}
	}
	return (TRUE);
}