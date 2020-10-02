/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 16:43:11 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/02 15:48:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		set_score(t_app *app, int o_count, int x_count)
{
	if (o_count > app->player1_count)
	{
		app->player1_count = o_count;
		app->player1_score++;
	}
	if (x_count > app->player2_count)
	{
		app->player2_count = x_count;
		app->player2_score++;
	}
	if ((app->player1_score > app->player2_score && app->is_player1) ||
		(app->player1_score < app->player2_score && !app->is_player1))
		app->i_won = true;
}

/*
** Calculates score based on each turn's incremented cell id counts.
** As shown above, if cell id count changed, score is incremented.
*/

void			calculate_score(t_app *app)
{
	int				x_count;
	int				o_count;
	int				x;
	int				y;

	y = -1;
	x_count = 0;
	o_count = 0;
	while (++y < app->board->height)
	{
		x = -1;
		while (++x < app->board->width)
		{
			if (app->board->cells[y][x].id == PLAYER_1)
				o_count++;
			else if (app->board->cells[y][x].id == PLAYER_2)
				x_count++;
		}
	}
	set_score(app, o_count, x_count);
}
