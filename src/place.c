/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 15:38:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/17 15:34:54 by ohakola          ###   ########.fr       */
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

	if (alignment == left)
	{
		x = -1;
		while (++x < piece->width)
		{
			y = -1;
			while (++y < piece->height)
				if (piece->cells[y][x].id == UNPLACED)
					return (x);
		}
	}
	x = piece->width;
	while (--x >= 0)
	{
		y = piece->height;
		while (--y >= 0)
			if (piece->cells[y][x].id == UNPLACED)
				return (piece->width - x);
	}
	return (x);
}

static int		height_extra(t_piece *piece, enum e_alignment alignment)
{
	int		x;
	int		y;

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

int				is_best(t_app *app, int *pos, int *other)
{
	(void)app;
	(void)pos;
	(void)other;
	return (TRUE);
}

int				place_piece(t_app *app)
{
	int		*xy_minmaxes;
	int		x;
	int		y;
	int		*best;

	xy_minmaxes = (int[4]){
		-width_extra(app->current_piece, left),
		app->board->width - app->current_piece->width +
		width_extra(app->current_piece, right),
		-height_extra(app->current_piece, top),
		app->board->height - app->current_piece->height +
		height_extra(app->current_piece, down)
	};
	y = xy_minmaxes[2] - 1;
	best = NULL;
	while (++y < xy_minmaxes[3])
	{
		x = xy_minmaxes[0] - 1;
		while (++x < xy_minmaxes[1])
			if (piece_fits(app, x, y) &&
				(best == NULL ||
					is_best(app, (int[2]){x, y}, best)))
				best = (int[2]){x, y};
	}
	return (best ?
			ft_printf("%d %d\n", best[1], best[0]) && TRUE : 
			ft_printf("%d %d\n", 0, 0) && FALSE);
}
