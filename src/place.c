/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:38:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/17 16:02:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		increment_overlaps(t_app *app, int *overlaps, char id)
{
	if (app->is_player1 && id == PLAYER_1)
		overlaps[0]++;
	else if (!app->is_player1 && id == PLAYER_2)
		overlaps[0]++;
	else if (app->is_player1 && id == PLAYER_2)
		overlaps[1]++;
	else if (!app->is_player1 && id == PLAYER_1)
		overlaps[1]++;
}

static int		piece_fits(t_app *app, int board_x, int board_y)
{
	int		x;
	int		y;
	int		*overlaps;
	t_cell	piece_cell;
	t_cell	board_cell;

	y = 0;
	overlaps = (int[2]){0, 0};
	while (y < app->current_piece->height)
	{
		x = 0;
		while (x < app->current_piece->width)
		{
			piece_cell = app->current_piece->cells[y][x];
			if (piece_cell.id == UNPLACED)
			{
				board_cell = app->board->cells[board_y + y][board_x + x];
				increment_overlaps(app, overlaps, board_cell.id);
			}
			x++;
		}
		y++;
	}
	return (overlaps[0] == 1 && overlaps[1] == 0);
}

static void		set_enemy_center_of_mass(t_app *app, int com[2])
{
	int		x;
	int		y;
	char	enemy;
	int		count;

	enemy = app->is_player1 ? PLAYER_2 : PLAYER_1;
	y = -1;
	count = 0;
	while (++y < app->board->height)
	{
		x = -1;
		while (++x < app->board->width)
		{
			if (app->board->cells[y][x].id == enemy)
			{
				com[0] += x;
				com[1] += y;
				count++;
			}
		}
	}
	com[0] /= count;
	com[1] /= count;
}

/*
** Pos is better if its distance from enemy center of mass is smaller than
** other
*/

static int		is_best(int *pos, int *other, int com[2])
{
	return (ft_sqrt((pos[0] - com[0]) * (pos[0] - com[0]) +
		(pos[1] - com[1]) * (pos[1] - com[1])) <
		ft_sqrt((other[0] - com[0]) * (other[0] - com[0]) +
		(other[1] - com[1]) * (other[1] - com[1])));
}

/*
** 1. Calculate extra bounds based on piece extra space
** 2. Try placing piece, if fits, check if that is the best location
** based on strategy
** 3. If best, print that output. If can't place, print 0 0
*/

int				place_piece(t_app *app)
{
	int		*xy_minmaxes;
	int		x;
	int		y;
	int		*best;
	int		com[2];

	set_enemy_center_of_mass(app, com);
	xy_minmaxes = (int[4]){-w_extra(app->current_piece, left),
		app->board->width - app->current_piece->width +
		w_extra(app->current_piece, right), -h_extra(app->current_piece, top),
		app->board->height - app->current_piece->height +
		h_extra(app->current_piece, down)
	};
	y = xy_minmaxes[2] - 1;
	best = NULL;
	while (++y < xy_minmaxes[3])
	{
		x = xy_minmaxes[0] - 1;
		while (++x < xy_minmaxes[1])
			if (piece_fits(app, x, y) &&
				(best == NULL || is_best((int[2]){x, y}, best, com)))
				best = (int[2]){x, y};
	}
	return (best ? ft_printf("%d %d\n", best[1], best[0]) :
			!ft_printf("%d %d\n", 0, 0));
}
