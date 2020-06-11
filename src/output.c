/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:38:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/11 13:48:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		piece_fits(t_app *app, int board_x, int board_y)
{
	int	x;
	int	y;
	int	overlaps_by_one;

	y = -1;
	overlaps_by_one = FALSE;
	while (++y < app->current_piece->height)
	{
		x = -1;
		while (++x < app->current_piece->width)
		{
			if (!overlaps_by_one && app->is_player1 &&
					app->current_piece->cells[y][x].player_i == UNPLACED &&
					app->board->cells[board_y + y][board_x + x].player_i == PLAYER_1)
				overlaps_by_one = TRUE;
			else if (!overlaps_by_one && !app->is_player1 &&
					app->current_piece->cells[y][x].player_i == UNPLACED &&
					app->board->cells[board_y + y][board_x + x].player_i == PLAYER_2)
				overlaps_by_one = TRUE;
			else if (overlaps_by_one &&
					app->current_piece->cells[y][x].player_i == UNPLACED &&
						app->board->cells[board_y + y][board_x + x].player_i != EMPTY)
				return (FALSE);
		}
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
			return (x);
	}
	return (x);
}

static int	height_extra(t_piece *piece, enum e_alignment alignment)
{
	int		x;
	int		y;
	int		found;

	found = FALSE;
	if (alignment == left)
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
				return (y);
	}
	return (y);
}

void		place_piece(t_app *app)
{
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
	int		x;
	int		y;

	min_x = -width_extra(app->current_piece, left);
	max_x = app->board->width - app->current_piece->width -
		width_extra(app->current_piece, right);
	min_y = -height_extra(app->current_piece, left);
	max_y = app->board->height - app->current_piece->height -
		height_extra(app->current_piece, right);
	ft_dprintf(2, "%d %d %d %d\n", min_x, max_x, min_y, max_y);
	debug_app(app);
	debug_board(app->board);
	if (app->strategy == find_first)
	{
		y = min_y;
		while (y < max_y)
		{
			x = min_x;
			while (x < max_x)
			{
				if (piece_fits(app, x, y))
				{
					ft_dprintf(2, "Fits %d %d\n", x, y);
					ft_printf("%d %d", x, y);
					break ;
				}
				x++;
			}
		}
		y++;
	}
}