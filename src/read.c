/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/17 17:29:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		parse_player(t_app *app, char *line)
{
	if (ft_strstr(line, "p1"))
		app->is_player1 = TRUE;
	return (TRUE);
}

static int		handle_piece(t_app *app, char *line)
{
	if (!init_new_piece(app, line) || !parse_piece(app) ||
		!place_piece(app))
	{
		ft_strdel(&line);
		return (FALSE);
	}
	ft_strdel(&line);
	return (TRUE);
}

static int		read_stdin(t_app *app)
{
	char		*line;

	if (app->is_finished)
		return (FALSE);
	while (get_next_line(0, &line) > 0)
	{
		if ((ft_strstr(line, app->name) && !parse_player(app, line)))
		{
			ft_strdel(&line);
			return (FALSE);
		}
		else if (ft_strstr(line, "Plateau"))
		{
			if (!init_new_board(app, line) || !parse_board(app))
				return (FALSE);
			ft_strdel(&line);
			return (TRUE);
		}
		else if (ft_strstr(line, "Piece"))
			return (handle_piece(app, line));
		ft_strdel(&line);
	}
	return (TRUE);
}

/*
** Read stdin based on input data from filler_vm
** Above function also sets app data structs based on
** the read input data.
*/

int				update_map(t_app *app)
{
	return (read_stdin(app));
}
