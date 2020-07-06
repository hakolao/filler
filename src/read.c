/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/07/06 21:45:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		parse_player(t_app *app, char *line)
{
	if (ft_strstr(line, "p1"))
		app->is_player1 = TRUE;
	return (TRUE);
}

static void		calculate_center_of_masses(t_app *app)
{
	int	*ecom;
	int	*pcom;

	ecom = mass_center(app,
		(int[2]){0}, app->is_player1 ? PLAYER_2 : PLAYER_1);
	pcom = mass_center(app, (int[2]){0},
		app->is_player1 ? PLAYER_1 : PLAYER_2);
	app->enemy_com[0] = ecom[0];
	app->enemy_com[1] = ecom[1];
	app->player_com[0] = pcom[1];
	app->player_com[1] = pcom[1];
}

static int		handle_piece(t_app *app, char *line)
{
	calculate_center_of_masses(app);
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
