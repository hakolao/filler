/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 17:33:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		parse_player(t_app *app, char *line)
{
	if (ft_strstr(line, "p1"))
		app->is_player1 = TRUE;
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
		x = 0;
		while (line[x] && x < app->current_piece->width)
		{
			if (line[x] == UNPLACED)
				app->current_piece->cells[y][x].id = UNPLACED;
			x++;
		}
		if (y >= app->current_piece->height - 1)
			return (TRUE);
		y++;
	}
	return (TRUE);
}

static int		read_stdin(t_app *app)
{
	char		*line;
	
	if (app->is_finished)
		return (FALSE);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strlen(line) == 0)
			return (TRUE);
		if ((ft_strstr(line, app->name) && !parse_player(app, line)))
			return (FALSE);
		else if (ft_strstr(line, "Plateau"))
		{
			if ((!init_new_board(app, line) || !parse_board(app)))
				return (FALSE);
			return (TRUE);
		}
		else if (ft_strstr(line, "Piece"))
		{
			if (!init_new_piece(app, line) || !parse_piece(app))
				return (FALSE);
			if (!place_piece(app))
				return (FALSE);
			ft_strdel(&line);
			return (TRUE);
		}
		ft_strdel(&line);
	}
	return (TRUE);
}

int				update_map(t_app *app)
{
	return (read_stdin(app));
}