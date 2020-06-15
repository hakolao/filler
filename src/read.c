/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 18:31:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		parse_player(t_app *app, char *line)
{
	if (ft_strstr(line, "p1"))
		app->is_player1 = TRUE;
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
			return (FALSE);
		else if (ft_strstr(line, "Plateau"))
		{
			if (!init_new_board(app, line) || !parse_board(app))
				return (FALSE);
			return (TRUE);
		}
		else if (ft_strstr(line, "Piece"))
		{
			if (!init_new_piece(app, line) || !parse_piece(app) ||
				!place_piece(app))
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
