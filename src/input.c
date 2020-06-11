/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/11 17:20:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		parse_player_1(t_app *app, char *line)
{
	if (ft_strstr(line, app->name) && (app->is_player1 = TRUE) &&
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

static int		parse_piece(t_app *app)
{
	int			y;
	int			x;
	char		*line;
	
	y = 0;
	while (get_next_line(0, &line) > 0)
	{
		ft_dprintf(2, "Token parsing: %s\n", line);
		x = 0;
		while (line[x] && x < app->current_piece->width)
		{
			if (line[x] == '*')
				app->current_piece->cells[y][x].player_i = UNPLACED;
			x++;
		}
		if (y == app->current_piece->height - 1)
			return (TRUE);
		y++;
	}
	return (TRUE);
}

static int		set_score(t_app *app)
{
	int	p1_score;
	int	p2_score;
	int	y;
	int	x;

	p1_score = 0;
	p2_score = 0;
	if (app->board == NULL)
		return (TRUE);
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
	app->player1_score = p1_score - 1;
	app->player2_score = p2_score - 1;
	return (TRUE);
}

static int		read_stdin(t_app *app)
{
	char		*line;
	
	while (get_next_line(0, &line) > 0)
	{
		ft_dprintf(2, "Tryna read %s\n", line);
		if ((ft_strstr(line, "p1") && !parse_player_1(app, line)) ||
			(ft_strstr(line, "p2") && !parse_player_2(app, line)))
			return (FALSE);
		else if (ft_strstr(line, "Plateau"))
		{
			if (!init_new_board(app, line) || !parse_board(app))
				return (FALSE);
			return (TRUE);
		}
		else if (ft_strstr(line, "Piece"))
		{
			if (!init_new_piece(app, line) || !parse_piece(app))
				return (FALSE);
			set_score(app);
			place_piece(app);
			ft_strdel(&line);
			return (TRUE);
		}
		else if (ft_strstr(line, "== 0"))
			app->player1_score = ft_atoi(line + 10);
		else if (ft_strstr(line, "== X") &&
			(app->player2_score = ft_atoi(line + 10)) &&
			(app->is_finished = TRUE))
		{
			ft_strdel(&line);
			return (TRUE);
		}
		ft_strdel(&line);
	}
	return (TRUE);
}

int				update_map(t_app *app)
{
	app->window->redraw = TRUE;
	return (read_stdin(app));
}