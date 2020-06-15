/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:38:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 18:42:31 by ohakola          ###   ########.fr       */
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

static int		width_extra(t_piece *piece, enum e_alignment alignment)
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
				if (piece->cells[y][x].id == UNPLACED)
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
			if (piece->cells[y][x].id == UNPLACED)
				found = TRUE;
		if (found)
			return (piece->width - x);
	}
	return (x);
}

static int		height_extra(t_piece *piece, enum e_alignment alignment)
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
				if (piece->cells[y][x].id == UNPLACED)
					return (y);
		}
	}
	y = piece->height;
	while (--y >= 0)
	{
		x = piece->width;
		while (--x >= 0)
			if (piece->cells[y][x].id == UNPLACED)
				return (piece->height - y);
	}
	return (y);
}

int				place_piece(t_app *app)
{
	int		min_x;
	int		max_x;
	int		max_y;
	int		x;
	int		y;

	min_x = -width_extra(app->current_piece, left);
	max_x = app->board->width - app->current_piece->width +
		width_extra(app->current_piece, right);
	max_y = app->board->height - app->current_piece->height +
		height_extra(app->current_piece, down);
	if (app->strategy == find_first)
	{
		y = -height_extra(app->current_piece, top) - 1;
		while (++y < max_y)
		{
			x = min_x - 1;
			while (++x < max_x)
				if (piece_fits(app, x, y))
					return (ft_printf("%d %d\n", y, x) && TRUE);
		}
		ft_printf("%d %d\n", 0, 0);
	}
	return (FALSE);
}
