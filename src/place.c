/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:38:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/12 15:21:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		piece_fits(t_app *app, int board_x, int board_y)
{
	int		x;
	int		y;
	int		overlaps_by_one;
	t_cell	piece_cell;
	t_cell	board_cell;

	y = 0;
	overlaps_by_one = FALSE;
	while (y < app->current_piece->height)
	{
		x = 0;
		while (x < app->current_piece->width)
		{
			piece_cell = app->current_piece->cells[y][x];
			if (piece_cell.player_i == UNPLACED)
			{
				board_cell = app->board->cells[board_y + y][board_x + x];
				if (!overlaps_by_one &&
					(((app->is_player1 && board_cell.player_i == PLAYER_1) ||
					(!app->is_player1 && board_cell.player_i == PLAYER_2))))
					overlaps_by_one = TRUE;
				else if (overlaps_by_one &&
					(board_cell.player_i == PLAYER_1 ||
					board_cell.player_i == PLAYER_2))
					return (FALSE);
			}
			x++;
		}
		y++;
	}
	return (overlaps_by_one);
}

static int	width_extra(t_piece *piece, enum e_alignment alignment)
{
	int		x;
	int		y;
	int		found;

	found = FALSE;
	if (alignment == left)
	{
		x = -1;
		while (++x < piece->width)
		{
			y = -1;
			while (++y < piece->height)
				if (piece->cells[y][x].player_i == UNPLACED)
					found = TRUE;
			if (found)
				return (x);
		}
	}
	x = piece->width;
	while (--x >= 0)
	{
		y = piece->height;
		while (--y >= 0)
			if (piece->cells[y][x].player_i == UNPLACED)
				found = TRUE;
		if (found)
			return (piece->width - x);
	}
	return (x);
}

static int	height_extra(t_piece *piece, enum e_alignment alignment)
{
	int		x;
	int		y;
	int		found;

	found = FALSE;
	if (alignment == top)
	{
		y = -1;
		while (++y < piece->height)
		{
			x = -1;
			while (++x < piece->width)
				if (piece->cells[y][x].player_i == UNPLACED)
					return (y);
		}
	}
	y = piece->height;
	while (--y >= 0)
	{
		x = piece->width;
		while (--x >= 0)
			if (piece->cells[y][x].player_i == UNPLACED)
				return (piece->height - y);
	}
	return (y);
}

int			place_piece(t_app *app)
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
	int		x;
	int		y;

	min_x = -width_extra(app->current_piece, left);
	max_x = app->board->width - app->current_piece->width +
		width_extra(app->current_piece, right);
	min_y = -height_extra(app->current_piece, top);
	max_y = app->board->height - app->current_piece->height +
		height_extra(app->current_piece, down);
	ft_dprintf(2, "max indices: min_x: %d, max_x: %d, min_y: %d, max_y: %d\n", min_x, max_x, min_y, max_y);
	debug_board(app->board);
	if (app->strategy == find_first)
	{
		y = min_y - 1;
		while (++y < max_y)
		{
			x = min_x - 1;
			while (++x < max_x)
				if (piece_fits(app, x, y))
				{
					ft_dprintf(2, "Placing at: Y: %d X: %d\n", y, x);
					ft_printf("%d %d\n", y, x);
					return (TRUE);
				}
		}
	}
	ft_printf("Can't place\n");
	return (FALSE);
}