/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:38:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/10 16:40:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		piece_fits(t_app *app, int board_x, int board_y)
{
	int	x_diff;
	int	y_diff;
	int	x;
	int	y;
	int	overlaps_by_one;

	x_diff = app->board->width - app->current_piece->width;
	y_diff = app->board->height - app->current_piece->height;
	y = -1;
	overlaps_by_one = FALSE;
	while (++y < app->current_piece->height)
	{
		x = -1;
		while (++x < app->current_piece->width)
		{
			if (!overlaps_by_one && app->is_player1 &&
					app->current_piece->cells[y][x].player_i == UNPLACED &&
					app->board->cells[board_y + y + y_diff][
						board_x + x + x_diff
					].player_i == PLAYER_1)
				overlaps_by_one = TRUE;
			else if (!overlaps_by_one &&
					app->current_piece->cells[y][x].player_i == UNPLACED &&
					app->board->cells[board_y + y + y_diff][
						board_x + x + x_diff
					].player_i == PLAYER_2)
				overlaps_by_one = TRUE;
			else if (app->current_piece->cells[y][x].player_i == UNPLACED &&
						app->board->cells[board_y + y + y_diff][
							board_x + x + x_diff
						].player_i != EMPTY)
				return (FALSE);
		}
	}
	return (TRUE);
}

void		place_piece(t_app *app)
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
	int		x;
	int		y;

	min_x = -app->current_piece->width;
	max_x = app->board->width - app->current_piece->width;
	min_y = -app->current_piece->height;
	max_y = app->board->height - app->current_piece->height;

	if (app->strategy == find_first)
	{
		y = min_y - 1;
		while (++y < max_y)
		{
			x = min_x - 1;
			while (++x < max_x)
				if (piece_fits(app, x, y))
					ft_printf("%d %d", x, y);
		}
	}
}