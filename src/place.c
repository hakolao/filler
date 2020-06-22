/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:38:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/22 15:03:48 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void				increment_overlaps(t_app *app, int *overlaps, char id)
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

static int				piece_fits(t_app *app, int board_x, int board_y)
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

/*
** Token position is better the closer it is to enemy center of mass and
** the farther it is from corners
*/

static int				get_fitness(t_app *app, int *pos, int *ecom)
{
	int		fitness;

	fitness = 0;
	fitness += distance(pos, ecom);
	fitness += distance(pos, (int[2]){0, 0});
	fitness += distance(pos, (int[2]){app->board->width - 1, 0});
	fitness += distance(pos, (int[2]){app->board->width - 1,
		app->board->height - 1});
	fitness += distance(pos, (int[2]){0, app->board->height - 1});
	return (fitness);
}

static int				is_better(t_app *app, int *pos,
						int *best_so_far, int *ecom)
{
	int		fitness;
	int		fitness_so_far;

	fitness = get_fitness(app, pos, ecom);
	fitness_so_far = get_fitness(app, best_so_far, ecom);
	return (fitness > fitness_so_far);
}

/*
** 1. Calculate extra bounds based on piece extra space
** 2. Try placing piece, if fits, check if that is the best location
** based on strategy
** 3. If best, print that output. If can't place, print 0 0
*/

int						place_piece(t_app *app)
{
	int		*xy_minmaxes;
	int		x;
	int		y;
	int		*best;
	int		*com;

	com = enemy_center_of_mass(app, (int[2]){0});
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
				(best == NULL || is_better(app, (int[2]){x, y}, best, com)))
				best = (int[2]){x, y};
	}
	return (best ? ft_printf("%d %d\n", best[1], best[0]) :
			!ft_printf("%d %d\n", 0, 0));
}
